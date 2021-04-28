	#include "fileaccess.h"
int32_t fbff(struct ext2file *f, uint32_t blocknum, void *buf){
	uint32_t* bList= new uint32_t[14];
	struct Inode *i = new struct Inode;
	auto epb = blocknum/sizeof(int);
	uint32_t bnum;
	if(blocknum<12){
		bList=i->i_block;
		goto direct;
		}
		else if(blocknum<12+epb)
		{
			blocknum-=12;
			fetchblock(f,i->i_block[12],buf);
			bList=(uint32_t*)buf;
			goto direct;
		}
		else if(blocknum<12+epb+(epb*epb)){
			blocknum-=12+epb;
			fetchblock(f,i->i_block[13],buf);
			bList=(uint32_t*)buf;
			goto dbl;
			}
		else{
			blocknum-=12-epb-(epb*epb);
			fetchblock(f,i->i_block[14],buf);
			bList=(uint32_t*)buf;
			goto triple;
			}
			triple:
			bnum=blocknum/(epb*epb);
			blocknum%=(epb*epb);
			fetchblock(f,bList[bnum],buf);
			dbl:
			bnum=blocknum/epb;
			blocknum%=epb;
			fetchblock(f,bList[bnum],buf);
			direct:
			fetchblock(f,bList[blocknum],buf);
	}
int32_t wbtf(struct ext2file *f, uint32_t blocknum, void* buf){
		uint32_t* bList= new uint32_t[14];
	struct Inode *i = new struct Inode;
	auto epb = blocknum/sizeof(int);
	uint32_t bnum;
	if(blocknum<12){
		bList=i->i_block;
		goto direct;
		}
		else if(blocknum<12+epb)
		{
			blocknum-=12;
			fetchblock(f,i->i_block[12],buf);
			bList=(uint32_t*)buf;
			goto direct;
		}
		else if(blocknum<12+epb+(epb*epb)){
			blocknum-=12+epb;
			fetchblock(f,i->i_block[13],buf);
			bList=(uint32_t*)buf;
			goto dbl;
			}
		else{
			blocknum-=12-epb-(epb*epb);
			fetchblock(f,i->i_block[14],buf);
			bList=(uint32_t*)buf;
			goto triple;
			}
			triple:
			bnum=blocknum/(epb*epb);
			blocknum%=(epb*epb);
			writeblock(f,bList[bnum],buf);
			dbl:
			bnum=blocknum/epb;
			blocknum%=epb;
			writeblock(f,bList[bnum],buf);
			direct:
			writeblock(f,bList[blocknum],buf);
	
	
	}
