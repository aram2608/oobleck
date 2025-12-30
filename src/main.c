#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/umkaPlugin.h"
#include "../include/gapBuffer.h"

int main(int argc, char** argv) {
    GapBuffer* buff = newBuffer(BUFFER_SIZE);
    Umka* umka = loadUmka("plugin.um", argc, argv);
    umkaRun(umka);

    insertString(buff, "Hello world!");

    printf("Buffer: %s\n", buff->data);

    umkaFree(umka);
    destroyBuffer(buff);
    return 0;
}
