#include <stdint.h>
//esta funcion debe retornar en base a un indice de tabla de paginas si dicha pagina fue seteada
int ptEntryPresent(uint64_t index){
	return 1;
}

void* getPhyAddr(void* virtualAddr){

	uint64_t ptindex = (uint64_t)virtualAddr >> 22 & 0x1FFFFF;
	uint64_t* pt = 0x1000000;

	if(ptEntryPresent(ptindex));
	if((uint64_t)(pt+(ptindex * 0x400)) & 0x1 == 0)
		return (void*)0;

	return (void*)((pt[ptindex] & ~0x3FFFFF)+((uint64_t)virtualAddr & 0x3FFFFF));
}

void mapPage(void* physAddr, void*virtualAddr, uint64_t flags){

	if(!((uint64_t)physAddr & ~0x400000 == (uint64_t)0 && (uint64_t)virtualAddr & ~0x400000 == (uint64_t)0)){
		return;
	}
 
 	uint64_t ptindex = (uint64_t)virtualAddr >> 22 & 0x1FFFFF;
	uint64_t* pt = 0x1000000;

	if(ptEntryPresent(ptindex));
	if((uint64_t)(pt+(ptindex * 0x400)) & 0x1 == 1)
		return;

	pt[ptindex] = ((uint64_t)physAddr) | (flags &0x3FFFFF) | 0x01;

}