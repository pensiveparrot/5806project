#ifndef _PARTITION_H_
#define _PARTITION_H_
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>
#include <cstddef>
#include <cstring>
#include <stdlib.h>
#include <iostream>
#include "vdifile.h"
struct PartitionEntry{
	static const int NUM_PARTITION_ENTRIES=4;
	static const int NUM_BYTES=16;
	uint8_t partitionEntries[NUM_PARTITION_ENTRIES][NUM_BYTES];

	};
	struct PartitionFile{
		size_t pstart;
		size_t psize;
		struct VDIFile *vdi;
		};
void SetPartition(struct VDIFile *f,struct PartitionEntry pentry);
struct PartitionFile* PartitionOpen(struct VDIFile *f,struct PartitionEntry pentry);
void PartitionClose(struct PartitionFile *p);
ssize_t PartitionRead(struct VDIFile *f,void *buf,size_t count,struct PartitionFile *p);
ssize_t PartitionWrite(struct VDIFile *f,void *buf, size_t count,struct PartitionFile *p);
off_t PartitionSeek(struct PartitionFile *p,off_t offset, int anchor,struct VDIFile *f);
#endif
