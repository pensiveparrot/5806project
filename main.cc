 //#include <cstddef>
#include "vdifile.h"
#include "debug.h"
#include "partition.h"
#include "inode.h"
#include "directory.h"
#include "ext2.h"
#include "fileaccess.h"

ssize_t copyfile(char* src, const char* dst){
	uint32_t *tmp2= new uint32_t;
	ext2file *ext2 = new ext2file;
	ext2open(src, 0);
	if(!ext2open(src,0));
	return -1;
	uint32_t inode = traversePath(ext2,src);
	if(inode<=0){ 
		ext2close(ext2);
		return -1;
}
	ssize_t filedescriptor=open(dst,O_WRONLY|O_CREAT|O_TRUNC,0666);
	if(filedescriptor<0){
	ext2close(ext2);
	return -1;
}
	struct Inode *in=new struct Inode;
	fetchInode(ext2,0,in);
	int count=in->i_size;
	auto tmp=0;
	//uint32_t blocknum;
	while(count>0){
		int32_t flag;
		fbff(ext2,ext2->blocksize,in);
		if(count>ext2->blocksize)
			flag=write(filedescriptor,&tmp2,ext2->blocksize);			
			
		else
		flag=write(filedescriptor,&tmp2,count);
		if(flag<0)
		{
			delete[] tmp2;
			delete in;
			ext2close(ext2);
			return -1;
			
			}
			else
			count-=ext2->blocksize;
		
		
		}
		delete[] tmp2;
		delete in;
		ext2close(ext2);
		delete ext2;
		close(filedescriptor);
		return 1;


	}

int main(int argc, char *argv[])
{
    //struct VDIHEADER* header;
    debug dbg;
    /*uint8_t *
    mbr = new uint8_t[512];*/
    uint8_t mbr[512];
    //VDIFile VDI(1024);
    struct VDIFile *f;
    struct PartitionFile *p;
    f = VDIOpen(argv[1]);
    if(f)
    {
		std::string cmd;
		std::string dir;
		const char* onlycmd="copy";
		printf("input your desired command (possible commands: copy)\n");
		std::cin>>cmd;
		if(strcmp(cmd.c_str(),onlycmd)==0)
		{
			//char* dir;
			printf("correct command inputted.  please input the path/to/copy/to\n Do keep in mind there is no validation here so please type the directory correctly\n");
			std::cin>>dir;
			copyfile(argv[1],dir.c_str());
			
			}
		else
		{
			printf("input your desired command (possible commands: copy)\n");
			std::cin>>cmd;
			
			}
       /* 
        * printf("header\n");
        dbg.dumpvdiheader(&f->header);
        dbg.displayBuffer((uint8_t *)(&f->header), 400, 0);

        printf("translation map\n");
        dbg.displayBuffer((uint8_t *)(f->map), 512, 0);
        //bg.displayBuffer(buf, 512, 0);
        printf("mbr partition scheme\n");
        //VDISeek(f, 256, SEEK_SET);
        //tested partitonseek, works
        PartitionSeek(p, 256, SEEK_SET, f);
        tested partitionread, works
         * issue lies with displaybuffer or displaybufferpage which is printing invalid data
         * This seems to be unfixable with my current knowledge.  This is a reminder to ask Dr. Kramer before time is up to help again with this debugging func.
         * This suggestion that the read/seek working comes from no noticeable changes to the data outputted when going to that specific byte/bit(idk which it is but at 256).  This should be the case
         * since it is just using the functions made before.  There isn't any seg faults or invalid memory exceptions so it has to be the way its outputting instead of a data violation.
        PartitionRead(f, (void *)mbr, 256, p);
        //VDIRead(f, (void *)mbr, 256);
        dbg.displayBufferPage(mbr, 64, 190, 256);
        VDIClose(f);
        //delete[] mbr;
        */
        
    }

    return 0;
}
