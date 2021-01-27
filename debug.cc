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
void debug::dumpheader(struct VDIHEADER* header){
    std::cout << "Image Name: " << header->szFileInfo << std::endl;
    std::cout << "Signature: 0x" << std::hex << header->u32Signature << std::endl;
    std::cout << "Version: " << std::hex << header->u32Version << endl;
    std::cout << "Header Size: 0x" << std::hex <<std::setw(8) <<std::setfill('0') << headerInfo->cbHeader << "   " << dec << headerInfo->cbHeader << endl;
    std::cout << "Image Type: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->imageType << endl;
    std::cout << "Flags: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->fFlags << endl;
    std::cout << "Virtual CHS: " << headerInfo->legacyGeometry[0] << "-" << headerInfo->legacyGeometry[1] << "-" << headerInfo->legacyGeometry[2] << endl;
    std::cout << "Sector size: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->legacyGeometry[3] << "   " << dec << headerInfo->legacyGeometry[3] << endl;
    std::cout << "Logical CHS: " << dec << headerInfo->LCHSGeometry[0] << "-" << headerInfo->LCHSGeometry[1] << "-" << headerInfo->LCHSGeometry[2] << endl;
    std::cout << "Sector size: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->LCHSGeometry[3] << "   " << dec << headerInfo->LCHSGeometry[3] << endl;
    std::cout << "Map Offset (""Offblocks""): 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->offBlocks << "   " << dec << headerInfo->offBlocks << endl;
    std::cout << "Frame offset (""OffData""): 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->offData << "   " << dec << headerInfo->offData << endl;
    std::cout << "Frame size (""cbBlock""): 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->cbBlock << "   " << dec << headerInfo->cbBlock << endl;
    std::cout << "Extra Frame Size: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->cbBlockExtra << "   " << dec << headerInfo->cbBlockExtra << endl;
    std::cout << "Total frames (""cBlocks""): 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->cBlocks << "   " << dec << headerInfo->cBlocks << endl;
    std::cout << "Frames allocated: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') << headerInfo->cBlocksAllocated << "   " << dec << headerInfo->cBlocksAllocated << endl;
    std::cout << "Disk size (""cbDisk""): 0x" <<std::hex<< std::setw(16) <<std::setfill('0') << headerInfo->cbDisk << "   " << dec << headerInfo->cbDisk << endl;
    std::cout << "Image Comment: " << endl;


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
