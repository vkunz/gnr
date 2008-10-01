#Makefile fuer linux

.PHONY: clean all co up ci st
TARGET = bin/GNR

CC = g++
CFLAGS =-Wall -finput-charset=iso-8859-1#-pedantic -ansi -Wall
CXX = $(CC) $(CFLAGS) -Isrc/include
LD = $(CC)

GL_LIBS =-lGL -lGLU
WX_COPTS = $(shell wx-config --cxxflags)
WX_LOPTS = $(shell wx-config --libs gl,core,base)

bin/GNR: bin/GNRApp.o bin/GNRMain.o
	$(LD) -o $(TARGET) bin/GNRApp.o bin/GNRMain.o $(WX_LOPTS)

bin/GNRApp.o: src/GNRApp.cpp src/include/GNRApp.h
	$(CXX) $(WX_COPTS) -c src/GNRApp.cpp -o bin/GNRApp.o

bin/GNRMain.o: src/GNRApp.cpp src/include/GNRMain.h
	$(CXX) $(WX_COPTS) -c src/GNRMain.cpp -o bin/GNRMain.o

all: $(TARGET)

co: 
	svn checkout https://gnr.googlecode.com/svn/trunk/ ../gnr --username K.Balabin
up:
	svn update
ci:
	svn commit
st:
	@echo $(shell svn status | grep "^M")
clean: 
	rm -f bin/*.o bin/GNR
