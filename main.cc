//#include <cstddef>
#include "vdifile.h"
#include "debug.h"

int main(int argc, char *argv[])
{
    //struct VDIHEADER* header;
    debug dbg;
    /*uint8_t *
    mbr = new uint8_t[512];*/
    uint8_t mbr[512];
    //VDIFile VDI(1024);
    struct VDIFile *f;
    f = VDIOpen(argv[1]);
    if(f)
    {
        printf("header\n");
        dbg.dumpvdiheader(&f->header);
        dbg.displayBuffer((uint8_t *)(&f->header), 400, 0);

        printf("translation map\n");
        dbg.displayBuffer((uint8_t *)(f->map), 512, 0);
        //bg.displayBuffer(buf, 512, 0);
        printf("mbr partition scheme\n");
        VDISeek(f, 256, SEEK_SET);
        VDIRead(f, (void *)mbr, 256);
        dbg.displayBufferPage(mbr, 64, 190, 256);
        VDIClose(f);
        //delete[] mbr;
    }

    return 0;
}

