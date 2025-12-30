#include "../include/umkaPlugin.h"

// Function to load a file's contents
// Takes a C string as an argument and returns a C string
// The caller is responsible for freeing the allocated memory of the buffer
const char* loadUmkaScriptFromFile(const char* filePath) {
    FILE* filePtr = fopen(filePath, "r");

    if (filePtr == NULL) {
        printf("PANIC: Could not open %s\n", filePath);
        exit(1);
    }

    if (fseek(filePtr, 0, SEEK_END) != 0) { 
        fclose(filePtr);
        printf("PANIC: Could not seek end of file %s\n", filePath);
        exit(1); 
    }

    long bufferSize = ftell(filePtr);
    if (bufferSize < 0) { 
        fclose(filePtr);
        printf("PANIC: Could not get file size %s\n", filePath);
        exit(1);
    }

    rewind(filePtr);

    char *buf = malloc((size_t)bufferSize + 1);

    if (buf == NULL) { 
        fclose(filePtr);
        printf("PANIC: Could not allocate memory for buffer\n");
        exit(1);
    }

    size_t newLength = fread(buf, 1, (size_t)bufferSize, filePtr);

    if (ferror(filePtr) != 0) {
        free(buf);
        fclose(filePtr);
        printf("PANIC: Failure reading file %s\n", filePath);
        exit(1);
    } else {
        buf[newLength] = '\0';
    }

    fclose(filePtr);
    return buf;
}

Umka* loadUmka(const char* filePath, int argc, char** argv) {
    int stackSize = 4096;
    const char* umkaSource = loadUmkaScriptFromFile(filePath);

    Umka* umka = umkaAlloc();
    bool fileSystem = true;
    bool implLibs = true;

    bool ok = umkaInit(
        umka, 
        filePath, 
        umkaSource,
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

    free(umkaSource);
    return umka;
}
