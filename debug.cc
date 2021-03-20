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
    std::cout<<std::dec;
}*/
{
    int h = 0,
        hwidth = 16,
        twidth = 16,
        hcursor = 0,
        tcursor = 0,
        numt = count,
        numh = count,
        hcur = 0,
        tcur = 0,
        placeholder=0;
    if(skip >= 256)
    {
        hcursor = skip;
        tcursor = skip;
        skip = 0;
    }
    printf("Offset: 0x%02x\n",offset);
    printf(" 00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f     0...4...8...c...\n+-----------------------------------------------+  +----------------+\n");

    while(h < 16)
    {
        printf("|");
        while(hwidth > 0)
        {
            if(skip <= offset && numh > 0 && hcur >= skip)
            {
				if(numh==1||hwidth==1)
				{	
				printf("%02x", buf[hcursor]);
				}
				else{
                printf("%02x ", buf[hcursor]);
			}
              
			    hcursor++;
                numh--;  
            }
            else
                printf("   ");

		
            hwidth--;
            hcur++;
        }
		printf("|%x0|",placeholder);
        placeholder++;

        //std::cout<<"|"<<std::setfill('0')<<std::setw(2)<<h<<"|";
        while(twidth > 0)
        {
            if(skip <= offset && numt > 0 && tcur >= skip)
            {
                if(isprint(buf[tcursor]))
                {	
                printf("%c",buf[tcursor]);
			}
                else
                    printf(" ");

			   tcursor++;
                numt--;
            }
            else
                printf(" ");

            twidth--;
            tcur++;
        }
        printf("|\n");
        h++;
        hwidth = 16;
        twidth = 16;
    }
    printf("+-----------------------------------------------+  +----------------+\n");
}

void debug::dumpvdiheader(struct VDIHEADER *header)
{
    printf("Image Name: %s\n",header->szFileInfo);
    printf("Signature: 0x%02x\n",header->u32Signature);
    printf("Version: 0x%02x\n",header->u32Version);
    printf("Header Size: 0x%08x\t%d\n",header->cbHeader,header->cbHeader);
    printf("Image Type: 0x%08x\n",header->u32Type);
    printf("Flags: 0x%08x\n",header->fFlags);
    printf("Virtual CHS: %d-%d-%d\n",header->LegacyGeometry[0],header->LegacyGeometry[1],header->LegacyGeometry[2]);
    printf("Sector size: 0x%08x\t%d\n",header->LegacyGeometry[3],header->LegacyGeometry[3]);
    printf("Logical CHS: %d-%d-%d\n",header->LCHSGeometry[0],header->LCHSGeometry[1],header->LCHSGeometry[2]);
    printf("Sector size: 0x%08x\t%d\n",header->LCHSGeometry[3],header->LCHSGeometry[3]);
    printf("Map Offset (Offblocks): 0x%08x\t%d\n",header->offBlocks,header->offBlocks);
    printf("Frame offset (OffData): 0x%08x\t%d\n",header->offData,header->offData);
    printf("Frame size (cbBlock): 0x%08x\t%d\n",header->cbBlock,header->cbBlock);
    printf("Extra Frame Size: 0x%08x\t%d\n",header->cbBlockExtra,header->cbBlockExtra);
    printf("Total frames (cBlocks): 0x%08x\t%d\n",header->cBlocks,header->cBlocks);
    printf("Frames allocated: 0x%08x\t%d\n",header->cBlocksAllocated,header->cBlocksAllocated);
    printf("Disk size (cbDisk): %p\t%d\n",header->cbDisk,header->cbDisk);
    //std::cout << "Image Comment: " << std::endl;
    

}
//void debug::displaysuperblock();

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
