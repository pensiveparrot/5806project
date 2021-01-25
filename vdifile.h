#ifndef _VDI_FILE_H_
#define _VDI_FILE_H_
#include <fcntl.h>
#include <unistd.h>
#include <iomanip>
#include <cstddef>
struct VDIHEADER
{
    /** Just text info about image type, for eyes only. */
    char            szFileInfo[64];
    /** The image signature (VDI_IMAGE_SIGNATURE). */
    uint32_t        u32Signature;
    /** The image version (VDI_IMAGE_VERSION). */
    uint32_t        u32Version;

    /** The image type (VDI_IMAGE_TYPE_*). */
    uint32_t        u32Type;
    /** Image flags (VDI_IMAGE_FLAGS_*). */
    uint32_t        fFlags;
    /** Image comment. (UTF-8) */
    char            szComment[256];
    /** Legacy image geometry (previous code stored PCHS there). */
    /** Size of disk (in bytes). */
    uint64_t        cbDisk;
    /** Block size. (For instance VDI_IMAGE_BLOCK_SIZE.) */
    uint32_t        cbBlock;
    /** Number of blocks. */
    uint32_t        cBlocks;
    /** Number of allocated blocks. */
    uint8_t     translationmap[256];
    uint32_t    cBlocksAllocated;
    uint32_t postHeaderSize;
    /** UUID of image. */
    // char          uuidCreate;
    /** UUID of image's last modification. */
    //RTUUID          uuidModify;
    /** Only for secondary images - UUID of primary image. */
    // RTUUID          uuidLinkage;
    /** Size of this structure in bytes. */
    uint32_t        cbHeader;
    /** The image type (VDI_IMAGE_TYPE_*). */
    // uint32_t        u32Type;
    /** Image flags (VDI_IMAGE_FLAGS_*). */
    // uint32_t        fFlags;
    /** Image comment. (UTF-8) */
    // char            szComment[256];
    /** Offset of Blocks array from the beginning of image file.
     * Should be sector-aligned for HDD access optimization. */
    uint32_t        offBlocks;
    /** Offset of image data from the beginning of image file.
     * Should be sector-aligned for HDD access optimization. */
    uint32_t        offData;
    /** Legacy image geometry (previous code stored PCHS there). */
    //  VDIDISKGEOMETRY LegacyGeometry;
    /** Cylinders. */
    uint32_t    cCylinders;
    uint32_t cHeads;
    uint32_t    cSectors;
    /** Sector size. (bytes per sector) */
    uint32_t    cbSector;
    /** Was BIOS HDD translation mode, now unused. */
    uint32_t        u32Dummy;
    /** Size of disk (in bytes). */
    // uint64_t        cbDisk;
    /** Block size. (For instance VDI_IMAGE_BLOCK_SIZE.) Should be a power of 2! */
    //uint32_t        cbBlock;
    /** Size of additional service information of every data block.
     * Prepended before block data. May be 0.
     * Should be a power of 2 and sector-aligned for optimization reasons. */
    uint32_t        cbBlockExtra;
    /** Number of blocks. */
    //uint32_t        cBlocks;
    /** Number of allocated blocks. */
    //uint32_t        cBlocksAllocated;
    /** UUID of image. */
    char          uuidCreate[16];
    /** UUID of image's last modification. */
    char          uuidModify[16];
    /** Only for secondary images - UUID of previous image. */
    char          uuidLinkage[16];
    /** Only for secondary images - UUID of previous image's last modification. */
    char          uuidParentModify[16];
};

class VDIFile
{

public:
    int VDIOpen(char *fn);
    VDIFile(int);
    void VDIClose(int fd);
    ssize_t VDIRead(int fd, void *buf, size_t count);
    ssize_t VDIWrite(int fd, void *buf, size_t count);
    off_t VDISeek(int fd, off_t offset, int anchor);
    struct VDIHEADER header;
    int fileSize;
    off_t cursor;
    int transmapsize;
    int *transmapptr;
    //int file;
    int fd;
    int *map;
    int whence;
};
#endif

