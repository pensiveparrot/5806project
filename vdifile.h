#ifndef _VDI_FILE_H_
#define _VDI_FILE_H_
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>
#include <cstddef>
#include <cstring>
#include <stdlib.h>
#include <iostream>
typedef struct VDIHEADER
{
	//preheader
    char            szFileInfo[64];
    uint32_t        u32Signature;
    uint32_t        u32Version;
    uint32_t        u32Type;
    uint32_t 		cbHeader;
    uint32_t        fFlags;
    char            szComment[256];
    uint32_t        offBlocks;//translation map
    uint32_t 		offData;
     //  VDIDISKGEOMETRY LegacyGeometry;
    uint32_t	 	LegacyGeometry[4];
    /** Cylinders. */
    //uint32_t    cCylinders;
   // uint32_t cHeads;
    //uint32_t    cSectors;
    uint32_t        u32Dummy;
    /** Sector size. (bytes per sector) */
    //uint32_t    cbSector;
    uint64_t        cbDisk;
    uint32_t        cbBlock;
    uint32_t		cbBlockExtra;
    uint32_t        cBlocks;
    uint32_t    cBlocksAllocated;
    /** Number of allocated blocks. */
    //uint8_t     translationMap[256];
    
    //uint32_t postHeaderSize;
    /** UUID of image. */
    // char          uuidCreate;
    /** UUID of image's last modification. */
    //RTUUID          uuidModify;
    /** Only for secondary images - UUID of primary image. */
    // RTUUID          uuidLinkage;
    /** Size of this structure in bytes. */
    //uint32_t        cbHeader;
    /** The image type (VDI_IMAGE_TYPE_*). */
    // uint32_t        u32Type;
    /** Image flags (VDI_IMAGE_FLAGS_*). */
    // uint32_t        fFlags;
    /** Image comment. (UTF-8) */
    // char            szComment[256];
//postheader
	char          uuidCreate[16];
	char          uuidModify[16];
	char          uuidLinkage[16];
	char          uuidParentModify[16];
	uint32_t		LCHSGeometry[4];
    /** Size of disk (in bytes). */
    // uint64_t        cbDisk;
    /** Block size. (For instance VDI_IMAGE_BLOCK_SIZE.) Should be a power of 2! */
    //uint32_t        cbBlock;
    /** Size of additional service information of every data block.
     * Prepended before block data. May be 0.
     * Should be a power of 2 and sector-aligned for optimization reasons. */
   // uint32_t        cbBlockExtra;
    /** Number of blocks. */
    //uint32_t        cBlocks;
    /** Number of allocated blocks. */
    //uint32_t        cBlocksAllocated;
    /** UUID of image. */
    
    /** UUID of image's last modification. */
    
    /** Only for secondary images - UUID of previous image. */
    
    /** Only for secondary images - UUID of previous image's last modification. */
    
}VDIHEADER;

typedef struct VDIFile
{


    struct VDIHEADER header;
    //struct PVDIHEADER* h;
   // int fileSize;
    off_t cursor;
    int transmapsize;
    //int *transmapptr;
    //int file;
    int fd;
    int *map;
    //int whence;


}VDIFile;
struct VDIFile* VDIOpen(char *fn);
void VDIClose(struct VDIFile *f);
ssize_t VDIRead(struct VDIFile *f, void *buf, size_t count);
ssize_t VDIWrite(struct VDIFile *f, void *buf, size_t count);
off_t VDISeek(VDIFile *f, off_t offset, int anchor);
#endif

