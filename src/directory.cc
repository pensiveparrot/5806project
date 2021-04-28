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
		
uint32_t searchDir(struct ext2file* f, uint32_t iNum, char* target){
			struct Directory *d = new struct Directory;
			openDir(iNum);
			uint32_t indnum;
			char* name = new char[255];
			bool eof=true;
			while(eof){
				getNextDirent(d,indnum,name);
				if(strcmp(name,target)==0){
					delete[] name;
					closeDir(d);
					return indnum;
					}
				
				}
			closeDir(d);
			delete[] name;
			return 0;
			}
uint32_t traversePath(ext2file* f,char *path){
	int start=1;
	uint32_t len=strlen(path);
	char *i=new char[len];
	uint32_t inum=2;
	int end = start+1;
	while(start<len&&inum!=0)
	{
		if(end=='/')
		break;
		path[end] = 0;
		inum=searchDir(f,inum,i);
		start=end+1;
		}
	return inum;
	
	}


