#Makefile fuer linux
# $<	erste Abhängigkeit
# $@	Name des Targets
# $+	Liste aller Abhängigkeiten
# $^	^^ ohne Wiederholungne


.PHONY: clean all co up ci st
TARGET = gnr/bin/GNR

CC = g++
CFLAGS =-Wall -finput-charset=iso-8859-1#-pedantic -ansi -Wall
CXX = $(CC) $(CFLAGS) -Ignr/src/include
LD = $(CC)

WX_COPTS = $(shell wx-config --cxxflags)
WX_LOPTS = $(shell wx-config --libs gl,core,base)

all: $(TARGET)

gnr/bin/GNR: gnr/bin/GNRApp.o gnr/bin/GNRAssembly.o gnr/bin/GNRDebugFrame.o gnr/bin/GNRFace.o gnr/bin/GNRGL2DCanvas.o gnr/bin/GNRGL3DCanvas.o gnr/bin/GNRGLCanvas.o gnr/bin/GNRMain.o gnr/bin/GNRMaterial.o gnr/bin/GNRMaterialImport.o gnr/bin/GNRModelsPanel.o gnr/bin/GNRMouse.o gnr/bin/GNRObjectImport.o gnr/bin/GNRPoint3d.o gnr/bin/GNRTreePanel.o gnr/bin/GNRVertex.o gnr/bin/md5.o
	@echo ... LINKING ...
	$(LD) -o $(TARGET) $(WX_LOPTS) $^

gnr/bin/%.o: gnr/src/%.cpp
	$(CXX) $(WX_COPTS) -c $< -o $@
	
co:
	svn checkout https://gnr.googlecode.com/svn/trunk/ gnr --username K.Balabin
up:
	svn update gnr
ci:
	svn commit gnr
st:
	@echo $(shell svn status gnr | grep "^M")

clean: 
	rm -f gnr/bin/*.o gnr/bin/GNR
