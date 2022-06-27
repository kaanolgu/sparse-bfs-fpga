//////////////////////////
//
//   Project     : Sparse BFS on Zedboard
//   File        : BitmapBFSOperation.h
// 
//   Created on: Feb 3, 2015   
//   Original Author: Yaman Umuroglu <yamanu@idi.ntnu.no> (https://github.com/maltanar/fpga-booleanring-bfs)
//
////////////////////////////////////////////////////////////////////////////

#ifndef BITMAPBFSOPERATION_H_
#define BITMAPBFSOPERATION_H_

#include <queue>
#include "bfsoperation.h"

class SimpleQueue {
public:
	SimpleQueue(unsigned int maxSize);
	~SimpleQueue();

	void push(unsigned int element);
	unsigned int pop();
	unsigned int size();
	bool isEmpty();

protected:
	unsigned int * m_queue;
	unsigned int m_head, m_tail;
};

class BitmapBFSOperation: public BFSOperation {
public:
	BitmapBFSOperation(GraphMatrixData * graph);
	virtual ~BitmapBFSOperation();

	virtual unsigned int step();
	virtual void resetBFS();
	virtual void setRootNode(unsigned int number);

	void rebuildFrontierFromDistVec();

protected:
	SimpleQueue * m_frontier;
	unsigned int * m_bitmap;
	unsigned int m_bitmapWordCount;

	// helper functions for visited bit set/test (inlined)
	void setBit(unsigned int ind);
	bool testBit(unsigned int ind);
};

#endif /* BITMAPBFSOPERATION_H_ */
