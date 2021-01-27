#include "debug.h"
void debug::displayBufferPage(uint8_t *buf, uint32_t count, uint32_t skip, uint64_t offset)
{
    std::cout << "value in hex\n";
    int c = 0;
    for(int i = skip; i <= skip + count; i++)
    {
        if(skip <= i && i < skip + count)
        {
            uint8_t bytes = buf[i];
            std::cout << std::setfill('0') << std::setw(2) << std::hex << (int)bytes << " ";
        }
        else
        {
            std::cout << std::endl;
            break;
        }

    }
    c++;
    if(c % 16 == 0)
        std::cout << std::endl;

    std::cout << "value in ascii\n";
    for (int j = skip; j <= count; j++)
    {
        if (skip <= j && j < skip + count)
        {
            uint8_t bytes = buf[j];
            if (isprint(int(bytes)))
            {
                std::cout << bytes << "";
            }
            else
            {
                std::cout << " ";
            }
        }
        else
        {
            std::cout << std::endl;
            break;
        }
    }
}
void debug::dumpvdiheader(struct VDIHEADER *header)
{
    std::cout << "Image Name: " << header->szFileInfo << std::endl;
    std::cout << "Signature: 0x" << std::hex << header->u32Signature << std::endl;
    std::cout << "Version: " << std::hex << header->u32Version << std::endl;
    std::cout << "Header Size: 0x" << std::hex << std::setw(8) << std::setfill('0') << header->cbHeader << "   " << std::dec << header->cbHeader << std::endl;
    std::cout << "Image Type: 0x" << std::hex << std::setw(8) << std::setfill('0') << header->u32Type << std::endl;
    std::cout << "Flags: 0x" << std::hex << std::setw(8) << std::setfill('0') << header->fFlags << std::endl;
    std::cout << "Virtual CHS: " << header->LegacyGeometry[0] << "-" << header->LegacyGeometry[1] << "-" << header->LegacyGeometry[2] << std::endl;
    std::cout << "Sector size: 0x" << std::hex << std::setw(8) << std::setfill('0') << header->LegacyGeometry[3] << "   " << std::dec << header->LegacyGeometry[3] << std::endl;
    std::cout << "Logical CHS: " << std::dec << header->LCHSGeometry[0] << "-" << header->LCHSGeometry[1] << "-" << header->LCHSGeometry[2] << std::endl;
    std::cout << "Sector size: 0x" << std::hex << std::setw(8) << std::setfill('0') << header->LCHSGeometry[3] << "   " << std::dec << header->LCHSGeometry[3] << std::endl;
    std::cout << "Map Offset (""Offblocks""): 0x" << std::hex << std::setw(8) << std::setfill('0') << header->offBlocks << "   " << std::dec << header->offBlocks << std::endl;
    std::cout << "Frame offset (""OffData""): 0x" << std::hex << std::setw(8) << std::setfill('0') << header->offData << "   " << std::dec << header->offData << std::endl;
    std::cout << "Frame size (""cbBlock""): 0x" << std::hex << std::setw(8) << std::setfill('0') << header->cbBlock << "   " << std::dec << header->cbBlock << std::endl;
    std::cout << "Extra Frame Size: 0x" << std::hex << std::setw(8) << std::setfill('0') << header->cbBlockExtra << "   " << std::dec << header->cbBlockExtra << std::endl;
    std::cout << "Total frames (""cBlocks""): 0x" << std::hex << std::setw(8) << std::setfill('0') << header->cBlocks << "   " << std::dec << header->cBlocks << std::endl;
    std::cout << "Frames allocated: 0x" << std::hex << std::setw(8) << std::setfill('0') << header->cBlocksAllocated << "   " << std::dec << header->cBlocksAllocated << std::endl;
    std::cout << "Disk size (""cbDisk""): 0x" << std::hex << std::setw(16) << std::setfill('0') << header->cbDisk << "   " << std::dec << header->cbDisk << std::endl;
    std::cout << "Image Comment: " << std::endl;


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
