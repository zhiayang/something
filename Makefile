WERROR?=-Werror
PKGS=sdl2 SDL2_ttf
CFLAGS=-Wall -Wextra $(WERROR) -pedantic -I.
CXXFLAGS=$(CFLAGS) -std=c++17 -fno-exceptions $(shell pkg-config --cflags $(PKGS))
CXXFLAGS_DEBUG=$(CXXFLAGS) -O0 -fno-builtin -ggdb
CXXFLAGS_RELEASE=$(CXXFLAGS) -DSOMETHING_RELEASE -O3 -ggdb
LIBS=$(shell pkg-config --libs $(PKGS)) -lm

.PHONY: all
all: something.debug something.release

something.debug: $(wildcard src/something*.cpp) $(wildcard src/something*.hpp) stb_image.o
	$(CXX) $(CXXFLAGS_DEBUG) -o something.debug src/something.cpp stb_image.o $(LIBS)

something.release: $(wildcard src/something*.cpp) $(wildcard src/something*.hpp) baked_config.hpp
	$(CXX) $(CXXFLAGS_RELEASE) -o something.release src/something.cpp $(LIBS)

stb_image.o: src/stb_image.h
	$(CC) $(CFLAGS) -x c -ggdb -DSTB_IMAGE_IMPLEMENTATION -c -o stb_image.o src/stb_image.h

baked_config.hpp: config_baker ./assets/config.vars
	./config_baker > baked_config.hpp

config_baker: src/config_baker.cpp src/common_string.cpp src/common_config.cpp src/common_print.cpp
	$(CXX) $(CXXFLAGS_DEBUG) -o config_baker src/config_baker.cpp
