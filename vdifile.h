#pragma once
#include <fcntl.h>
#include <unistd.h>
class VDIFile{
public:
bool VDIOpen(char* fn);
void VDIClose(int fd);
ssize_t VDIRead(int fd,void* buf,size_t count);
ssize_t VDIWrite(int fd,void* buf,size_t count);
off_t VDISeek(int fd,off_t offset,int anchor);
int fileSize;
off_t cursor;
int file;
int fd;
};
