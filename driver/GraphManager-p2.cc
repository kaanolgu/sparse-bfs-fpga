//////////////////////////
//
//   Project     : Sparse BFS on Zedboard
//   File        : GraphManager-p2.cc
// 
//   Created on: Feb 3, 2015   
//   Original Author: Yaman Umuroglu <yamanu@idi.ntnu.no> (https://github.com/maltanar/fpga-booleanring-bfs)
//   Modified on: March 10,2022
//	 Modified By: Kaan Olgu <kaan.olgu@bristol.ac.uk>
////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "sdcard.h"
void * loadMatrixP2(unsigned int id) {
switch(id) {
case 0:
	readFromSDCard("rmat-1-1-csc-2/rmat-1-1-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-1-1-csc-2/rmat-1-1-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-1-1-csc-2/rmat-1-1-csc-0-inds.bin", 273070080);
	readFromSDCard("rmat-1-1-csc-2/rmat-1-1-csc-1-meta.bin", 281038848);
	readFromSDCard("rmat-1-1-csc-2/rmat-1-1-csc-1-indptr.bin", 281040896);
	readFromSDCard("rmat-1-1-csc-2/rmat-1-1-csc-1-inds.bin", 285673472);
	readFromSDCard("rmat-1-1-csc-2/config.bin", 268435456);

break;
case 1:
	readFromSDCard("rmat-1-2-csc-2/rmat-1-2-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-1-2-csc-2/rmat-1-2-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-1-2-csc-2/rmat-1-2-csc-0-inds.bin", 270632960);
	readFromSDCard("rmat-1-2-csc-2/rmat-1-2-csc-1-meta.bin", 271562752);
	readFromSDCard("rmat-1-2-csc-2/rmat-1-2-csc-1-indptr.bin", 271564800);
	readFromSDCard("rmat-1-2-csc-2/rmat-1-2-csc-1-inds.bin", 273760256);
	readFromSDCard("rmat-1-2-csc-2/config.bin", 268435456);

break;
case 2:
	readFromSDCard("rmat-1-3-csc-2/rmat-1-3-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-1-3-csc-2/rmat-1-3-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-1-3-csc-2/rmat-1-3-csc-0-inds.bin", 270141440);
	readFromSDCard("rmat-1-3-csc-2/rmat-1-3-csc-1-meta.bin", 272142336);
	readFromSDCard("rmat-1-3-csc-2/rmat-1-3-csc-1-indptr.bin", 272144384);
	readFromSDCard("rmat-1-3-csc-2/rmat-1-3-csc-1-inds.bin", 273848320);
	readFromSDCard("rmat-1-3-csc-2/config.bin", 268435456);

break;
case 3:
	readFromSDCard("rmat-1-4-csc-2/rmat-1-4-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-1-4-csc-2/rmat-1-4-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-1-4-csc-2/rmat-1-4-csc-0-inds.bin", 268441600);
	readFromSDCard("rmat-1-4-csc-2/rmat-1-4-csc-1-meta.bin", 268525568);
	readFromSDCard("rmat-1-4-csc-2/rmat-1-4-csc-1-indptr.bin", 268527616);
	readFromSDCard("rmat-1-4-csc-2/rmat-1-4-csc-1-inds.bin", 268531712);
	readFromSDCard("rmat-1-4-csc-2/config.bin", 268435456);

break;
case 4:
	readFromSDCard("rmat-1-5-csc-2/rmat-1-5-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-1-5-csc-2/rmat-1-5-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-1-5-csc-2/rmat-1-5-csc-0-inds.bin", 268472320);
	readFromSDCard("rmat-1-5-csc-2/rmat-1-5-csc-1-meta.bin", 268730368);
	readFromSDCard("rmat-1-5-csc-2/rmat-1-5-csc-1-indptr.bin", 268732416);
	readFromSDCard("rmat-1-5-csc-2/rmat-1-5-csc-1-inds.bin", 268767232);
	readFromSDCard("rmat-1-5-csc-2/config.bin", 268435456);

break;
case 5:
	readFromSDCard("rmat-1-6-csc-2/rmat-1-6-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-1-6-csc-2/rmat-1-6-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-1-6-csc-2/rmat-1-6-csc-0-inds.bin", 268482560);
	readFromSDCard("rmat-1-6-csc-2/rmat-1-6-csc-1-meta.bin", 268595200);
	readFromSDCard("rmat-1-6-csc-2/rmat-1-6-csc-1-indptr.bin", 268597248);
	readFromSDCard("rmat-1-6-csc-2/rmat-1-6-csc-1-inds.bin", 268642304);
	readFromSDCard("rmat-1-6-csc-2/config.bin", 268435456);

break;
case 6:
	readFromSDCard("rmat-1-7-csc-2/rmat-1-7-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-1-7-csc-2/rmat-1-7-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-1-7-csc-2/rmat-1-7-csc-0-inds.bin", 268896256);
	readFromSDCard("rmat-1-7-csc-2/rmat-1-7-csc-1-meta.bin", 269150208);
	readFromSDCard("rmat-1-7-csc-2/rmat-1-7-csc-1-indptr.bin", 269152256);
	readFromSDCard("rmat-1-7-csc-2/rmat-1-7-csc-1-inds.bin", 269611008);
	readFromSDCard("rmat-1-7-csc-2/config.bin", 268435456);

break;
case 7:
	readFromSDCard("rmat-2-1-csc-2/rmat-2-1-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-2-1-csc-2/rmat-2-1-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-2-1-csc-2/rmat-2-1-csc-0-inds.bin", 275224576);
	readFromSDCard("rmat-2-1-csc-2/rmat-2-1-csc-1-meta.bin", 307603456);
	readFromSDCard("rmat-2-1-csc-2/rmat-2-1-csc-1-indptr.bin", 307605504);
	readFromSDCard("rmat-2-1-csc-2/rmat-2-1-csc-1-inds.bin", 314392576);
	readFromSDCard("rmat-2-1-csc-2/config.bin", 268435456);

break;
case 8:
	readFromSDCard("rmat-2-2-csc-2/rmat-2-2-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-2-2-csc-2/rmat-2-2-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-2-2-csc-2/rmat-2-2-csc-0-inds.bin", 270264320);
	readFromSDCard("rmat-2-2-csc-2/rmat-2-2-csc-1-meta.bin", 327084032);
	readFromSDCard("rmat-2-2-csc-2/rmat-2-2-csc-1-indptr.bin", 327086080);
	readFromSDCard("rmat-2-2-csc-2/rmat-2-2-csc-1-inds.bin", 328912896);
	readFromSDCard("rmat-2-2-csc-2/config.bin", 268435456);

break;
case 9:
	readFromSDCard("rmat-2-3-csc-2/rmat-2-3-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-2-3-csc-2/rmat-2-3-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-2-3-csc-2/rmat-2-3-csc-0-inds.bin", 276324352);
	readFromSDCard("rmat-2-3-csc-2/rmat-2-3-csc-1-meta.bin", 287479808);
	readFromSDCard("rmat-2-3-csc-2/rmat-2-3-csc-1-indptr.bin", 287481856);
	readFromSDCard("rmat-2-3-csc-2/rmat-2-3-csc-1-inds.bin", 295368704);
	readFromSDCard("rmat-2-3-csc-2/config.bin", 268435456);

break;
case 10:
	readFromSDCard("rmat-2-4-csc-2/rmat-2-4-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-2-4-csc-2/rmat-2-4-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-2-4-csc-2/rmat-2-4-csc-0-inds.bin", 272801792);
	readFromSDCard("rmat-2-4-csc-2/rmat-2-4-csc-1-meta.bin", 278972416);
	readFromSDCard("rmat-2-4-csc-2/rmat-2-4-csc-1-indptr.bin", 278974464);
	readFromSDCard("rmat-2-4-csc-2/rmat-2-4-csc-1-inds.bin", 283338752);
	readFromSDCard("rmat-2-4-csc-2/config.bin", 268435456);

break;
case 11:
	readFromSDCard("rmat-2-5-csc-2/rmat-2-5-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-2-5-csc-2/rmat-2-5-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-2-5-csc-2/rmat-2-5-csc-0-inds.bin", 274204672);
	readFromSDCard("rmat-2-5-csc-2/rmat-2-5-csc-1-meta.bin", 277577728);
	readFromSDCard("rmat-2-5-csc-2/rmat-2-5-csc-1-indptr.bin", 277579776);
	readFromSDCard("rmat-2-5-csc-2/rmat-2-5-csc-1-inds.bin", 283346944);
	readFromSDCard("rmat-2-5-csc-2/config.bin", 268435456);

break;
case 12:
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-0-inds.bin", 270512128);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-1-meta.bin", 280309760);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-1-indptr.bin", 280311808);
	readFromSDCard("rmat-19-8-csc-2/rmat-19-8-csc-1-inds.bin", 282386432);
	readFromSDCard("rmat-19-8-csc-2/config.bin", 268435456);

break;
case 13:
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-0-inds.bin", 270516224);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-1-meta.bin", 290091008);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-1-indptr.bin", 290093056);
	readFromSDCard("rmat-19-16-csc-2/rmat-19-16-csc-1-inds.bin", 292171776);
	readFromSDCard("rmat-19-16-csc-2/config.bin", 268435456);

