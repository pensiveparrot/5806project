//#include <cstddef>
#include "vdifile.h"
#include "debug.h"

int main(int argc, char *argv[])
{
	//struct VDIHEADER* header;
    debug dbg;
       uint8_t
        mbr[512];
    //VDIFile VDI(1024);
    struct VDIFile *f;
    f=VDIOpen(argv[1]);
    if(f)
    {
		 
        //buf[4096];
        //VDI.VDISeek(VDI.fd, 0, SEEK_END);
        //lseek(VDI.fd,0,SEEK_SET);
        //read(VDI.fd,buf,4096);
       // VDI.VDIRead(VDI.fd, buf, 512);
        /*std::cout<<"dump of VDI Header"<<std::endl;
        std::cout<<"Image Name:"<<VDI.header.szFileInfo<<std::endl;
         printf("Signature: 0x%08x\n",VDI.header.u32Signature);
        std::cout<<"version:"<<VDI.header.u32Version<<std::endl;
        std::cout<<"version:"<<VDI.header.szComment<<std::endl;*/

        /*printf("Image name: [%-64.64s]\n", VDI.header.szFileInfo);
        printf("Signature: 0x%08x\n", VDI.header.u32Signature);
        printf("Version: 0x%08x\n", VDI.header.u32Version);
        printf("Header size: 0x%08x  %d\n",VDI.header.postHeaderSize,VDI.header.postHeaderSize);
        printf("Image type: 0x%08x\n", VDI.header.u32Type);
        printf("Flags: 0x%08x\n", VDI.header.fFlags);*/
        /* printf("Virtual CHS: %d-%d-%d\n",VDI.header.cCylinders,
                VDI.header.cHeads,VDI.header.cSectors);*/
        /*std::cout << "Sector Size:" <<
         VDI.header.cbSector << std::endl;*/
        /*
        printf("Map offset: 0x%08x\n",VDI.header.offBlocks);*/
        /*printf("    Frame offset: 0x%08x  %d\n",f->header->dataOffset,
               f->header->dataOffset);
        printf("      Frame size: 0x%08x  %d\n",f->header->pageSize,
               f->header->pageSize);
        printf("Extra frame size: 0x%08x  %d\n",f->header->extraPageSize,
               f->header->extraPageSize);
        printf("    Total frames: 0x%08x  %d\n",f->header->nPagesTotal,
               f->header->nPagesTotal);
        printf("Frames allocated: 0x%08x  %d\n",f->header->nPagesAllocated,
               f->header->nPagesAllocated);*/
       // std::cout << "Disk Size: " << VDI.header.cbDisk << std::endl;
        /*printf("UUID: %s\n",uuid2ascii(&VDI.header.uuidCreate));
        printf("Last snap UUID: %s\n",uuid2ascii(&VDI.header.uuidModify));
        printf("Link UUID: %s\n",uuid2ascii(&VDI.header.uuidPrevImage));
        printf("Parent UUID: %s\n",uuid2ascii(&VDI.header.uuidPrevImageModify));*/
       // printf("Image comment:\n");
        std::cout<<"header"<<std::endl;
        dbg.displayBuffer((uint8_t *)(&f->header),400,0);
        std::cout<<std::endl<<"translation map"<<std::endl;
        dbg.displayBuffer((uint8_t*)(f->transmapptr),512,0);
        //bg.displayBuffer(buf, 512, 0);
        std::cout<<std::endl;
      VDISeek(f,256,SEEK_SET);
      VDIRead(f,mbr,256);
    dbg.displayBufferPage(mbr,64,190,256);
     VDIClose(f);
        //delete[] mbr;
    }

    return 0;
}

