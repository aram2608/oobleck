# Compiler
CC := gcc

# Build directory and target
APP := ./oobleck
BUILD_DIR := ./build
TARGET := main

# Source directory and source files
SRC_DIR := $(APP)/src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Includes
INCLUDES := $(APP)/include

# Library directory
LIB_DIR := $(APP)/libs

# Flags for gcc command
INCLUDE_FLAGS := -I$(INCLUDES)
LDFLAGS := -L$(LIB_DIR)
UMKAFLAGS := -lumka_static_darwin
SDLFLAGS := $(shell pkg-config --cflags --libs --static sdl3-ttf)
CFLAGS := -Wall -Wextra -pedantic

$(BUILD_DIR)/$(TARGET):
	@mkdir -p $(@D)
	$(CC) $(INCLUDE_FLAGS) $(SRC_FILES) $(LDFLAGS) $(UMKAFLAGS) $(SDLFLAGS) -o $@ $(CFLAGS)