break;
case 14:
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-0-inds.bin", 270534656);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-1-meta.bin", 309626880);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-1-indptr.bin", 309628928);
	readFromSDCard("rmat-19-32-csc-2/rmat-19-32-csc-1-inds.bin", 311726080);
	readFromSDCard("rmat-19-32-csc-2/config.bin", 268435456);

break;
case 15:
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-0-inds.bin", 272617472);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-1-meta.bin", 292229120);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-1-indptr.bin", 292231168);
	readFromSDCard("rmat-20-8-csc-2/rmat-20-8-csc-1-inds.bin", 296411136);
	readFromSDCard("rmat-20-8-csc-2/config.bin", 268435456);

break;
case 16:
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-0-inds.bin", 272601088);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-1-meta.bin", 311777280);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-1-indptr.bin", 311779328);
	readFromSDCard("rmat-20-16-csc-2/rmat-20-16-csc-1-inds.bin", 315942912);
	readFromSDCard("rmat-20-16-csc-2/config.bin", 268435456);

break;
case 17:
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-0-inds.bin", 272617472);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-1-meta.bin", 350871552);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-1-indptr.bin", 350873600);
	readFromSDCard("rmat-20-32-csc-2/rmat-20-32-csc-1-inds.bin", 355053568);
	readFromSDCard("rmat-20-32-csc-2/config.bin", 268435456);

