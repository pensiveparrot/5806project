#ifndef _INODE_H_
#define _INODE_H_
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


struct Inode
{
    uint16_t i_mode;
    uint16_t i_uid;
    uint32_t i_size;
    uint32_t i_atime;
    uint32_t i_ctime;
    uint32_t i_mtime;
    uint32_t i_dtime;
    uint16_t i_gid;
    uint16_t i_links_count;
    uint32_t i_blocks;
    uint32_t i_flags;
    uint32_t i_osd1;
    uint32_t i_block[15];
    uint32_t i_generation;
    uint32_t i_file_acl;
    uint32_t i_sizeHigh;
    uint32_t i_faddr;
    uint16_t i_blocksHigh;
    uint16_t reserved16;
    uint16_t i_uidHigh;
    uint16_t i_gidHigh;
    uint32_t reserved32;
};


//int size = 1024;
int32_t fetchInode(struct ext2file *f, uint32_t iNum, struct Inode *buf);
int32_t fbff(struct ext2file *f, uint32_t blocknum, void *buf);
int32_t writeInode(struct ext2file *f, uint32_t iNum, struct Inode *buf);
int32_t writeInode(struct ext2file *f, uint32_t iNum, struct Inode *buf);
bool InodeInUse(struct ext2file *f, uint32_t iNum);
uint32_t allocateInode(struct ext2file *f, int32_t group);
int32_t freeInode(struct ext2file *f, uint32_t iNum);
void displayInode(struct ext2file *f, uint32_t iNum, struct Inode *buf);

#endif
