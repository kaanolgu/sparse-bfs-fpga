//////////////////////////
//
//   Project     : Sparse BFS on Zedboard
//   File        : main.cc
// 
//   Created on: Feb 3, 2015   
//   Original Author: Yaman Umuroglu <yamanu@idi.ntnu.no> (https://github.com/maltanar/fpga-booleanring-bfs)
//   Modified on: March 10,2022
//	 Modified By: Kaan Olgu <kaan.olgu@bristol.ac.uk>
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <malloc.h>
#include <xscutimer.h>
#include "xil_cache.h"
#include "xparameters.h"
#include "GraphManager.h"
#include "classicalbfsoperation.h"
#include "BitmapBFSOperation.h"
#include "BFSAccelerator.h"
#include "HardwareBFSManager.h"
#include "sdcard.h"

using namespace std;

unsigned int hardwarePECount;
unsigned int matrixID;
float mteps_record[16];
float time_record[16];
volatile unsigned int * baseData = (volatile unsigned int *) 0x10000000;
volatile int * distVec = (volatile int *) 0x1F000000;

const float peMHz = 250.0;
const float timerMHz = 333.3;
const float ticksPerSec = 1000000.0;

#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID

XScuTimer timer;

#define TIMER_DISABLE	0;

void TimerSetup() {
	TIMER_DISABLE
	XScuTimer_Config * timerConfig = XScuTimer_LookupConfig(TIMER_DEVICE_ID);
	XScuTimer_CfgInitialize(&timer, timerConfig, timerConfig->BaseAddr);
	XScuTimer_DisableAutoReload(&timer);
	XScuTimer_DisableInterrupt(&timer);
	//XScuTimer_SetPrescaler(&timer, 1);
}

void TimerLoadAndStart(unsigned int value) {
	TIMER_DISABLE
	XScuTimer_LoadTimer(&timer, value);
	XScuTimer_Start(&timer);
}

void TimerStop() {
	TIMER_DISABLE
	XScuTimer_Stop(&timer);
}

unsigned int TimerRead() {
	return XScuTimer_GetCounterValue(&timer);
}



const char * getMatrixName(unsigned int id, unsigned int peCount) {
	if (peCount == 1) {
		return getMatrixNameP1(id);
	} else if (peCount == 2) {
		return getMatrixNameP2(id);
	}else {
		cout << "Unknown PE count!" << endl;
		return NULL;
	}
}

unsigned int loadedMatrixID = 0, loadedPECount = 0;
void * loadedBasePtr = 0;

void * loadMatrix(unsigned int id, unsigned int peCount) {
	VERBOSE(
			cout << "Loading matrix " << id << " with " << peCount << " partitions.." << endl; cout << "Matrix name: " << getMatrixName(id, peCount) << endl;);
	void * ret = 0;

	// is this already loaded?
	if (loadedMatrixID == id && loadedPECount == peCount) {
		VERBOSE(cout << "Reusing in-memory matrix..." << endl);
		return loadedBasePtr;
	}

	mount();
	if (peCount == 1) {
		ret = loadMatrixP1(id);
	} else if (peCount == 2) {
		ret = loadMatrixP2(id);
	}  else {
		cout << "Unknown PE count!" << endl;
	}

	if (ret) {
		// cache the loaded matrix details to reuse later
		loadedMatrixID = id;
		loadedPECount = peCount;
		loadedBasePtr = ret;
	}

	unmount();
	return ret;
}

void HybridBFS(unsigned int matrixID, unsigned int rootNode) {

	// TODO
	assert(0);
}

