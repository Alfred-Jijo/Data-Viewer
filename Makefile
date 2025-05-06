# Makefile for C++ Template Project

# Variables
NAME = data-viewer
VERSION = 0.0.1
PREFIX ?= $(HOME)/.local

CXX ?= g++
CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++20

CC ?= gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99

CXXSRC = src/main.cpp lib/file_operations.cpp
CSRC = lib/ds.c
OBJ = $(CXXSRC:%.cpp=%.o) $(CSRC:%.c=%.o)
INCLUDE = -Iinclude

# Default target
all: $(NAME)

# Compile target
$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $(NAME)

# Rule to compile source files
.cpp.o:
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDE)

.c.o:
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

# Run target
run: $(NAME)
	./$(NAME)

# Clean target
clean:
	$(RM) $(OBJ)
	$(RM) $(NAME)

# Phony targets
.PHONY: all run clean
