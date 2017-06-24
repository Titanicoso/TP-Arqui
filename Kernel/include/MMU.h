void changePDEPresent(int entry, int present);
void setKernelPresent(int present);
void copyAndExecuteModule(int moduleIndex, int argc, char *argv[]);
void copyModule(int moduleIndex);
void copyAndExectueDefaultModule();
void changePDE(int entry, uint64_t* physAddr, int present);
void changePDEPresent(int entry, int present);
void * initializeKernelBinary();