void SoftwareBFS(unsigned int matrixID, unsigned int rootNode) {
	Xil_DCacheEnable();
	VERBOSE(cout << "Method: Software BFS" << endl);
	void * configBase = loadMatrix(matrixID, 1);
	GraphManager mgr((unsigned int *) configBase);
	VERBOSE(mgr.printBaseInfo());
	GraphMatrixData * graphData = mgr.getPartitionData(0);
	BitmapBFSOperation op(graphData);
	op.setRootNode(rootNode);
	unsigned int timerStart = 0xffffffff, timerStop;
	unsigned long int totalTicks = 0;

	cout << "<--- SW Results Table ---> \n";	
	cout << "> MatrixID = " << matrixID << "\t\n" << "> Root Node = " << rootNode << "\t\n"
	 <<"> PE Count = "<< hardwarePECount << "\t\n";

	int i = 0, frontierSize = 0;
	while (!op.isConverged()) {
		TimerLoadAndStart(timerStart);
		frontierSize = op.step();
		timerStop = TimerRead();
		TimerStop();
	    //cout << i << "\t" << frontierSize << "\t" << timerStart - timerStop << "\t" /*<< op.getEdgeVisits()*/ << endl;
		//cout << timerStart-timerStop << "\t";

		//cout << timerStart - timerStop << "\t";
		i++;
		totalTicks += timerStart - timerStop;
		cout << timerStart - timerStop << " ticks of an 333 MHz clock" << endl;
		std::cout << "Frontier size at step " << i << " = " << frontierSize << std::endl << endl << endl;
	}
	cout << endl;

	VERBOSE(cout << "BFS took " << i << " steps to finish" << endl;
	cout << op.getResultCount() << " distances have been written" << endl;
	cout << "Total ticks: " << totalTicks << endl;
	float elapsedSecs = (float) totalTicks / (333333333.0f);
	cout << "Elapsed time (s): " << elapsedSecs << endl;
	float teps = (float) graphData->nz / elapsedSecs;
	cout << "MTEPS: " << teps / 1000000.0f << endl);

	Xil_DCacheDisable();
}

void HardwareBFS(unsigned int matrixID, unsigned int rootNode,unsigned int roots_i) {
	unsigned int baseAddrs[] = { 0x43c30000,0x43c20000,0x43c30000};
	VERBOSE(cout << "Performing BFS in hardware.." << endl);
	void * configBase = loadMatrix(matrixID, hardwarePECount);
	GraphManager gm((unsigned int *) configBase);
	VERBOSE(gm.printBaseInfo());
	HardwareBFSManager acc(baseAddrs);

	acc.setGraph(&gm);


	for (int i = 0; i < hardwarePECount; i++)
		acc.assignPartition(i, i);

	acc.initVectorSingleRoot(rootNode);
	acc.setDistance(0);

	unsigned int totalRegularCycles = 0, totalLevGenCycles = 0;
	unsigned int levelRegular = 0, levelLevGen = 0, level = 0;
	unsigned int totalFrontierSize = 0, currentFrontier = 1;

	unsigned int timerStart = 0xffffffff, timerStop;

	//cout << matrixID << "\t" << rootNode << "\t" << gm.getRowCount() << "\t"
	//		<< gm.getNzCount() << "\t";
	//cout << endl;
	while (currentFrontier != 0) {
		//cout << "distvec before: " << endl;	acc.printDistanceVector();

		TimerLoadAndStart(timerStart);
		acc.step();
		timerStop = TimerRead();
		TimerStop();
		totalRegularCycles += timerStart - timerStop;
		levelRegular = timerStart - timerStop;
		//acc.printProfiles();

		//cout << "distvec between: " << endl;	acc.printDistanceVector();

		TimerLoadAndStart(timerStart);
		acc.levelGeneration();
		timerStop = TimerRead();
		TimerStop();
		totalLevGenCycles += timerStart - timerStop;
		levelLevGen = timerStart - timerStop;

		totalFrontierSize += acc.getLastFrontierSize();
		currentFrontier = acc.getLastFrontierSize();

		//cout << "distvec after: " << endl;	acc.printDistanceVector();

		//cout << "level " << level << " " << currentFrontier << " "
		//		<< levelRegular + levelLevGen << " " << levelLevGen << " "
		//		<< levelRegular << endl;



		level++;

		if (level >= 15) {
			cout << "!!!!!!! Too many levels, exiting !!!!!!!!!" << endl;
			break;
		}
	}

	VERBOSE(
	cout << "----------------------------" << endl;
	cout << "Summary" << endl;
	cout << "----------------------------" << endl;
	cout << level << " BFS levels, total frontier size " << totalFrontierSize
			<< endl;
	unsigned int workloadSize = gm.getTotalWorkloadSize();
	unsigned int totalCycles = totalRegularCycles + totalLevGenCycles;

	cout << "Total cycles: " << totalCycles << " at " << timerMHz << " MHz"
			<< endl;
	cout << "Regular cycles %: "
			<< 100 * (float) totalRegularCycles / (float) totalCycles << endl;
	cout << "LevGen cycles %: "
			<< 100 * (float) totalLevGenCycles / (float) totalCycles << endl;
	cout << "Bandwidth during regular exec: "
			<< (timerMHz / peMHz) * (float) workloadSize
					/ (float) totalRegularCycles << " bytes/cycle" << endl;

	float secs = (float) totalCycles / (timerMHz * ticksPerSec);
	cout << "Runtime: " << secs << " seconds" << endl;
	float mteps = ((float) (gm.getNzCount()) / secs) / 1000000.0;
	cout << "Performance: " << mteps << " MTEPS" << endl;
	mteps_record[roots_i] = mteps;
	time_record[roots_i] = secs;
	);

}

