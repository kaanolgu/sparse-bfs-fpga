//////////////////////////
//
//   Project     : Sparse BFS on Zedboard
//   File        : sdcard.cpp
// 
//   Created on: Feb 3, 2015   
//   Original Author: Yaman Umuroglu <yamanu@idi.ntnu.no> (https://github.com/maltanar/fpga-booleanring-bfs)
//   Modified on: March 10,2022
//	 Modified By: Kaan Olgu <kaan.olgu@bristol.ac.uk>
////////////////////////////////////////////////////////////////////////////
#include <malloc.h>
#include "sdcard.h"
#include <iostream>
#include <assert.h>

using namespace std;

FATFS fatfs;

WCHAR ff_convert(WCHAR wch, UINT dir) {
	if (wch < 0x80) {
		/* ASCII Char */
		return wch;
	}

	/* I don't support unicode it is too big! */
	return 0;
}

WCHAR ff_wtoupper(WCHAR wch) {
	if (wch < 0x80) {
		/* ASCII Char */
		if (wch >= 'a' && wch <= 'z') {
			wch &= ~0x20;
		}
		return wch;
	}

	/* I don't support unicode it is too big! */
	return 0;
}

void mount() {
	FRESULT Res = f_mount(&fatfs,"0:",0);

	if (Res != FR_OK)
		throw "Could not mount SD card.";
	else
		//cout << "SD card mounted" << endl;
		;
}

void unmount() {
	FRESULT Res = f_mount(&fatfs, "0:", 0);

	if (Res != FR_OK)
		throw "Could not unmount SD card.";
	else
		//cout << "SD card unmounted" << endl;
		;
}

void readFromSDCard(const char * fileName, unsigned int bufferBase) {
	cout << "Reading " << fileName << "..." << endl;
	unsigned int fileSize = getFileSize(fileName);
	readIntoBuffer(fileName, (char *) bufferBase, fileSize);
	cout << "fileSize: " << fileSize <<"bufferBase : " << bufferBase << " \n OK" << endl;
}

unsigned int getFileSize(const char *fileName) {
	FILINFO file_info;
	file_info.lfname = 0; // it was used to be file_info.lfname = 0

	if (f_stat(fileName, &file_info) != 0) {
		assert(0);
	}

	DWORD fil_size = file_info.fsize;

	return fil_size;
}

void readIntoBuffer(const char * fileName, char * buffer,
		unsigned int bufsize) {
	FIL fil;
	char *SD_File;

	FRESULT Res;

	UINT NumBytesRead;

	SD_File = (char *) fileName;

	Res = f_open(&fil, SD_File, FA_READ | FA_OPEN_EXISTING);
	if (Res)
		assert(0);

	Res = f_lseek(&fil, 0);
	if (Res)
		throw "Failed to seek opened file.";

	f_read(&fil, buffer, bufsize, &NumBytesRead);

	if (NumBytesRead != bufsize) {
		assert(0);
	}

	if (Res != 0) {
		assert(0);
	}

	Res = f_close(&fil);
	if (Res)
		assert(0);

}

