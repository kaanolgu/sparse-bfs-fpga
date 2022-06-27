//////////////////////////
//
//   Project     : Sparse BFS on Zedboard
//   File        : DecoupledTester.h
// 
//   Created on: Feb 3, 2015   
//   Original Author: Yaman Umuroglu <yamanu@idi.ntnu.no> (https://github.com/maltanar/fpga-booleanring-bfs)
//
////////////////////////////////////////////////////////////////////////////

#ifndef DECOUPLEDTESTER_H_
#define DECOUPLEDTESTER_H_

// TODO add a reset register
// TODO add controllable muxes for "protecting" the FIFOs from the outside

#define	BASE_OUTPUT_OFFSET	0x1000

class DecoupledTester {
public:
	DecoupledTester(unsigned int baseAddr);
	virtual ~DecoupledTester();

	unsigned int getInputFIFODataCount();
	unsigned int getOutputFIFODataCount();

	bool writeToSingle(unsigned int value);
	bool readFromSingle(unsigned int & value);
	bool readFromDouble(unsigned int & valueUpper, unsigned int & valueLower);

	void passthrough(unsigned int count, bool print = false);
	void readAndPrintAll(bool dbl=false);

protected:

	typedef enum {
		regOutFIFOWriteData = 0,
		regOutFIFOWritePulse = 1,
		regOutFIFOReadPulse = 2,
		regInFIFOWriteReady = 0,
		regInFIFOReadDataAvailable = 1,
		regInFIFOReadDataUpper32 = 2,
		regInFIFOReadDataLower32 = 5,
		regInputFIFODataCount = 3,
		regOutputFIFODataCount = 4
	} DecoupledTesterRegs;

	volatile unsigned int * m_inputRegs, * m_outputRegs;
	unsigned int m_fifoWriteCount, m_fifoReadCount;
};

#endif /* DECOUPLEDTESTER_H_ */
