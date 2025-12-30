#ifndef UMKA_PLUGIN_H
#define UMKA_PLUGIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../include/umka_api.h"

// Function to load a file's contents
// Takes a C string as an argument and returns a C string
// The caller is responsible for freeing the allocated memory of the buffer
const char* loadUmkaScriptFromFile(const char* filePath);

// Function to load an Umka context from a filePath
// Takes a C string for the filepath and command line args as the arguments
// Returns a pointer to an Umka context
Umka* loadUmka(const char* filePath, int argc, char** argv);

#endif // umkaPlugin.h
