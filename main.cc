//#include <cstddef>
#include <bit>
#include "vdifile.h"
#include "debug.h"


VDIFile::VDIFile(int tmapsize)
{
    transmapsize = tmapsize;
    transmapptr = new int[transmapsize];
    this->cursor = 0;
}
int VDIFile::VDIOpen(char *fn)
{


    this->fd = open(fn, O_RDONLY);

    if(this->fd == -1)
        return false;
    else
    {
        this->transmapsize = header.cBlocks;
        //lseek(fd, 0, SEEK_SET);
        read(this->fd, &header, sizeof(header));
        this->map = new int[transmapsize];
        lseek(this->fd, header.offBlocks, SEEK_SET);
        read(this->fd, map, transmapsize * sizeof(int));


    }
    return this->fd;
    //this->cursor = 0;
}
void VDIFile::VDIClose(int fd)
{
    fd = this->fd;
    close(fd);
}
off_t VDIFile::VDISeek(int fd, off_t offset, int anchor)
{
    whence = anchor;
    fd = this->fd;
    off_t location;
    switch(whence)
    {
    case(SEEK_SET):
        //location = lseek(fd, offset, anchor);
        //if(location < 0) return 1;
        this->cursor = offset;
        break;
    case(SEEK_CUR):
        //location = lseek(fd, offset, anchor);
        //if(location < 0) return 1;
        this->cursor += offset;
        break;
    case(SEEK_END):
        //location = lseek(fd, offset, anchor);
        //if(location < 0) return 1;
        this->cursor = offset + this->fileSize;
        break;
    default:
        perror("seek");
        break;

    }
    return this->cursor;

    //return lseek(fd,offset,anchor);
}
ssize_t VDIFile::VDIRead(int fd, void *buf, size_t count)
{

    size_t bytesleft = count,

           bytesread = 0,
           virtualpage,
           offset,
           physicalpage,
           reallocation;
    fd = this->fd;
    while(bytesleft > 0)
    {
        virtualpage = cursor / this->header.cbBlock;
        offset = cursor % this->header.cbBlock;
        physicalpage = this->transmapptr[virtualpage];
        reallocation = physicalpage * this->header.cbBlock + offset;
        lseek(fd, reallocation + this->header.offData, SEEK_SET);
        ssize_t bytesjustread = 0;
        if(reallocation >= 0)
        {
            size_t bytestoread = 0;
            if(count < this->header.cbBlock)
                bytestoread = count;
            else
                bytestoread = this->header.cbBlock;

            bytesjustread = read(fd, (uint8_t *)buf + bytesread, bytestoread);
        }
        else
        {
            for(int i = 0; i > this->header.cbBlock; i++)
            {
                *(static_cast<uint8_t *>(buf) + (bytesread + bytesjustread)) = '0';
                bytesjustread++;
            }
        }
        if(bytesjustread < 0)
            return -1;
        bytesread += bytesjustread;
        bytesleft -= bytesjustread;
        VDISeek(fd, bytesjustread, SEEK_CUR);

    }

    return bytesread;


}

ssize_t VDIFile::VDIWrite(int fd, void *buf, size_t count)
{
    /* fd = this->fd;
     ssize_t byte;
     size_t bytesleft = count;
     while(bytesleft > 0)
     {
         byte = write(fd, buf, bytesleft);
         bytesleft--;
     }

     return byte;*/
    fd = this->fd;
    size_t bytesleft = count,

           byteswrote = 0,
           byteswrotenow,
           virtualpage,
           bytestowrite,
           offset,
           physicalpage,
           reallocation;
    while(bytesleft > 0)
    {
        offset = cursor % this->header.cbBlock;
        virtualpage = cursor / this->header.cbBlock;
        physicalpage = this->transmapptr[virtualpage];
        reallocation = physicalpage * this->header.cbBlock + offset;
        lseek(fd, reallocation + this->header.offData, SEEK_SET);
        byteswrotenow = 0;
        if(reallocation < 0)
        {
            lseek(fd, 0, SEEK_END);
            uint8_t *buf2 = new uint8_t[this->header.cbBlock];
            write(fd, buf2, this->header.cbBlock);
            delete[] buf2;
            physicalpage = this->header.cBlocksAllocated;
            this->header.cBlocksAllocated++;
            this->transmapptr[virtualpage] = physicalpage;
            lseek(fd, 0, SEEK_SET);
            write(fd, &this->header, sizeof(this->header));
            lseek(fd, this->header.offBlocks, SEEK_SET);
            write(fd, this->transmapptr, sizeof(uint32_t)*this->header.cbBlock);


        }
        if(count < this->header.cbBlock)
            bytestowrite = count;
        else
            bytestowrite = this->header.cbBlock;
        byteswrotenow = write(fd, static_cast<uint8_t*>(buf) + byteswrote, bytestowrite);
        byteswrote += byteswrotenow;
        bytesleft -= byteswrotenow;
        VDISeek(fd, byteswrotenow, SEEK_CUR);
    }
    return byteswrote;
}

int main(int argc, char *argv[])
{
    debug dbg;
    uint8_t buf[4096];
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
        std::cout << "Header size: 0x" << VDI.header.cbHeader << std::endl;
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
    }

    return 0;
}
void debug::displayBufferPage(uint8_t *buf, uint32_t count, uint32_t skip, uint64_t offset)
{
    std::cout << "value in hex\n";
    int c = 0;
    for(int i = skip; i <= skip + count; i++)
    {
        if(skip <= i && i < skip + count)
        {
            uint8_t bytes = buf[i];
            std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)bytes << " ";
        }
        else
        {
            std::cout << std::endl;
            break;
        }

    }
    c++;
    if(c % 16 == 0)
        std::cout << std::endl;

    std::cout << "value in ascii\n";
    for (int j = skip; j <= count; j++)
    {
        if (skip <= j && j < skip + count)
        {
            uint8_t bytes = buf[j];
            if (isprint(int(bytes)))
            {
                std::cout << bytes << "";
            }
            else
            {
                std::cout << " ";
            }
        }
        else
        {
            std::cout << std::endl;
            break;
        }
    }
}


void debug::displayBuffer(uint8_t *buf, uint32_t count, uint64_t offset)
{
    int counter = 0;
    while(count > 0)
    {
        if(count > 256)
        {
            displayBufferPage(buf, 256, counter, offset);
            counter += 256;
            count -= 256;
            offset += 256;
        }
        else
        {
            displayBufferPage(buf, count, counter, offset);
            count = 0;
        }


    }

}
