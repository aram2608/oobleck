# Compiler
CC := clang

# Build directory and target
APP := ./oobleck
BUILD_DIR := ./build
TARGET := oobleck

# Source directory and source files
SRC_DIR := $(APP)/src
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Includes
INCLUDES := $(APP)/include

# Library directory
LIB_DIR := $(APP)/libs

# Flags for gcc command
INCLUDE_FLAGS := -I$(INCLUDES)
UMKAFLAGS := -L$(LIB_DIR) -lumka_static_darwin
SDLFLAGS := $(shell pkg-config --cflags --libs --static sdl3-ttf)
GLFLAGS := -I/opt/homebrew/Cellar/glfw/3.4/include -L/opt/homebrew/Cellar/glfw/3.4/lib -lglfw3 -framework Cocoa -framework IOKit -framework CoreFoundation
GLEWFLAGS := $(shell pkg-config --cflags --libs --static glew)
CFLAGS := -g -Wall -Wextra -pedantic -framework OpenGL

$(BUILD_DIR)/$(TARGET):
	@mkdir -p $(@D)
	$(CC) $(INCLUDE_FLAGS) $(UMKAFLAGS) $(SDLFLAGS) $(GLFLAGS) $(GLEWFLAGS) $(CFLAGS) -o $@ $(SRC_FILES)