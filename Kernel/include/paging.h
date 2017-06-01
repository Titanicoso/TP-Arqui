#include <stdint.h>

void* getPhyAddr(void* linearAddr);
void mapPage(void* physAddr, void*linearAddr, uint32_t flags);