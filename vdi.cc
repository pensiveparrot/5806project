#include "vdifile.h"

struct VDIFile *VDIOpen(char *fn)
{
    //VDIHEADER header;

    int filedesc = open(fn, O_RDONLY);
    try
    {
        if(filedesc == -1)
            throw filedesc;
        struct VDIFile *file = new VDIFile;
        try
        {
            if(file == nullptr)
                throw file;
            file->fd = filedesc;
            read(file->fd, &file->header, sizeof(file->header));
            file->transmapsize = file->header.cBlocks;
            file->map = new int[file->transmapsize];
            lseek(file->fd, /*header.offBlocks*/file->header.offBlocks, SEEK_SET);
            read(file->fd, file->map, file->transmapsize * sizeof(int));
            //file->fd = filedesc;
            file->cursor = 0;
            return file;
        }
        catch(struct VDIFile *file)
        {
            std::cout << "invalid file in VDIOpen";
            return nullptr;
        }
    }
    catch(int filedesc)
    {
        std::cout << "invalid filedesc in VDIOpen";
        return nullptr;
    }



    //struct VDIFile* file = (struct VDIFile*)malloc(sizeof(struct VDIFile));




    return nullptr;

}
void VDIClose(struct VDIFile *f)
{

    delete[] f->map;
    close(f->fd);
    delete f;
}
off_t VDISeek(VDIFile *f, off_t offset, int anchor)
{
    off_t newpos;
    std::cout << "offset " << offset << std::endl;
    std::cout << "disk " << f->header.cbDisk << std::endl;
    if(anchor == SEEK_SET)
        newpos = offset;
    else if(anchor == SEEK_CUR)
        newpos = f->cursor + offset;
    else if(anchor == SEEK_END)
        newpos = offset + f->header.cbDisk;
    else
        newpos = f->cursor;
    if(newpos >= 0 && newpos <= f->header.cbDisk)
        f->cursor = newpos;
    return f->cursor;
}
ssize_t VDIRead(struct VDIFile *f, void *buf, size_t count)
{

    size_t nbytes = count,
           nread,
           bytesread = 0,
           vpagenum,
           voffset,
           cursize,
           ppagenum;
    //reallocation;
    //this->fd;

    while(nbytes > 0)
    {
        vpagenum = f->cursor / f->header.cbBlock;
        voffset = f->cursor % f->header.cbBlock;
        cursize = f->header.cbBlock - voffset;
        if(cursize > nbytes)
            cursize = nbytes;
        ppagenum = f->map[vpagenum];
        if(ppagenum >= 0xfffffffe)
            memset(buf, 0, cursize);
        else
        {
            lseek(f->fd, f->header.offData + (ppagenum * f->header.cbBlock + voffset), SEEK_SET);
            nread = read(f->fd, buf, cursize);
            if(nread != cursize)
                break;

        }
        f->cursor += cursize;
        buf += cursize;
        nbytes -= cursize;
        nread += cursize;

    }
    /*while(bytesleft > 0)
     {
         virtualpage = f->cursor / f->header.cbBlock;
         offset = f->cursor % f->header.cbBlock;
         cursize = f->header.cbBlock - offset;
         if(cursize > bytesleft)
             cursize = bytesleft;
         physicalpage = f->map[virtualpage];
         reallocation = physicalpage * f->header.cbBlock + offset;
         lseek(f->fd, reallocation + f->header.offData, SEEK_SET);
         if(physicalpage >= 0){
             size_t bytestoread=0;
         if(count<f->header.cbBlock)
         bytestoread=f->header.cbBlock;
         lseek(f->fd, f->header.offData + offset, SEEK_SET);
         cursize = read(f->fd, buf, sizeof(cursize));

    }else{
        for(int i=0;i>f->header.cbBlock;i++){
            *(static_cast<uint8_t*>(buf)+(bytesread+cursize))='0';
            cursize++;
            }

        }
        if(cursize<0)
        return -1;
         //buf += cursize;
         bytesread += cursize;
         bytesleft -= cursize;
        VDISeek(f,offset,SEEK_CUR);

     }*/
    return nread;
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
        physicalpage = f->map[virtualpage];
        if(physicalpage >= 0xfffffffe)
        {
            uint8_t *tmp = new uint8_t[f->header.cbBlock];
            lseek(f->fd, 0, SEEK_END);
            write(f->fd, tmp, f->header.cbBlock);
            delete[] tmp;
            f->map[virtualpage] = f->header.cBlocksAllocated;
            lseek(f->fd, f->header.offBlocks, SEEK_SET);
            write(f->fd, f->map, sizeof(f->header.cbBlock));
            f->header.cBlocksAllocated++;
            lseek(f->fd, 0, SEEK_SET);
            write(f->fd, &f->header, sizeof(f->header));
            physicalpage = f->map[virtualpage];
        }

        lseek(f->fd, f->header.offData + physicalpage * f->header.cbBlock + offset, SEEK_SET);
        byteswrotenow = write(f->fd, buf, cursize);
        if(byteswrotenow != cursize)
            break;
        f->cursor += cursize;
        buf += cursize;
        bytesleft -= cursize;
        byteswritten += cursize;
    }

    return byteswritten;
}
