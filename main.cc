 //#include <cstddef>
#include "vdifile.h"
#include "debug.h"
#include "partition.h"
#include "inode.h"
#include "directory.h"
#include "ext2.h"
int main(int argc, char *argv[])
{
    //struct VDIHEADER* header;
    debug dbg;
    /*uint8_t *
    mbr = new uint8_t[512];*/
    uint8_t mbr[512];
    //VDIFile VDI(1024);
    struct VDIFile *f;
    struct PartitionFile *p;
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
        //VDISeek(f, 256, SEEK_SET);
        //tested partitonseek, works
        PartitionSeek(p, 256, SEEK_SET, f);
        /*tested partitionread, works
         * issue lies with displaybuffer or displaybufferpage which is printing invalid data
         * This seems to be unfixable with my current knowledge.  This is a reminder to ask Dr. Kramer before time is up to help again with this debugging func.
         * This suggestion that the read/seek working comes from no noticeable changes to the data outputted when going to that specific byte/bit(idk which it is but at 256).  This should be the case
         * since it is just using the functions made before.  There isn't any seg faults or invalid memory exceptions so it has to be the way its outputting instead of a data violation.*/
        PartitionRead(f, (void *)mbr, 256, p);
        //VDIRead(f, (void *)mbr, 256);
        dbg.displayBufferPage(mbr, 64, 190, 256);
        VDIClose(f);
        //delete[] mbr;
    }

    return 0;
}
ssize_t copyfile(char* vdifilename, char* src, char* dst){
	
	ext2file *ext2 = new ext2file; 
	
	
	
	}
