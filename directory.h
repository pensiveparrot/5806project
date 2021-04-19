#ifndef _DIRECTORY_H_
#define _DIRECTORY_H_
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>
#include <cstddef>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "vdifile.h"
#include "partition.h"
#include "ext2.h"
#include "inode.h"

struct Directory {
	uint32_t iNum;
	uint16_t recLen;
	uint8_t nameLen,fileType,name[1];
	int cursor;
	
	};

struct Directory *openDir(uint32_t iNum);
bool getNextDirent(struct Directory *d, uint32_t &iNum, char* name);
void rewindDir(struct Directory *d);
void closeDir(struct Directory *d);
uint32_t searchDir(struct ext2file* f, uint32_t iNum, char* target);
#endif