int main() {
	Xil_DCacheDisable();
	cout << "==========================================================="
				<< endl;

		TimerSetup();

	    float avg_mteps[20] = {0.00};  //or double for higher precision
	    float avg_time[20] = {0.00};  //or double for higher precision
		matrixID=0;

		beginning:
		int rootNode = 0;
		unsigned int roots[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		unsigned int roots_i =0;

		//VERBOSE(cout << "Enter matrix ID: \n #2 - RMAT-19-32 " << endl);
		//cin >> matrixID;
		hardwarePECount = 1;
		//VERBOSE(cout <<  "Enter desired partition count: " << endl);
		//		cin >>hardwarePECount;
		//		assert(hardwarePECount <= 5);
	    switch(matrixID){
	    case 0: // Rmat 1-1

	    	{unsigned int newarr[] = {1128, 1782, 769, 48, 366, 1777, 772, 1518, 1682, 1103, 165, 585, 940, 1702, 1790, 1828};
	    	std::copy(newarr, newarr + 16, roots);
	      break;}

	    case 1: // RMAT-1-2
	    {unsigned int newarr[] = {193, 1355, 494, 1042, 845, 426, 1858, 612, 878, 165, 492, 1745, 82, 62, 1034, 1566};
	     std::copy(newarr, newarr + 16, roots);
	      break;}



	    case 2: // Rmat 1-3
	    		{unsigned int newarr[] = {1007, 148, 1306, 1986, 493, 499, 1324, 269, 1343, 1769, 926, 305, 386, 553, 743, 417};
	    	 std::copy(newarr, newarr + 16, roots);
	      break;}
	    case 3: // RMAT 1-4 // buna bir bak

			{unsigned int newarr[] = {776, 477, 754, 407, 103, 253, 460, 126, 750, 478, 121, 543, 107, 280, 11, 17 };
	    	 std::copy(newarr, newarr + 16, roots);
	      break;}
	    case 4: // RMAT 1-5

		{unsigned int newarr[] = {439, 843, 426, 205, 1554, 1769, 1858, 1504, 1688, 1914, 1951, 900, 1789, 1346, 1984, 984 };
	    	 std::copy(newarr, newarr + 16, roots);
	      break;}



	    case 5: // RMAT-1-6
	   {unsigned int newarr[] = {1811, 1837, 638, 698, 2002, 1581, 987, 1621, 1030, 295, 475, 1881, 506, 971, 936, 1308};
	    	    	 std::copy(newarr, newarr + 16, roots);
	      break;}
	    case 6: // RMAT-1-7
		{
			unsigned int newarr[] = {593, 920, 844, 1747, 784, 1259, 1811, 1735, 356, 645, 598, 1835, 304, 911, 1697, 77};
			 std::copy(newarr, newarr + 16, roots);
			break;
	    }

	    case 7: // RMAT-2-1
		{
			unsigned int newarr[] = {826, 1192, 1436, 127, 1619, 1506, 1229, 172, 1899, 1929, 444, 1212, 166, 1718, 1000, 1137};
			 std::copy(newarr, newarr + 16, roots);
			break;
	    }


	    case 8: // RMAT-2-2
		{
			unsigned int newarr[] = {1447, 563, 2034, 347, 722, 1560, 1372, 437, 95, 1214, 483, 250, 1590, 1981, 996, 942};
			 std::copy(newarr, newarr + 16, roots);
			break;
	    }

	    case 9: // RMAT-2-3
		{
			unsigned int newarr[] = {862, 1647, 259, 1551, 1683, 1664, 482, 2012, 1592, 741, 1795, 1670, 558, 124, 1184, 617};
			 std::copy(newarr, newarr + 16, roots);
			break;
	    }

	    case 10: // RMAT-2-4
		{
			unsigned int newarr[] = {1896, 1370, 1359, 1871, 534, 1314, 1964, 670, 1643, 1, 1474, 1313, 1395, 1742, 1136, 220};
			 std::copy(newarr, newarr + 16, roots);
			break;
	    }

	    case 11: // RMAT-2-5
		{
			unsigned int newarr[] = {1430, 1521, 1522, 1024, 798, 909, 1710, 1063, 1097, 1288, 463, 1307, 8, 1916, 558, 1403};
			 std::copy(newarr, newarr + 16, roots);
			break;
	    }


	    case 12: // RMAT-19-8
	    {
	    	unsigned int newarr[16] = {1940, 194, 1130, 1544, 1921, 648, 1040, 476, 1318, 1556, 164, 305, 1297, 651, 834, 1816};
	    	 std::copy(newarr, newarr + 16, roots);
	    	break;
	    }
	    case 13:// RMAT-19-16
	    {
	    	unsigned int newarr[16] = {1133, 827, 157, 577, 181, 1878, 1298, 283, 577, 1242, 1426, 242, 1061, 1390, 670, 1761};
	    	 std::copy(newarr, newarr + 16, roots);
	    	break;
	    }
		case 14: // RMAT-19-32
		{
	    	unsigned int newarr[16] = {1013, 1083, 1260, 1385, 847, 484, 1351, 1050, 430, 742, 344, 331, 216, 12, 1386, 816};
	    	 std::copy(newarr, newarr + 16, roots);
	    	break;
	    }
		case 15: // RMAT-20-8
		{
			unsigned int newarr[16] = {1064, 90, 1105, 739, 1719, 965, 1230, 127, 54, 1219, 493, 727, 770, 1166, 1246, 1930};
			 std::copy(newarr, newarr + 16, roots);
			break;
	    }
		case 16: // RMAT-20-16
	    			{
	    	unsigned int newarr[16] = {220, 189, 993, 78, 1631, 1961, 1934, 1068, 992, 1931, 217, 1212, 607, 1477, 589, 1194};
	    	 std::copy(newarr, newarr + 16, roots);
	      break;
	   }
		case 17: //RMAT-20-32
	    				{
	    	unsigned int newarr[16] = {1216, 984, 552, 837, 456, 1731, 390, 436, 1587, 1650, 1760, 1740, 1503, 938, 1162, 1776};
	    	 std::copy(newarr, newarr + 16, roots);
	      break;
	    				}

		case 18: //RMAT-21-8
	    				{
	    	unsigned int newarr[16] = {1608, 74, 1629, 386, 636, 1538, 1404, 1974, 84, 1854, 1867, 613, 1128, 346, 1146, 758};
	    	 std::copy(newarr, newarr + 16, roots);
	      break;
	    				}

		case 19: //RMAT-21-16
	    				{
	    	unsigned int newarr[16] = {724, 83, 1340, 149, 642, 1042, 1861, 1489, 1183, 99, 649, 98, 921, 1556, 1736, 75};
	    	 std::copy(newarr, newarr + 16, roots);
	      break;
	    				}


	    default:
	    	unsigned int newarr[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	    	 std::copy(newarr, newarr + 16, roots);
	    }



		while(roots_i <= 15){

//


//		int rootNode = 3;
//		VERBOSE(cout << "Enter root node: " << endl);
		rootNode = roots[roots_i];
//		cin >> rootNode;


		char method = 'f';
//		VERBOSE(cout << "Enter s for software, h for hybrid, f for FPGA:" << endl);
//		cin >> method;
		cout << "matrix ID : "  << matrixID << "PE Count : " <<hardwarePECount << "Method : " << method << "ROOTNODE : " << rootNode << endl;

		if (method == 'h')
			HybridBFS(matrixID, rootNode);
		else if (method == 's')
			SoftwareBFS(matrixID, rootNode);
		else if (method == 'f')
			HardwareBFS(matrixID, rootNode,roots_i);
		else
			cout << "unrecognized method: " << method << endl;

		roots_i++;


		}

	    //the average may not necessarily be integer
	    float sum_mteps = 0.00;
	    for (int i = 0; i < 16; ++i)
	    {
	        sum_mteps += mteps_record[i];
	    }
	    avg_mteps[matrixID] = ((float)sum_mteps)/16; //or cast sum to double before division



	    //the average may not necessarily be integer
	    float sum_time = 0.00;

	    for (int i = 0; i < 16; ++i)
	    {
	        sum_time += time_record[i];
	    }
	    avg_time[matrixID] = ((float)sum_time)/16; //or cast sum to double before division
	    float pwr_value = 2.32;
	    //std::cout << "-----------\n AVERAGE MTEPS = " << avg_mteps[matrixID] <<" MTEPS "<< std::endl;
	    //std::cout << " AVERAGE MTEPS/PWR = " << avg_mteps[matrixID]/pwr_value <<" MTEPS/W "<< std::endl;
	    //std::cout << " AVERAGE ExecTime = " << (float)(avg_time[matrixID] * 1000) << " ms \n ------------ "<< std::endl;

	    matrixID++;
	    if(matrixID < 19){
	    	goto beginning;
	    }
	    for(int i =0; i < 2; i++){
	    	switch(i) {
	    	case 0:
	    		{std::cout << "rmat-1-1-csc";
	    		break;}
	    	case 1:
	    		{std::cout << "rmat-1-2-csc";
	    		break;}
	    	case 2:
	    		{std::cout << "rmat-1-3-csc";
	    		break;}
	    	case 3:
	    		{std::cout << "rmat-1-4-csc";
	    		break;}
	    	case 4:
	    		{std::cout << "rmat-1-5-csc";
	    		break;}
	    	case 5:
	    		{std::cout << "rmat-1-6-csc";break;}
	    	case 6:
	    		{std::cout << "rmat-1-7-csc";break;}
	    	case 7:
	    		{std::cout << "rmat-2-1-csc";break;}
	    	case 8:
	    		{std::cout << "rmat-2-2-csc";break;}
	    	case 9:
	    		{std::cout << "rmat-2-3-csc";break;}
	    	case 10:
	    		{std::cout << "rmat-2-4-csc";break;}
	    	case 11:
	    		{std::cout << "rmat-2-5-csc";break;}
	    	case 12:
	    		{std::cout << "rmat-19-8-csc";break;}
	    	case 13:
	    		{std::cout << "rmat-19-16-csc";break;}
	    	case 14:
	    		{std::cout << "rmat-19-32-csc";break;}
	    	case 15:
	    		{std::cout << "rmat-20-8-csc";break;}
	    	case 16:
	    		{std::cout << "rmat-20-16-csc";break;}
	    	case 17:
	    		{std::cout << "rmat-20-32-csc";break;}
	    	case 18:
	    		{std::cout << "rmat-21-8-csc";break;}
	    	case 19:
	    		{std::cout<< "rmat-21-16-csc";break;}
	    	default:
	    		{std::cout << "Matrix not found!";break;}
	    	}

	    	std::cout << " -----\nAVERAGE MTEPS = " << avg_mteps[i] <<" MTEPS "<< std::endl;
	    	std::cout << " AVERAGE ExecTime = " << (float)(avg_time[i] * 1000) << " ms \n ------------ "<< std::endl;
	    }


		return 0;
}

/*
 void* operator new (size_t size)
 {
 cout << "size: " << size << endl;
 if(size % 32 != 0)
 size = size -(size%32) +32;

 void *p=malloc(size);
 if (p==0) {
 cout << "OUCHIES: " << size  << endl;
 throw std::bad_alloc(); // ANSI/ISO compliant behavior
 }

 return p;
 }

 void operator delete (void *p)
 {
 free(p);
 }
 */
