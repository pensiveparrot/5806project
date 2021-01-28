#include "debug.h"
void debug::displayBufferPage(uint8_t *buf, uint32_t count, uint32_t skip, uint64_t offset)
/*{
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
}*/
{
	int h=0,
	hwidth=16,
	twidth=16,
	hcursor=0,
	tcursor=0,
	numt=count,
	numh=count,
	hcur=0,
	tcur=0;
	if(skip>=256){
	hcursor=skip;
	tcursor=skip;
	skip=0;
}
std::cout << std::hex << "Offset: 0x" << offset << std::endl;
	std::cout << "   00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f     0...4...8...c..." <<std::endl;
    std::cout << "  +------------------------------------------------+  +----------------+" <<std::endl;

	while(h<16){
		std::cout<<std::hex<<std::setfill('0')<<std::setw(2)<<h<<"|";
		while(hwidth>0)
		{
			if(skip<=offset&&numh>0&&hcur>=skip)
			{
				printf("%02x",buf[hcursor]);
				std::cout<<" ";
				hcursor++;
				numh--;
				}
				else
				std::cout<<"   ";
				
				hwidth--;
				hcur++;
			}
			std::cout<<"|"<<std::setfill('0')<<std::setw(2)<<h<<"|";
		while(twidth>0){
			if(skip<=offset&&numt>0&&tcur>=skip)
			{
			if(isprint(buf[tcursor]))
			std::cout<<static_cast<uint8_t>(buf[tcursor]);
			else
			std::cout<<" ";
		
		tcursor++;
		numt--;
		}
		else
		std::cout<<" ";
			
			twidth--;
			tcur++;
			}
			std::cout<<"|"<<std::endl;
		h++;
		hwidth=16;
		twidth=16;
		}
		    std::cout << "  +------------------------------------------------+  +----------------+" <<std::endl;
	
	}

void debug::dumpvdiheader(struct VDIHEADER *header){
    std::cout << "Image Name: " << header->szFileInfo << std::endl;
    std::cout << "Signature: 0x" << std::hex << header->u32Signature << std::endl;
    std::cout << "Version: " << std::hex << header->u32Version << std::endl;
    std::cout << "Header Size: 0x" << std::hex <<std::setw(8) <<std::setfill('0') <<header->cbHeader << "   " <<std::dec <<header->cbHeader << std::endl;
    std::cout << "Image Type: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->u32Type <<std::endl;
    std::cout << "Flags: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->fFlags <<std::endl;
    std::cout << "Virtual CHS: " << header->LegacyGeometry[0] << "-" <<header->LegacyGeometry[1] << "-" <<header->LegacyGeometry[2] <<std::endl;
    std::cout << "Sector size: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->LegacyGeometry[3] << "   " <<std::dec <<header->LegacyGeometry[3] <<std::endl;
    std::cout << "Logical CHS: " <<std::dec << header->LCHSGeometry[0] << "-" <<header->LCHSGeometry[1] << "-" <<header->LCHSGeometry[2] <<std::endl;
    std::cout << "Sector size: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->LCHSGeometry[3] << "   " << std::dec <<header->LCHSGeometry[3] <<std::endl;
    std::cout << "Map Offset (""Offblocks""): 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->offBlocks << "   " <<std::dec <<header->offBlocks <<std::endl;
    std::cout << "Frame offset (""OffData""): 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->offData << "   " <<std::dec <<header->offData <<std::endl;
    std::cout << "Frame size (""cbBlock""): 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->cbBlock << "   " <<std::dec <<header->cbBlock <<std::endl;
    std::cout << "Extra Frame Size: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->cbBlockExtra << "   " <<std::dec <<header->cbBlockExtra <<std::endl;
    std::cout << "Total frames (""cBlocks""): 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->cBlocks << "   " <<std::dec <<header->cBlocks <<std::endl;
    std::cout << "Frames allocated: 0x" <<std::hex<<std::setw(8) <<std::setfill('0') <<header->cBlocksAllocated << "   " <<std::dec <<header->cBlocksAllocated <<std::endl;
    std::cout << "Disk size (""cbDisk""): 0x" <<std::hex<< std::setw(16) <<std::setfill('0') <<header->cbDisk << "   " <<std::dec <<header->cbDisk <<std::endl;
    std::cout << "Image Comment: " <<std::endl;


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
