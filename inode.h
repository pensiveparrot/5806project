#include "incode.cc"


int size = 1024;
int32_t bSize = size << spbk.s_log_block.size;
int32_t fetchInode(struct ext2File *f,uint32_t iNum, struct Inode *buf);
int32_t writeInode(struct Ext2File *f,uint32_t iNum, struct Inode *buf);
int32_t writeInode(struct Ext2File *f,uint32_t iNum, struct Inode *buf);
bool int32_t inodeInUse(struct Ext2File *f,uint32_t iNum);
uint32_t allocateInode(struct Ext2File *f,int32_t group);
int32_t freeInode(struct Ext2File *f,uint32_t iNum);
void displayInode(struct Ext2File *f, unint32_t iNum, struct Inode *buf);