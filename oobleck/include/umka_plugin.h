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
 * @brief Function used to create an Umka context
 * 
 * @param filePath The path to the Umka Script
 * @param argc The command line argument number
 * @param argv The command line arguments
 * @return A pointer to the Umka context
 */
Umka* loadUmka(const char* filePath, int argc, char** argv);

#endif // UMKA_PLUGIN_H
