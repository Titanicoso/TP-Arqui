#include <stdint.h>
//esta funcion debe retornar en base a un indice de tabla de paginas si dicha pagina fue seteada
int ptEntryPresent(uint64_t index){
	return 1;
}

void* getPhyAddr(void* linearAddr){

	uint32_t ptindex = (uint32_t)linearAddr >> 22 & 0x1FFFFF;
	//la tabla de paginas esta en fisica a partir del 32avo mega
	uint32_t* pt = 0x1000000;

	if(ptEntryPresent(ptindex));
	if((uint32_t)(pt+(ptindex * 0x400)) & 0x1 == 0)
		//excepcion de page not present

	return (void*)((pt[ptindex] & ~0x3FFFFF)+((uint32_t)linearAddr & 0x3FFFFF));
}

void mapPage(void* physAddr, void*linearAddr, uint32_t flags){

	if(!((uint32_t)physAddr & ~0x400000 == (uint32_t)0 && (uint32_t)linearAddr & ~0x400000 == (uint32_t)0)){
		return;
	}
 
 	uint32_t ptindex = (uint32_t)linearAddr >> 22 & 0x1FFFFF;
	uint32_t* pt = 0x1000000;

	if(ptEntryPresent(ptindex));
	if((uint32_t)(pt+(ptindex * 0x400)) & 0x1 == 1)
		return;

	pt[ptindex] = ((uint32_t)physAddr) | (flags &0x3FFFFF) | 0x01;

}