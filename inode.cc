#include "incode.h"


//bool allocated = false;
int size = 1024;

//ik block sizes, blocks store 256
//1480576 data blocks, each file is 4GB in size

int32_t bSize = size << spbk.s_log_block.size;	

int32_t fetchInode(struct ext2File *f,uint32_t iNum, struct Inode *buf)
{

	int32_t spbk = fetchsuperblock(*f, blocknum, buf);

	//gets block size in bytes
	//int32_t bSize = size << spbk.s_log_block.size;	
	
	//off_t partition = PartitionSeek(*f, size, anchor, *f);
	//PartitionRead(*f, buf, partition, *p);
	//ext2Open(fn, 

	int32_t bkDT = fetchBGDT(*f, blocknum, bdgt);
	uint32_t bksPerGroup = spbk.s_blocks_per_group;
	uint32_t bksTotal = spbk.s_blocks_count;

	uint32_t bks = (bksPerGroup + bksTotal - 1) / bksTotal;
	//blocknum*blocksize

	int32_t block = fetchBlock(block_num);

	return Inode;

}

//int32_t fetchblock(int32_t blocknum 


int32_t writeInode(struct Ext2File *f,uint32_t iNum, struct Inode *buf)
{

}


bool int32_t inodeInUse(struct Ext2File *f,uint32_t iNum)
{
	bool inUse;

	

	return inUse;
}

uint32_t allocateInode(struct Ext2File *f,int32_t group)
{
	if (inodeInUse(f, group) == false){
		group = malloc(bsize);
		return group;
	}
	else{
		return 0;
		//not entirely sure how to do this
	}


	//return inodenumber;
}

int32_t freeInode(struct Ext2File *f,uint32_t iNum)
{

}

void displayInode(struct Ext2File *f, unint32_t iNum, struct Inode *buf)
{
	int32_t inodeToDisplay = fetchInode(struct Ext2File *f,uint32_t iNum, struct Inode *buf);

	std::cout << "Inode: " << iNum;
	//how do i display the offset?
	std::cout << "Mode: " << inodeToDisplay.i_mode;
	std::cout << "Size: " << inodeToDisplay.i_size;
	std::cout << "Blocks: " << inodeToDisplay.i_blocks;
	std::cout << "UID/GID: " << inodeToDisplay.i_uid;
	std::cout << "Links: " << inodeToDisplay.i_links_count;
	std::cout << "Time Created: " << inodeToDisplay.i_ctime;
	std::cout << "Last Access: " << inodeToDisplay.i_atime;
	std::cout << "Last Modification: " <<inodeToDisplay.i_mtime;
	std::cout << "Deleted: " << inodeToDisplay.i_dtime;
	std::cout << "Flags: " << inodeToDisplay.i_flags;
	std::cout << "File Version: ";
	std::cout << "ACL block: ";
	std::cout << "Direct Blocks: " ;
	std::cout << "Single Indirect Block: ";
	std::cout << "Double Indirect Block: ";
	std::cout << "Triple Indirect Block: ";


	//wasn't sure of the syntax, saw something about this on this site http://www.science.smith.edu/~nhowe/262/oldlabs/ext2.html 
	

}