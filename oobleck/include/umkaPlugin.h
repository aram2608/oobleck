#ifndef UMKA_PLUGIN_H
#define UMKA_PLUGIN_H

/**
 * @file umkaPlugin.h
 * @brief Provides wrapper functions for the creation of an Umka context for editor plugin purposes
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "umka_api.h"

/**
 * @brief Function to load a file's contents
 * 
 * Takes a C string as an argument and returns a C string
 * The caller is responsible for freeing the allocated memory of the buffer
 * 
 * @param filePath The path to the Umka script

 * @return A C string of the loaded script
 */
const char* loadUmkaScriptFromFile(const char* filePath);

// Function to load an Umka context from a filePath
// Takes a C string for the filepath and command line args as the arguments
// Returns a pointer to an Umka context

/**
 * @brief Function used to create an Umka context
 * 
 * @param filePath The path to the Umka Script
 * @param argc The command line argument number
 * @param argv The command line arguments
 * @return A pointer to the Umka context
 */
Umka* loadUmka(const char* filePath, int argc, char** argv);

#endif // UMKA_PLUGIN_H
