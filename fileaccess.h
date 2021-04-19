#ifndef _FILE_ACCESS_H_
#define _FILE_ACCESS_H_
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
int32_t fbff(struct ext2file *f, uint32_t blocknum, void *buf);
int32_t wbtf(struct ext2file *f, uint32_t blocknum, void* buf);




#endif
