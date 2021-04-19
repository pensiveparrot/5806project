#include "directory.h"
struct Directory *openDir(uint32_t iNum){
	struct Directory *dir= new struct Directory;
	struct ext2file *ext2 = new struct ext2file;
	struct Inode *in= new struct Inode;
	dir->cursor=0;
	dir->iNum=iNum;
	fetchInode(ext2,iNum,in);
	return dir;
	}
bool getNextDirent(struct Directory *d, uint32_t &iNum, char* name){
	struct Directory *dir= new struct Directory;
	struct Inode *in= new struct Inode;
	struct ext2file *ext2 = new struct ext2file;
	int32_t offset;
	void* buf;
	while(dir->cursor < in->i_size)
	{
		auto blocknum=dir->cursor / ext2->blocksize;
		offset=dir->cursor & ext2->blocksize;
		int32_t fetchflag=fbff(ext2,blocknum,buf);
		if(fetchflag==-1)
		return 0;
		
		}
		auto dirent = ext2->blocksize + offset;
		dir->cursor+=dir->recLen;
		if(dir->iNum!=0){
			iNum=dir->iNum;
			for(int i=0;i<dir->nameLen;i++)
			{
				name[i]=dir->name[i];
				}
			name[dir->nameLen]=0;
			return 1;
			}
			return 0;
	}
void rewindDir(struct Directory *d)
{
	d->cursor=0;
	
	}
	void closeDir(struct Directory *d){
		delete d;
		
		}


