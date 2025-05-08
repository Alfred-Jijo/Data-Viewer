# Makefile for C++ Template Project

# Variables
NAME = data-viewer
VERSION = 0.2.5
PREFIX ?= $(HOME)/.local

BUILD ?= debug
OUTDIR = out/$(BUILD)
OUTNAME = $(OUTDIR)/$(NAME)

CXX ?= g++
CC ?= gcc

# Base flags
BASE_CXXFLAGS = -Wall -Wextra -Werror -pedantic -std=c++20
BASE_CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99

# Build-specific flags
ifeq ($(BUILD),release)
	CXXFLAGS = $(BASE_CXXFLAGS) -O2 -D_DEBUG
	CFLAGS = $(BASE_CFLAGS) -O2 -D_DEBUG
else
	CXXFLAGS = $(BASE_CXXFLAGS) -g -DDEBUG
	CFLAGS = $(BASE_CFLAGS) -g -DDEBUG
endif

CXXSRC = src/main.cpp lib/viewer.cpp
CSRC =  
OBJ = $(CXXSRC:%.cpp=%.o) $(CSRC:%.c=%.o)
INCLUDE = -Iinclude

# Default target
all: $(OUTNAME)

# Link target
$(OUTNAME): $(OBJ)
	mkdir -p $(OUTDIR)
	$(CXX) $(OBJ) -o $(OUTNAME)

# Pattern rule for C++ files
%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(INCLUDE)

# Pattern rule for C files
%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

# Run target
run: $(OUTNAME)
	./$(OUTNAME)

# Clean target
clean:
	$(RM) -r $(OUTDIR)
	$(RM) $(OBJ)

# Phony targets
.PHONY: all run clean