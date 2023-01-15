OBJS = $(wildcard src/*.cpp)
CC = clang++
INCLUDE_PATHS = -I/usr/local/include
LIBRARY_PATHS = -L/usr/local/lib
COMPILER_FLAGS = -std=c++11 -Wall -O2
LINKER_FLAGS = -lSDL2 -lSDL2_image
OBJ_NAME = pacman

main:
	$(CC) -g -o $(OBJ_NAME) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(OBJS) src/actors/*.cpp src/components/*.cpp