//////////////////////////
//
//   Project     : Sparse BFS on Zedboard
//   File        : GraphManager-p1.cc
// 
//   Created on: Feb 3, 2015   
//   Original Author: Yaman Umuroglu <yamanu@idi.ntnu.no> (https://github.com/maltanar/fpga-booleanring-bfs)
//
////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "sdcard.h"
void * loadMatrixP1(unsigned int id) {
switch(id) {
case 0:
	readFromSDCard("rmat-19-8-csc-1/rmat-19-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-8-csc-1/rmat-19-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-8-csc-1/rmat-19-8-csc-0-inds.bin", 270512128);
	readFromSDCard("rmat-19-8-csc-1/config.bin", 268435456);

break;
case 1:
	readFromSDCard("rmat-19-16-csc-1/rmat-19-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-16-csc-1/rmat-19-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-16-csc-1/rmat-19-16-csc-0-inds.bin", 270516224);
	readFromSDCard("rmat-19-16-csc-1/config.bin", 268435456);

break;
case 2:
	readFromSDCard("rmat-19-32-csc-1/rmat-19-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-32-csc-1/rmat-19-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-32-csc-1/rmat-19-32-csc-0-inds.bin", 270534656);
	readFromSDCard("rmat-19-32-csc-1/config.bin", 268435456);

break;
case 3:
	readFromSDCard("rmat-20-8-csc-1/rmat-20-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-8-csc-1/rmat-20-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-8-csc-1/rmat-20-8-csc-0-inds.bin", 272617472);
	readFromSDCard("rmat-20-8-csc-1/config.bin", 268435456);

break;
case 4:
	readFromSDCard("rmat-20-16-csc-1/rmat-20-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-16-csc-1/rmat-20-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-16-csc-1/rmat-20-16-csc-0-inds.bin", 272601088);
	readFromSDCard("rmat-20-16-csc-1/config.bin", 268435456);

break;
case 5:
	readFromSDCard("rmat-20-32-csc-1/rmat-20-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-32-csc-1/rmat-20-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-32-csc-1/rmat-20-32-csc-0-inds.bin", 272617472);
	readFromSDCard("rmat-20-32-csc-1/config.bin", 268435456);

break;
case 6:
	readFromSDCard("rmat-20-64-csc-1/rmat-20-64-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-64-csc-1/rmat-20-64-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-64-csc-1/rmat-20-64-csc-0-inds.bin", 272631808);
	readFromSDCard("rmat-20-64-csc-1/config.bin", 268435456);

break;
case 7:
	readFromSDCard("rmat-21-8-csc-1/rmat-21-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-8-csc-1/rmat-21-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-8-csc-1/rmat-21-8-csc-0-inds.bin", 276799488);
	readFromSDCard("rmat-21-8-csc-1/config.bin", 268435456);

break;
case 8:
	readFromSDCard("rmat-21-16-csc-1/rmat-21-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-16-csc-1/rmat-21-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-16-csc-1/rmat-21-16-csc-0-inds.bin", 276826112);
	readFromSDCard("rmat-21-16-csc-1/config.bin", 268435456);

break;
case 9:
	readFromSDCard("rmat-21-31-csc-1/rmat-21-31-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-31-csc-1/rmat-21-31-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-31-csc-1/rmat-21-31-csc-0-inds.bin", 276826112);
	readFromSDCard("rmat-21-31-csc-1/config.bin", 268435456);

break;
default:
std::cout << "Matrix not found!" << std::endl; return (void*)0;
}
 return (void *)268435456;
}


const char * getMatrixNameP1(unsigned int id) {
switch(id) {
case 0:
  return "rmat-19-8-csc";
case 1:
  return "rmat-19-16-csc";
case 2:
  return "rmat-19-32-csc";
case 3:
  return "rmat-20-8-csc";
case 4:
  return "rmat-20-16-csc";
case 5:
  return "rmat-20-32-csc";
case 6:
  return "rmat-20-64-csc";
case 7:
  return "rmat-21-8-csc";
case 8:
  return "rmat-21-16-csc";
case 9:
  return "rmat-21-31-csc";
default:
return "Matrix not found!";
}}
