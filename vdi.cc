#include "vdifile.h"

struct VDIFile *VDIOpen( char *fn)
{
    //VDIHEADER header;

    int filedesc = open(fn, O_RDONLY);

    if(filedesc == -1)
        return NULL;

    else
    {
        struct VDIFile *file = (struct VDIFile *)malloc(sizeof(struct VDIFile));
        read(filedesc, &file->header, sizeof(file->header));
        file->transmapsize = file->header.cBlocks;
        file->transmapptr = new int[file->transmapsize];
        lseek(filedesc, /*header.offBlocks*/file->header.offBlocks, SEEK_SET);
        read(filedesc, file->transmapptr, sizeof(file->transmapsize));
        file->fd = filedesc;
        file->cursor = 0;
        return file;
    }


}
void VDIClose(struct VDIFile *f)
{

    delete[] f->transmapptr;
    close(f->fd);
}
off_t VDISeek(VDIFile *f, off_t offset, int anchor)
{
    uint8_t newpos;
    off_t location;
    switch(anchor)
    {
    case(SEEK_SET):

        newpos = offset;


        break;
    case(SEEK_CUR):

        newpos += offset;


        break;
    case(SEEK_END):

        newpos = offset + f->header.cbDisk;

        break;
    default:
        perror("seek");
        break;

    }
    if(newpos >= 0 && newpos <= f->header.cbDisk)
        newpos = f->cursor;
    return f->cursor;
}
ssize_t VDIRead(struct VDIFile *f, void *buf, size_t count)
{

    size_t bytesleft = count,

           bytesread = 0,
           virtualpage,
           offset,
           cursize,
           physicalpage,
           reallocation;
    //this->fd;
    while(bytesleft > 0)
    {
        virtualpage = f->cursor / f->header.cbBlock;
        offset = f->cursor % f->header.cbBlock;
        cursize = f->header.cbBlock - offset;
        if(cursize > bytesleft)
            cursize = bytesleft;
        physicalpage = f->transmapptr[virtualpage];
        //reallocation = physicalpage * f->header.cbBlock + offset;
        lseek(f->fd, reallocation + f->header.offData, SEEK_SET);
        ssize_t bytesjustread = 0;
        if(physicalpage >= 0xfffffffe)
            memset(buf, 0, cursize);
        else
        {
            lseek(f->fd, f->header.offData + offset, SEEK_SET);
            bytesjustread = read(f->fd, buf, cursize);
            if(bytesjustread != cursize)
                break;
        }
        f->cursor += cursize;
        buf += cursize;
        bytesleft -= cursize;
        bytesread += cursize;

    }
    return bytesread;
}

ssize_t VDIWrite(struct VDIFile *f, void *buf, size_t count)
{
    size_t bytesleft = count,

           byteswritten = 0,
           virtualpage,
           byteswrotenow,
           offset,
           cursize,
           physicalpage,
           reallocation;

    while(bytesleft > 0)
    {
        virtualpage = f->cursor / f->header.cbBlock;
        offset = f->cursor % f->header.cbBlock;
        cursize = f->header.cbBlock - offset;
        if(cursize > bytesleft)
            cursize = bytesleft;
        physicalpage = f->transmapptr[virtualpage];
        if(physicalpage >= 0xfffffffe)
        {
            uint8_t *tmp = new uint8_t[f->header.cbBlock];
            lseek(f->fd, 0, SEEK_END);
            write(f->fd, tmp, f->header.cbBlock);
            delete[] tmp;
        }
        f->map[virtualpage] = f->header.cBlocksAllocated;
        write(f->fd, f->map, sizeof(f->header.cbBlock));
        f->header.cBlocksAllocated++;
        write(f->fd, &f->header, sizeof(f->header));
        physicalpage = f->map[virtualpage];
        lseek(f->fd, f->header.offData + physicalpage * f->header.cbBlock + offset, SEEK_SET);
        byteswrotenow = write(f->fd, buf, cursize);
        if(byteswrotenow != cursize)
            break;
        buf += cursize;
        bytesleft -= cursize;
        byteswritten += cursize;
    }
    return byteswritten;
}
