//////////////////////////
//
//   Project     : Sparse BFS on Zedboard
//   File        : bfsoperation.cpp
// 
//   Created on: Feb 3, 2015   
//   Original Author: Yaman Umuroglu <yamanu@idi.ntnu.no> (https://github.com/maltanar/fpga-booleanring-bfs)
//   Modified on: March 10,2022
//	 Modified By: Kaan Olgu <kaan.olgu@bristol.ac.uk>
////////////////////////////////////////////////////////////////////////////

#include <string.h>
#include <iostream>
#include "bfsoperation.h"

using namespace std;

BFSOperation::BFSOperation(GraphMatrixData *graph)
{
	m_graph = graph;
	m_isConverged = false;
	m_resultCount = 0;

    assert(m_graph);

    // our implementation works only on full (unpartitioned) graphs
    // assert(m_graph->rows == m_graph->cols);

    // Changed this to not equal so to check whether it works because the col count is not equal to row count (e.g. 65536 != 65534 )
    //assert(m_graph->rows != m_graph->cols);

    m_graph = graph;
    m_resultVector = new DistVecElem[graph->rows];

    assert(m_resultVector);

    resetBFS();
}

BFSOperation::~BFSOperation()
{
    delete [] m_resultVector;
}

void BFSOperation::resetBFS()
{
    m_rootNode = 0;
    m_nextDistance = 0;
    m_resultCount = 0;
    memset(m_resultVector, -1, sizeof(DistVecElem) * m_graph->rows);
}

void BFSOperation::setRootNode(unsigned int number)
{
    assert(number < m_graph->rows);
    assert(m_nextDistance == 0);

    m_rootNode = number;
    m_isConverged = false;
}

unsigned int BFSOperation::getRootNode()
{
    return m_rootNode;
}

unsigned int BFSOperation::getNextDistance()
{
    return m_nextDistance;
}

DistVecElem *BFSOperation::getResultVector()
{
    return m_resultVector;
}

void BFSOperation::copyResultVector(unsigned int* dest) {
	for(unsigned int i = 0; i < m_graph->rows; i++) {
		dest[i] = m_resultVector[i];
	}
}

void BFSOperation::setNextDistance(unsigned int level) {
	m_nextDistance = level;
}

void BFSOperation::printResultVector() {
	cout << "Result vector contents: " << endl;
	for(unsigned int i = 0; i < m_graph->rows; i++) {
		if(m_resultVector[i] != -1) {
			//cout << "Element " << i << " = ";
			cout<< m_resultVector[i] << endl;
		}
	}

}
