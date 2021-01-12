#include "vdifile.h"
bool VDIFile::VDIOpen(char *fn,int mode){
mode=2;
open(fn,mode);
if(filedescriptor=-1)
return false;
return true;
}
void VDIFile::VDIClose(int fd)
{
close(fd);
}
ssize_t VDIFile::VDIRead(int fd, void *buf, size_t count){
ssize_t bytesleft=count;
while(bytesleft!=0){
read(fd,&buf,bytesleft);
bytesleft--;
}
}
ssize_t VDIFile::VDIWrite(int fd,void* buf, size_t count)
{
size_t byteslefttowrite=0;
while(byteslefttowrite!=count){
write(fd,&buf,byteslefttowrite);
byteslefttowrite++;
}
}
off_t VDIFile::VDISeek(int fd,off_t offset,int anchor)
{
off_t location;
if(anchor==SEEK_SET){
location =lseek(fd,offset,anchor);
if(location<0) return 1;cursor=location;}if(anchor==SEEK_CUR){location=lseek(fd,offset,anchor);if(location<0) return 1;cursor+=offset;}if(anchor==SEEK_END){location=lseek(fd,offset,anchor);if(location<0) return 1;cursor=offset+fileSize;}return cursor;}int main(){return 0;}/*void displayBufferPage(uint8_t *buf,uint32_t count, uint32_t skip, uint64_t offset){}*/