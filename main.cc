#include "vdifile.h"
bool VDIFile::VDIOpen(char *fn, int mode)
{
    mode = 2;
    open(fn, mode);
    if(filedescriptor = -1)
        return false;
    return true;
}
void VDIFile::VDIClose(int fd)
{
    close(fd);
}
ssize_t VDIFile::VDIRead(int fd, void *buf, size_t count)
{
    ssize_t bytesleft = count;
    while(bytesleft != 0)
    {
        read(fd, &buf, bytesleft);
        bytesleft--;
    }
}
ssize_t VDIFile::VDIWrite(int fd, void *buf, size_t count)
{
    size_t byteslefttowrite = 0;
    while(byteslefttowrite != count)
    {
        write(fd, &buf, byteslefttowrite);
        byteslefttowrite++;
    }
}
off_t VDIFile::VDISeek(int fd, off_t offset, int anchor)
{
    off_t location;
    if(anchor == SEEK_SET)
    {
        location = lseek(fd, offset, anchor);
        if(location < 0) return 1;
        cursor = location;
    }
    if(anchor == SEEK_CUR)
    {
        location = lseek(fd, offset, anchor);
        if(location < 0) return 1;
        cursor += offset;
    }
    if(anchor == SEEK_END)
    {
        location = lseek(fd, offset, anchor);
        if(location < 0) return 1;
        cursor = offset + fileSize;
    }
    return cursor;
}
int main()
{
    return 0;
}
void debug::displayBufferPage(uint8_t *buf, uint32_t count, uint32_t skip, uint64_t offset)
{
    int h = 0;
    int iHexW = 16;
    int iCharW = 16;
    int iCharCursor = 0;
    int iHexCursor = 0;
    int iNumHex = count;
    int iNumChar = count;

    int iHexCurrent = 0;
    int iCharCurrent = 0;

    if(skip >= 256)
    {
        iHexCursor = skip;
        iCharCursor = skip;
        skip = 0;
    }
    std::cout << std::hex << "0x" << offset << std::endl;
    while(h < 16)
    {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << h << "-";
        while(iHexW > 0)
        {
            if(start <= offset && iNumHex > 0 && iHexCurrent >= skip)
            {
                printf("%02x"/*<2 dig = 0*/, buf[iHexCursor]);
                std::cout << " ";
                iHexCursor++;
                iNumHex--;
            }
            else
                std::cout << "	";
            iHexW--;
            iHexCurrent++;
        }

        std::cout << std::hex << "|" << std::setfill('0') << std::setw(2) << h << "|";

        while (iCharW > 0)
        {
            if(skip <= offset && iNumChar > 0 && iCharCurrent >= skip)
            {
                if(isprint(buf[iCharCursor]))
                    std::cout << static_cast<uint8_t>(buf[iCharCursor]);
                else
                    std::cout << " ";
            }
            iCharCursor++;
            iNumChar--;
            else
                std::cout << " ";

            iCharW--;
            iCharCurrent++;
        }

    }
    std::cout << "+\n";
    h++;
    iHexW = 16;
    iCharW = 16;
    std::cout << "+________________________________________________+  +________________+\n"
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