#include "incode.h"


//bool allocated = false;
int size = 1024;

//ik block sizes, blocks store 256
//1480576 data blocks, each file is 4GB in size


/*
 * THIS IS FOR FETCHINODE
 * inode is an array and part of it is in each different parts of the array.
you are given an inode number, inode 1 is 0
first thing subtract 1 from the number
figure out the block group one is in:
how many inodes in each group? s_blocks_inodes_

groupnum = inodenum divided by superblock.s_inodes_per_group
iNum%=sb.s_inodes_per_group
figure out which block has inode
ipb inodeperblock
ipb=blocksize/sizeof(inode)
inode is typically 128 bytes but dont hardcode	
similar for blocknode
b=bgdt[g].bg_inode_table
b+=iNum/ipb
iNum%=ipb climbing the block here
fetchblock(b,tmp) tmp is just a new inode[ipb]
then once its fetched then
inode=tmp[iNum];

the root inode is always number 2
so check the mode in octal (if you fetched inode right the mode would be 40755)
the size should always be 1 block so if its a 1k filesystem it'll be 1k(1024)
links field should be 4 or 5
*/
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
