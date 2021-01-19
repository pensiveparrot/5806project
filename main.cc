#include "vdifile.h"
#include "debug.h"
bool VDIFile::VDIOpen(char *fn)
{
    
    this->fd=open(fn,O_RDONLY);
    if(this->fd == -1)
        return false;
    return true;
}
void VDIFile::VDIClose(int fd)
{
    close(this->fd);
}
ssize_t VDIFile::VDIRead(int fd, void *buf, size_t count)
{
	fd=this->fd;
	ssize_t curbyte = read(fd, &buf, count);
	if(curbyte>-1)
	return curbyte;
	perror("read");
}
ssize_t VDIFile::VDIWrite(int fd, void *buf, size_t count)
{
	fd=this->fd;
    /*ssize_t curbyte;
    size_t byteslefttowrite = 0;
    while(byteslefttowrite != count)
    {
        curbyte = write(this->fd, &buf, byteslefttowrite);
        byteslefttowrite++;
    }
    return curbyte;*/
    //lseek(this->fd,
    write(fd,buf,count);
}
off_t VDIFile::VDISeek(int fd, off_t offset, int anchor)
{
    /*off_t location;
    if(anchor == SEEK_SET)
    {
        location = lseek(this->fd, offset, anchor);
        if(location < 0) return 1;
        this->cursor = location;
    }
    if(anchor == SEEK_CUR)
    {
        location = lseek(this->fd, offset, anchor);
        if(location < 0) return 1;
        this->cursor += offset;
    }
    if(anchor == SEEK_END)
    {
        location = lseek(this->fd, offset, anchor);
        if(location < 0) return 1;
        this->cursor = offset + this->fileSize;
    }
    return cursor;*/
    fd=this->fd;
    return lseek(fd,offset,anchor);
}
int main(int argc, char* argv[])
{
    debug dbg;
    void* buf[1024];
    VDIFile VDI;
    bool ab=VDI.VDIOpen(argv[1]);
    if(ab==true)
    {
    ssize_t byytes=VDI.VDIRead(VDI.fd,(buf),1024);
    dbg.displayBuffer((uint8_t*)buf,1024,0);
    VDI.VDIClose(VDI.fd);
    }
    
    return 0;
}
void debug::displayBufferPage(uint8_t *buf, uint32_t count, uint32_t skip, uint64_t offset){
	int c=0;
	for(int i=skip;i<=skip+count;i++){
	if(skip<=i&&i<skip+count){
	uint8_t bytes=buf[i];
	std::cout<<std::setfill('0')<<std::setw(2)<<std::hex<<(int)bytes<<" ";
	}
	else
	{
	std::cout<<"\n";
	break;
	}
	
	}
	c++;
	if(c%16==0)
	std::cout<<std::endl;
	    for (int j = skip; j <= count; j++) {
        if (skip <= j && j < skip + count) {
            uint8_t bytes = buf[j];
            if (isprint(int(bytes))) {
                std::cout << bytes << " ";
            } else {
                std::cout << " ";
            }
        }
        else{
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
