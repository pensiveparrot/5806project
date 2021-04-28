#include "inode.h"


//bool allocated = false;

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
//int32_t bSize = size << spbk.s_log_block.size;

int32_t fetchInode(struct ext2file *f, uint32_t iNum, struct Inode *buf)
{
    int32_t sb;
    void *buf2;
    uint8_t blocknum = 0;
    if(blocknum == 0)
    {
        PartitionSeek(f->p, 1024, SEEK_SET, f->vdi);
        PartitionRead(f->vdi, buf2, f->blocksize, f->p);
    }
    else if(blocknum > 0)
    {
        fetchblock(f, f->superblock->s_first_data_block + blocknum * f->superblock->s_blocks_per_group, buf2);
    }
    /*switch (blocknum){
    case 0:

    break;
    default:

    }*/

    /* if bgnum==0, then use partitionseekto offset 1024 then partitionread the superblock
     * if bgnum>0 then fetchblock(sb.s_first_data_block+bgnum*sb.s_blocks_per_group), the superblock will be the first 1K of that block.
     *
     *
     * */



    iNum -= 1;
    //struct ext2superblock *subb = new ext2superblock;
    //struct ext2file* f = new ext2file;
    struct ext2superblock *sbl = new ext2superblock;
    int32_t fetchedsb = fetchsuperblock(f, blocknum, sbl	);

    uint32_t groupnum = iNum / f->superblock->s_inodes_per_group;

    iNum %= f->superblock->s_inodes_per_group;

    uint32_t ipb = f->blocksize / sizeof(Inode);



    uint32_t b = f->bgdt->bg_inode_table;

    b += iNum / ipb;

    iNum %= ipb;
    struct Inode *tmp = new Inode[ipb];
    fetchblock(f, b, tmp);
    struct Inode answer = tmp[iNum];

    /*int32_t spbk = fetchsuperblock(*f, blocknum, buf);

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

    int32_t block = fetchBlock(block_num);*/


}

//int32_t fetchblock(int32_t blocknum

int32_t writeInode(struct ext2file *f, uint32_t iNum, struct Inode *buf)
{
    int32_t failure = 0;
    iNum -= 1;
    int32_t group = iNum / f->superblock->s_inodes_per_group;
    int32_t index = iNum % f->superblock->s_inodes_per_group;
    uint32_t *tmp = new uint32_t[f->blocksize];
    int32_t ipb = f->blocksize / f->superblock->s_inode_size;
    int32_t block = index / ipb;
    int32_t blockindex = index % ipb;
    failure = fetchblock(f, f->bgdt[group].bg_inode_table + block, (void *) tmp);
    if(failure == -1)
        return -1;
    memcpy(tmp + (blockindex * f->superblock->s_inode_size), buf, f->superblock->s_inode_size);
    failure = writeblock(f, f->bgdt[group].bg_inode_table + block, (void *)tmp);

    return failure;
}


bool InodeInUse(struct ext2file *f, uint32_t iNum)
{
    iNum -= 1;
    int32_t group = iNum / f->superblock->s_inodes_per_group;
    int32_t index = iNum % f->superblock->s_blocks_per_group;
    uint32_t ipb = f->blocksize / f->superblock->s_inode_size;
    int32_t block = index / ipb;
    int32_t byte = index / 8;
    int32_t bit = index % 8;
    uint32_t *tmp = new uint32_t[f->blocksize];
    fetchblock(f, f->bgdt[group].bg_inode_bitmap + block, (void *)tmp);
    if(tmp[byte] & (1 << (bit)))
        return true;
    return false;
}

uint32_t allocateInode(struct ext2file *f, int32_t group)
{
    //int32_t bSize = 1024 << f->superblock->s_log_block_size;
    /*if (InodeInUse(f, group) == false)
    {
        malloc(f->blocksize);
    }
    else
    {
        return 0;
        //not entirely sure how to do this
    }*/
    uint32_t inode;
    uint32_t *tmp = new uint32_t[f->blocksize];
    void* buf;
    void* buf2;
    uint8_t blocknum = 0;
    if(blocknum == 0)
    {
        PartitionSeek(f->p, 1024, SEEK_SET, f->vdi);
        PartitionRead(f->vdi, buf2, f->blocksize, f->p);
    }
    else if(blocknum > 0)
    {
        fetchblock(f, f->superblock->s_first_data_block + blocknum * f->superblock->s_blocks_per_group, buf2);
    }
    
    
	if (!InodeInUse(f, group)){
		if(group>0)
		{
			for(int i=0;i<=group-1;i++)
			{
				auto bitmaploc= f->bgdt[i].bg_inode_bitmap;
				uint32_t flag=-1;
				flag=fetchblock(f,blocknum,buf);
				if(flag<0)
				return flag;
				
				for(int j = 0; j < f->blocksize/sizeof(int);j++)
				{
					
					if(tmp[j]!= 0xff){
						for(int k=0;k<8;k++)
						{
							if(!tmp[k]>>k & 1U){
								inode=k+j*8+i*f->superblock->s_inodes_per_group+1;
								tmp[k]=1UL<<k;
								flag=writeblock(f,blocknum,buf);
								if(flag<0)
								return flag;
								}
							k=8;
							j=f->blocksize/sizeof(int);
							i=group;
							}
							
						
						}
					
					}
				
				
				}
			
				
			
			}
			
		if(inode<0)
		return -1;
		else{
			f->bgdt[(inode-1)/f->superblock->s_inodes_per_group].bg_free_inodes_count--;
			f->superblock->s_free_inodes_count--;
			}	
		return inode;
		
	}

    //return group;
}

int32_t freeInode(struct ext2file *f, uint32_t iNum)
{
	iNum-=1;
	auto group = iNum/f->superblock->s_inodes_per_group;
	auto inode = iNum%f->superblock->s_inodes_per_group;
	auto ipb = f->blocksize/f->superblock->s_inode_size;
	auto bit=inode%8;
	auto byte=inode/8; 
	auto block=inode/ipb;
	void* buf;
	fetchblock(f,f->bgdt[group].bg_inode_bitmap+block,buf);
	f->blocksize&=(1UL << bit);
	writeblock(f,f->bgdt[group].bg_inode_bitmap+block,buf);
	struct Inode *tmp = {0};
	writeInode(f,iNum,tmp);
	
	return 0;
}

/*void displayInode(struct Ext2File *f, uint32_t iNum, struct Inode *buf)
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
	
	std::cout << "File Version: " << GetFileVersionInfo(buf);
	/*
	std::cout << "ACL block: ";
	std::cout << "Direct Blocks: " ;
	std::cout << "Single Indirect Block: ";
	std::cout << "Double Indirect Block: ";
	std::cout << "Triple Indirect Block: ";
	*/

	//wasn't sure of the syntax, saw something about this on this site http://www.science.smith.edu/~nhowe/262/oldlabs/ext2.html


//}


