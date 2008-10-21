#Makefile fuer linux
# $<	erste Abhängigkeit
# $@	Name des Targets
# $+	Liste aller Abhängigkeiten
# $^	^^ ohne Wiederholungne


.PHONY: clean all co up ci st
TARGET = gnr/GNR

CC = g++
CFLAGS =-D__ATHOS_DEBUG__ -g -Wall -finput-charset=iso-8859-1#-pedantic -ansi -Wall
CXX = $(CC) $(CFLAGS) -Ignr/src/include
LD = $(CC)

WX_COPTS = $(shell wx-config --cppflags)
## Mandriva's wx-config is BUGGY!
#WX_LOPTS = $(shell wx-config --libs gl,core,base)
WX_LOPTS = -pthread -lwx_gtk2_gl-2.8 -lwx_gtk2_core-2.8 -lwx_base-2.8 
GL_LIBS = -lGL -lGLU

all: $(TARGET)

$(TARGET): gnr/bin/GNRApp.o gnr/bin/GNRAssembly.o gnr/bin/GNRAssemblyTranslater.o gnr/bin/GNRController.o gnr/bin/GNRDebugFrame.o gnr/bin/GNRFace.o gnr/bin/GNRGL2DCanvas.o gnr/bin/GNRGL3DCanvas.o gnr/bin/GNRGLCamera.o gnr/bin/GNRGLCanvas.o gnr/bin/GNRGLNotifyEvent.o gnr/bin/GNRMainFrame.o gnr/bin/GNRMaterial.o gnr/bin/GNRMaterialImport.o gnr/bin/GNRNotifyEvent.o gnr/bin/GNRObjectImport.o gnr/bin/GNRPoint3d.o gnr/bin/GNRTreePanel.o gnr/bin/GNRVertex.o gnr/bin/md5.o gnr/bin/TestCanvas.o
	@echo ... LINKING ...
	$(LD) $(WX_LOPTS) $(GL_LIBS) $^ -o $@
	

gnr/bin/%.o: gnr/src/%.cpp gnr/src/include/%.h
	$(CXX) $(WX_COPTS) -c $< -o $@

run: $(TARGET)
	$(TARGET)
co:
	svn checkout https://gnr.googlecode.com/svn/trunk/ gnr --username K.Balabin
up:
	svn update gnr
ci:
	svn commit gnr
st:
	@echo $(shell svn status gnr | grep "^M")

run: $(TARGET)
	$(TARGET)

clean: 
	rm -f gnr/bin/*.o $(TARGET)