break;
case 18:
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-0-inds.bin", 276799488);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-1-meta.bin", 316008448);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-1-indptr.bin", 316010496);
	readFromSDCard("rmat-21-8-csc-2/rmat-21-8-csc-1-inds.bin", 324372480);
	readFromSDCard("rmat-21-8-csc-2/config.bin", 268435456);

break;
case 19:
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-0-meta.bin", 268436480);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-0-indptr.bin", 268437504);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-0-inds.bin", 276826112);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-1-meta.bin", 355182592);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-1-indptr.bin", 355184640);
	readFromSDCard("rmat-21-16-csc-2/rmat-21-16-csc-1-inds.bin", 363573248);
	readFromSDCard("rmat-21-16-csc-2/config.bin", 268435456);

break;
default:
std::cout << "Matrix not found!" << std::endl; return (void*)0;
}
 return (void *)268435456;
}


const char * getMatrixNameP2(unsigned int id) {
switch(id) {
case 0:
  return "rmat-1-1-csc";
case 1:
  return "rmat-1-2-csc";
case 2:
  return "rmat-1-3-csc";
case 3:
  return "rmat-1-4-csc";
case 4:
  return "rmat-1-5-csc";
case 5:
  return "rmat-1-6-csc";
case 6:
  return "rmat-1-7-csc";
case 7:
  return "rmat-2-1-csc";
case 8:
  return "rmat-2-2-csc";
case 9:
  return "rmat-2-3-csc";
case 10:
  return "rmat-2-4-csc";
case 11:
  return "rmat-2-5-csc";
case 12:
  return "rmat-19-8-csc";
case 13:
  return "rmat-19-16-csc";
case 14:
  return "rmat-19-32-csc";
case 15:
  return "rmat-20-8-csc";
case 16:
  return "rmat-20-16-csc";
case 17:
  return "rmat-20-32-csc";
case 18:
  return "rmat-21-8-csc";
case 19:
  return "rmat-21-16-csc";
default:
return "Matrix not found!";
}}
