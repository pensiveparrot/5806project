#include "ext2.h"

int32_t fetchblock(struct ext2file *f, uint32_t blocknum,void *buf){
	auto tmp = f->blocksize*blocknum;
	PartitionSeek(f->p,tmp,SEEK_SET,f->vdi);
	auto blocksread = PartitionRead(f->vdi,buf,f->blocksize,f->p);
	if(blocksread!=f->blocksize)
	return -1;
	return 0;
	}
	int32_t writeblock(struct ext2file *f, uint32_t blocknum,void *buf){
		auto tmp = f->blocksize*blocknum;
		PartitionSeek(f->p,tmp,SEEK_SET,f->vdi);
		auto blockswrote=PartitionWrite(f->vdi,buf,f->blocksize,f->p);
		if(blockswrote!=f->blocksize)
		return -1;
		return 0;
		}
		
int32_t fbff(struct ext2file* f, uint32_t blocknum, void* buf){
			
			
			
			
			}
int32_t fetchsuperblock(struct ext2file *f, uint32_t blocknum,struct ext2superblock *buf){
	if(blocknum==0){
	PartitionSeek(f->p,1024,SEEK_SET,f->vdi);
	PartitionRead(f->vdi,buf,1024,f->p);
	}
	else
	{
		PartitionSeek(f->p,blocknum*f->blocksize,SEEK_SET,f->vdi);
		PartitionRead(f->vdi,buf,1024,f->p);
		}
	if(f->superblock->s_magic != 0xef53)
	return -1;
	
	return 0;
	}
struct ext2file *ext2Open(char *fn, int32_t pNum){
	struct ext2file* ext2 = new ext2file;
	struct VDIFile* VDI = new VDIFile;
	struct PartitionEntry pentry;
	VDI=VDIOpen(fn);
	if(!VDI)
	return nullptr;
	struct ext2superblock* sb = new ext2superblock;
	fetchsuperblock(ext2,(uint32_t)0,sb);
	struct PartitionFile* popen = PartitionOpen(VDI,pentry);
	if(!popen)
	return nullptr;
	
	return ext2;
	}

void ext2close(struct ext2file *f){
	PartitionClose(f->p);
	VDIClose(f->vdi);
	delete f->superblock;
	delete f->bgdt;
	}

int32_t writesuperblock(struct ext2file *f, uint32_t blocknum, struct ext2superblock *sb){
	PartitionSeek(f->p,f->blocksize*blocknum,SEEK_SET,f->vdi);
	auto blockswrote =PartitionWrite(f->vdi,sb,f->blocksize,f->p);
	if(blockswrote!=f->blocksize)
	return -1;
	return 0;
	}
int32_t fetchBGDT(struct ext2file *f, uint32_t blocknum, struct ext2blockgroupdescriptor *bgdt){
	int boot;
	if(f->blocksize==1024)
	boot==1024;
	else
	boot=0;
	PartitionSeek(f->p,f->blocksize*blocknum+boot,SEEK_SET,f->vdi);
	return PartitionRead(f->vdi,bgdt,32*f->numBGs,f->p);
	
	}

int32_t writeBGDT(struct ext2file *f, uint32_t blocknum, struct ext2blockgroupdescriptor *bgdt){
    int boot;
    if(f->blocksize == 1024)
    boot == 2048;
    else
    boot == f->blocksize;


    ssize_t tmp;
    if(blocknum == 0) {
        PartitionSeek(f->p,boot, SEEK_SET,f->vdi);
        tmp = PartitionWrite(f->vdi,bgdt, 32*f->numBGs,f->p);
    }
    else
    {
        PartitionSeek(f->p,f->blocksize*blocknum, SEEK_SET,f->vdi);
        tmp = PartitionWrite(f->vdi,bgdt, 32*f->numBGs,f->p);
    }
    if(tmp < 0)
        {
			return -1;
			}
    return 0;
}
