# Compiler
CC := gcc

# Build directory and target
BUILD_DIR := ./build
TARGET := main

# Source directory and source files
SRC_DIR := ./src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Include and lib directories
INCLUDES := ./include
LIB_DIR := ./lib

# Flags for gcc command
INCLUDE_FLAG := -I$(INCLUDES)
LDFLAGS := -L$(LIB_DIR)
UMKA_FLAG := -lumka_static_darwin
CFLAGS := -Wall -Wextra -pedantic

$(BUILD_DIR)/$(TARGET):
	@mkdir -p $(@D)
	$(CC) $(INCLUDE_FLAG) $(SRC_FILES) $(LDFLAGS) $(UMKA_FLAG) -o $@ $(CFLAGS)