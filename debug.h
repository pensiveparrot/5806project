#ifndef _DEBUG_H_
#define _DEBUG_H_
#include <iostream>
#include <iomanip>
class debug{
	public:
	void displayBuffer(uint8_t * buf, uint32_t count, uint64_t offset);
	void displayBufferPage(uint8_t * buf, uint32_t count, uint32_t skip, uint64_t offset);
	
	
};
#endif
