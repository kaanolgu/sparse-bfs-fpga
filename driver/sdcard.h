//////////////////////////
//
//   Project     : Sparse BFS on Zedboard
//   File        : GraphManager-p2.cc
// 
//   Created on: Feb 3, 2015   
//   Original Author: Yaman Umuroglu <yamanu@idi.ntnu.no> (https://github.com/maltanar/fpga-booleanring-bfs)
//
////////////////////////////////////////////////////////////////////////////
#include "xparameters.h"	/* SDK generated parameters */
#include "xsdps.h"		/* SD device driver */
#include <stdio.h>
#include "ff.h" // It's in the bsp/ps7_cortexa9_0/libsrc/xilffs_v3_9/src/include/ff.h

void readFromSDCard(const char * fileName, unsigned int bufferBase);
void readIntoBuffer(const char * fileName, char * buffer, unsigned int bufsize);
unsigned int getFileSize(const char *fileName);
void mount();
void unmount();
