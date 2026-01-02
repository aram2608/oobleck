#include "../include/umka_plugin.h"

Umka* loadUmka(const char* filePath, int argc, char** argv) {
    int stackSize = 4096;

    Umka* umka = umkaAlloc();
    bool fileSystem = true;
    bool implLibs = true;

    bool ok = umkaInit(
        umka, 
        filePath, 
        NULL,
        stackSize,
        NULL, 
        argc,
        argv, 
        fileSystem, 
        implLibs,
        NULL);
    
    if (!ok) {
        printf("UmkaError: failed to initialize Umka\n");
        exit(1);
    }

    ok = umkaCompile(umka);

    if (!ok) {
        printf("UmkaError: failed to compile Umka\n");
        exit(1);
    }
    return umka;
}
