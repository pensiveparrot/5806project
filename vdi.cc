#include "vdifile.h"
/*VDIFile::VDIFile(int tmapsize)
{
    transmapsize = tmapsize;
    transmapptr = new int[transmapsize];
    cursor = 0;
    fileSize=header.cbDisk;
}*/
struct VDIFile *VDIOpen(char *fn)
{
//VDIHEADER header;

    int fd = open(fn, O_RDONLY);

    if(fd == -1)
       return NULL;
	
    else
    {
       struct VDIFile *file=(struct VDIFile*)malloc(sizeof(struct VDIFile));
       read(fd, &file->header, sizeof(file->header));
       file->transmapsize = file->header.cBlocks;
       file->transmapptr=new int[file->transmapsize];
       lseek(fd, /*header.offBlocks*/file->transmapsize, SEEK_SET);
       read(fd, file->transmapptr, sizeof(file->transmapsize));
        file->fd=fd;
		file->cursor = 0;
		return file;
    }
    //return fd;
    
}
void VDIClose(struct VDIFile *f)
{
    
    delete[] f->transmapptr;
    close(f->fd);
}
off_t VDISeek(VDIFile *f, off_t offset, int anchor)
{
	uint8_t newpos;
    //whence = anchor;
    //fd = this->fd;
    off_t location;
    switch(anchor)
    {
    case(SEEK_SET):
		if(offset<f->header.cbDisk && offset>=0)
		f->cursor = offset;
		else
		return -1;
        //location = lseek(fd, offset, anchor);
        //if(location < 0) return 1;
        
        break;
    case(SEEK_CUR):
    if(f->cursor+offset<f->header.cbDisk && f->cursor + offset>=0)
		 f->cursor += offset;
		 else
		 return -1;
        //location = lseek(fd, offset, anchor);
        //if(location < 0) return 1;
       
        break;
    case(SEEK_END):
        //location = lseek(fd, offset, anchor);
        //if(location < 0) return 1;
        if(offset<0)
        f->cursor = offset + f->header.cbDisk;
        else
        return -1;
        break;
    default:
        perror("seek");
        break;

    }
    return f->cursor;

    //return lseek(fd,offset,anchor);
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
        cursize=f->header.cbBlock - offset;
        if(cursize>bytesleft)
        cursize=bytesleft;
        physicalpage = f->transmapptr[virtualpage];
        //reallocation = physicalpage * f->header.cbBlock + offset;
        lseek(f->fd, reallocation + f->header.offData, SEEK_SET);
        ssize_t bytesjustread = 0;
        if(physicalpage>=0xfffffffe)
        memset(buf,0,cursize);
        else
        {
			lseek(f->fd,f->header.offData + offset,SEEK_SET);
			bytesjustread=read(f->fd,buf,cursize);
			if(bytesjustread!=cursize)
			break;
			}
			f->cursor+=cursize;
			buf+=cursize;
			bytesleft-=cursize;
			bytesread+=cursize;
        /*if(reallocation >= 0)
        {
            size_t bytestoread = 0;
            if(count < f->header.cbBlock)
                bytestoread = count;
            else
                bytestoread = f->header.cbBlock;

            bytesjustread = read(f->fd, static_cast<uint8_t*>(buf) + bytesread, bytestoread);
        }
        else
        {
            for(int i = 0; i > f->header.cbBlock; i++)
            {
                *(static_cast<uint8_t *>(buf) + (bytesread + bytesjustread)) = '0';
                bytesjustread++;
            }
        }
        if(bytesjustread < 0)
            return -1;
        bytesread += bytesjustread;
        bytesleft -= bytesjustread;
        VDISeek(f, bytesjustread, SEEK_CUR);

    }

    return bytesread;

*/
}
return bytesread;
}

ssize_t VDIWrite(struct VDIFile *f, void *buf, size_t count)
/*{
    /* fd = this->fd;
     ssize_t byte;
     size_t bytesleft = count;
     while(bytesleft > 0)
     {
         byte = write(fd, buf, bytesleft);
         bytesleft--;
     }

     return byte;
   // fd = this->fd;
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
        offset = f->cursor % f->header.cbBlock;
        virtualpage = f->cursor / f->header.cbBlock;
        physicalpage = f->transmapptr[virtualpage];
        reallocation = physicalpage * f->header.cbBlock + offset;
        lseek(f->fd, reallocation + f->header.offData, SEEK_SET);
        byteswrotenow = 0;
        if(reallocation < 0)
        {
            lseek(f->fd, 0, SEEK_END);
            uint8_t *buf2 = new uint8_t[f->header.cbBlock];
            write(f->fd, buf2, f->header.cbBlock);
            delete[] buf2;
            physicalpage = f->header.cBlocksAllocated;
            f->header.cBlocksAllocated++;
            f->transmapptr[virtualpage] = physicalpage;
            lseek(f->fd, 0, SEEK_SET);
            write(f->fd, &f->header, sizeof(f->header));
            lseek(f->fd, f->header.offBlocks, SEEK_SET);
            write(f->fd, f->transmapptr, sizeof(uint32_t)*f->header.cbBlock);


        }
        if(count < f->header.cbBlock)
            bytestowrite = count;
        else
            bytestowrite = f->header.cbBlock;
        byteswrotenow = write(f->fd, static_cast<uint8_t*>(buf) + byteswrote, bytestowrite);
        byteswrote += byteswrotenow;
        bytesleft -= byteswrotenow;
        VDISeek(f, byteswrotenow, SEEK_CUR);
    }
    return byteswrote;
}*/
{
	size_t bytesleft = count,

           byteswritten = 0,
           virtualpage,
           byteswrotenow,
           offset,
           cursize,
           physicalpage,
           reallocation;
           
	while(bytesleft>0){
		virtualpage = f->cursor / f->header.cbBlock;
        offset = f->cursor % f->header.cbBlock;
        cursize=f->header.cbBlock - offset;
        if(cursize>bytesleft)
        cursize=bytesleft;
        physicalpage = f->transmapptr[virtualpage];
        if(physicalpage>=0xfffffffe){
		uint8_t *tmp = new uint8_t[f->header.cbBlock];
		lseek(f->fd,0,SEEK_END);
		write(f->fd,tmp,f->header.cbBlock);
		delete[] tmp;
	}
	f->map[virtualpage]=f->header.cBlocksAllocated;
	write(f->fd,f->map,sizeof(f->header.cbBlock));
	f->header.cBlocksAllocated++;
	write(f->fd,&f->header,sizeof(f->header));
	physicalpage=f->map[virtualpage];
	lseek(f->fd,f->header.offData+physicalpage*f->header.cbBlock+offset,SEEK_SET);
	byteswrotenow=write(f->fd,buf,cursize);
	if(byteswrotenow!=cursize)
	break;
			buf+=cursize;
			bytesleft-=cursize;
			byteswritten+=cursize;
		}
	}
