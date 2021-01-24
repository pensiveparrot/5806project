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
