#include <stdint.h>
#include <moduleLoader.h>

typedef int (*EntryPoint)();

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x600000;
static void * const shell = (void*)0x800000;
static void * const executableMemoryAdress = (void*)0xA00000;

void copyAndExectueDefaultModule(){
	memcpy(executableMemoryAdress, shell, 0x20000);
	((EntryPoint)executableMemoryAdress)();


}
void copyAndExecuteModule(void* moduleAdress){
	memcpy(executableMemoryAdress, moduleAdress, 0x200000);
	((EntryPoint)executableMemoryAdress)();
}

void setKernelPresent(int present){
  uint64_t *PD = 0x10000; 
  uint64_t entry= *PD; 
  if(present) 
    *PD = entry | 0x1; 
  else 
    *PD = entry & ~0x1; 
}

void changePDEPresent(int entry, int present){
	uint64_t* PD = 0x10000;

	while(entry){ 
    PD + 0x8; 
    --entry; 
  	} 
 	uint64_t PDE = *PD;
 
 	if(present)
  		*PD =  PDE | 0x1; 
  	else
  		*PD = PDE & ~0x1;  
}

void changePDE(int entry, uint64_t* physAddr, int present){ 
  if(*physAddr & 0x000FFFFF != 0) 
    return; 
 
  
  uint64_t *PD = 0x10000; 
 
  while(entry){ 
    PD + 0x4; 
    --entry; 
  } 

  uint64_t oldEntry = *PD;
 
  if(present) 
    *PD = oldEntry & 0xFFFFF | (uint64_t)physAddr & ~0xFFFFF | 0x1; 
  else 
    *PD = oldEntry & 0xFFFFF | (uint64_t)physAddr & ~0xFFFFF & ~0x1; 
} 

void pageFaultHandler(){ 
  copyAndExectueDefaultModule();
} 

