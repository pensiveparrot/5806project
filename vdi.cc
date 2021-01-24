#include "vdifile.h"
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
