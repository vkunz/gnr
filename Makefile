#Makefile fuer linux
# $<	erste Abhängigkeit
# $@	Name des Targets
# $+	Liste aller Abhängigkeiten
# $^	^^ ohne Wiederholungne

.PHONY: clean all co up ci st btf
TARGET = gnr/GNR

CC = g++
CFLAGS = -g -finput-charset=iso-8859-1 #-D__ATHOS_DEBUG__ #-Wall -pedantic -ansi
CXX = $(CC) $(CFLAGS) -Ignr/src/include
LD = $(CC)

WX_COPTS = $(shell wx-config --cppflags)
## Mandriva's wx-config is BUGGY!
#WX_LOPTS = $(shell wx-config --libs gl,core,base)
WX_LOPTS = -pthread -lwx_gtk2_gl-2.8 -lwx_gtk2_core-2.8 -lwx_base-2.8 -lwx_base_xml-2.8 -lwx_gtk2_adv-2.8 -lwx_gtk2_html-2.8
GL_LIBS = -lGL -lGLU

all: $(TARGET)

$(TARGET): gnr/bin/GNRApp.o gnr/bin/GNRAssembly.o gnr/bin/GNRAssemblyMediator2D.o gnr/bin/GNRAssemblyMediator3D.o gnr/bin/GNRAssemblyMediator.o gnr/bin/GNRCommandTransform.o gnr/bin/GNRCreatePrimitiveEvent.o gnr/bin/GNRDebugFrame.o gnr/bin/GNRFace.o gnr/bin/GNRGLCamera.o gnr/bin/GNRGLCameraMediator2D.o gnr/bin/GNRGLCameraMediator3D.o gnr/bin/GNRGLCameraMediator.o gnr/bin/GNRGLCanvas2D.o gnr/bin/GNRGLCanvas3D.o gnr/bin/GNRGLCanvas.o gnr/bin/GNRGLCanvasPreview.o gnr/bin/GNRGLNotifyEvent.o gnr/bin/GNRGLScreenshot.o gnr/bin/GNRHelpFrame.o gnr/bin/GNRImportFile.o gnr/bin/GNRLibraryCategory.o gnr/bin/GNRLibrary.o gnr/bin/GNRLibraryEntry.o gnr/bin/GNRLineDrawEvent.o gnr/bin/GNRMainFrame.o gnr/bin/GNRMaterial.o gnr/bin/GNRMaterialLibrary.o gnr/bin/GNRMediator.o gnr/bin/GNRMouseController.o gnr/bin/GNRNotifyEvent.o gnr/bin/GNROaxExport.o gnr/bin/GNROaxImport.o gnr/bin/GNRObjectImport.o gnr/bin/GNRObjOaxConverter.o gnr/bin/GNRObjOaxConverterFrame.o gnr/bin/GNROpxExport.o gnr/bin/GNROpxImport.o gnr/bin/GNRPrimitiveCreator.o gnr/bin/GNRScene.o gnr/bin/GNRSceneTreeNode.o gnr/bin/GNRTCoord.o gnr/bin/GNRTests.o gnr/bin/GNRTreeControlEvent.o gnr/bin/GNRTreeLibraryController.o gnr/bin/GNRTreePanelLibrary.o gnr/bin/GNRTreePanelMyScene.o gnr/bin/GNRTreeSceneController.o gnr/bin/GNRTreeSceneCtrl.o gnr/bin/GNRTreeSceneItemData.o gnr/bin/GNRUndoRedo.o gnr/bin/GNRVertex.o gnr/bin/GNRVNT.o gnr/bin/GNRWallMediator.o gnr/bin/md5.o
	@echo ... LINKING ...
	$(LD) $(WX_LOPTS) $(GL_LIBS) $^ -o $@
	
gnr/bin/%.o: gnr/src/%.cpp gnr/src/include/%.h
	$(CXX) $(WX_COPTS) -c $< -o $@

run: $(TARGET)
	$(TARGET)
btf:
	astyle --style=linux --indent=tab --mode=c -b -R -U -E gnr/src/*.cpp gnr/src/include/*.h
co:
	svn checkout https://gnr.googlecode.com/svn/trunk/ gnr --username K.Balabin
up:
	svn update gnr
ci: btf
	svn commit gnr
st:
	@echo $(shell svn status gnr | grep "^M")

clean: 
	rm -f gnr/bin/*.o $(TARGET)
