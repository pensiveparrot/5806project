//#include <cstddef>
#include "vdifile.h"
#include "debug.h"

int main(int argc, char *argv[])
{
    debug dbg;
    uint8_t* buf= new uint8_t[4096];
    VDIFile VDI(512);
    bool ab = VDI.VDIOpen(argv[1]);
    if(ab == true)
    {
        //buf[4096];
        VDI.VDISeek(VDI.fd, 0, SEEK_SET);
        //lseek(VDI.fd,0,SEEK_SET);
        //read(VDI.fd,buf,4096);
        VDI.VDIRead(VDI.fd, buf, 4096);
        /*std::cout<<"dump of VDI Header"<<std::endl;
        std::cout<<"Image Name:"<<VDI.header.szFileInfo<<std::endl;
         printf("Signature: 0x%08x\n",VDI.header.u32Signature);
        std::cout<<"version:"<<VDI.header.u32Version<<std::endl;
        std::cout<<"version:"<<VDI.header.szComment<<std::endl;*/

        printf("Image name: [%-64.64s]\n", VDI.header.szFileInfo);
        printf("Signature: 0x%08x\n", VDI.header.u32Signature);
        printf("Version: 0x%08x\n", VDI.header.u32Version);
        printf("Header size: 0x%08x  %d\n",VDI.header.postHeaderSize,VDI.header.postHeaderSize);
        printf("Image type: 0x%08x\n", VDI.header.u32Type);
        printf("Flags: 0x%08x\n", VDI.header.fFlags);
        /* printf("Virtual CHS: %d-%d-%d\n",VDI.header.cCylinders,
                VDI.header.cHeads,VDI.header.cSectors);*/
        std::cout << "Sector Size:" <<
                  VDI.header.cbSector << std::endl;
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
        std::cout << "Disk Size: " << VDI.header.cbDisk << std::endl;
        /*printf("UUID: %s\n",uuid2ascii(&VDI.header.uuidCreate));
        printf("Last snap UUID: %s\n",uuid2ascii(&VDI.header.uuidModify));
        printf("Link UUID: %s\n",uuid2ascii(&VDI.header.uuidPrevImage));
        printf("Parent UUID: %s\n",uuid2ascii(&VDI.header.uuidPrevImageModify));*/
        printf("Image comment:\n");
        dbg.displayBuffer((uint8_t *)buf, 4096, 0);
        VDI.VDIClose(VDI.fd);
        delete[] buf;
    }

    return 0;
}

