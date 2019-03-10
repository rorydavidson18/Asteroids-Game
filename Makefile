# Makefile for all code in the sp3000 project
# Uses paths for SDL2 and SDL2_Image Libraries
# Installed using homebrew on Mac OS X
# Other systems will require different paths

# LIBRARY PATHS:
# if Mac OS (Darwin) use homebrew SDL2 paths
# if Linux use different paths
# if Windows use windows paths

ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell uname -s)
endif
ifeq ($(detected_OS), Windows)
$(info ************  WINDOWS ************)
SDL2_LIB = C:\mingw_dev_lib\include\SDL2
SDL2_IMAGE_LIB = C:\path\to\SDL2_Image\Headers
SDL2_TTF = C:\path\to\SDL2_TTF\Headers
endif
ifeq ($(detected_OS), Linux)
$(info ************  LINUX ************)
SDL2_LIB = /usr/include/SDL2/
SDL2_IMAGE_LIB = /usr/include/SDL2/
SDL2_TTF = /usr/include/SDL2/
endif
ifeq ($(detected_OS), Darwin)
$(info ************  MAC OS X (Darwin) ************)
SDL2_LIB = /usr/local/Cellar/sdl2/2.0.8/include/SDL2/
SDL2_IMAGE_LIB = /usr/local/Cellar/sdl2_image/2.0.3/include/SDL2/
SDL2_TTF = /usr/local/Cellar/sdl2_ttf/2.0.14/include/SDL2/
endif

# OTHER VARIABLES:
CXX = g++
LIBS = -L$(SDL2_LIB) -L$(SDL2_IMAGE_LIB) -L$(SDL2_TTF) -lSDL2 -lSDL2_image -lSDL2_ttf
CPPFLAGS = -std=c++14 -I$(SDL2_LIB) -I$(SDL2_IMAGE_LIB) -I$(SDL2_TTF) -Iasteroids -Igame -Ilevels -Imap -Imaterials -Iship -I -g -Wall
VPATH = asteroids:game:levels:map:materials:ship
OBJECTS = $(wildcard *.o)
EXE = $(wildcard *.exe)
BUILDDIR = build
TESTDIR = build/tests

# shortcut for compiling object code
define o-command
$(CXX) $(CPPFLAGS) -c -o $@ $<
endef

# shortcut for executable linking
define exe-command
$(CXX) -o $@ $^ $(LIBS)
endef


all: tests exe

# main game executable
exe: $(BUILDDIR)/run_game.exe

# object files
%.o: %.cpp %.hpp
	$(o-command)

# tests
tests: $(TESTDIR)/test-ship.exe

$(TESTDIR)/test-ship.exe: test-ship.o ship.o asteroid.o material.o gold.o silver.o titanium.o
	$(exe-command)

$(TESTDIR)/test-material.exe: test-material.o material.o gold.o silver.o titanium.o
	$(exe-command)

$(TESTDIR)/test-asteroidclass.exe: test-asteroidclass.o asteroid.o material.o gold.o silver.o titanium.o
	$(exe-command)

$(BUILDDIR)/run_game.exe: main.o game.o ship.o asteroid.o material.o gold.o silver.o titanium.o
	$(exe-command)

list:
	find . -type f \( -iname \*.o -o -iname \*.exe \)

clean:
	find . -type f \( -iname \*.o -o -iname \*.exe \) -delete
