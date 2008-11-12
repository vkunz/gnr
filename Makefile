#Makefile fuer linux
# $<	erste Abhängigkeit
# $@	Name des Targets
# $+	Liste aller Abhängigkeiten
# $^	^^ ohne Wiederholungne

.PHONY: clean all co up ci st btf
TARGET = gnr/GNR

CC = g++
CFLAGS = -g -finput-charset=iso-8859-1 -D__ATHOS_DEBUG__ #-Wall -pedantic -ansi
CXX = $(CC) $(CFLAGS) -Ignr/src/include
LD = $(CC)

WX_COPTS = $(shell wx-config --cppflags)
## Mandriva's wx-config is BUGGY!
#WX_LOPTS = $(shell wx-config --libs gl,core,base)
WX_LOPTS = -pthread -lwx_gtk2_gl-2.8 -lwx_gtk2_core-2.8 -lwx_base-2.8 -lwx_base_xml-2.8 -lwx_gtk2_adv-2.8 -lwx_gtk2_html-2.8
GL_LIBS = -lGL -lGLU

all: $(TARGET)

$(TARGET): gnr/bin/App.o gnr/bin/Assembly.o gnr/bin/AssemblyDataFrame.o gnr/bin/AssemblyMediator2D.o gnr/bin/AssemblyMediator3D.o gnr/bin/AssemblyMediator.o gnr/bin/CommandTransform.o gnr/bin/CreateCuboidFrame.o gnr/bin/CreatePrimitiveEvent.o gnr/bin/DebugFrame.o gnr/bin/Face.o gnr/bin/GLCamera.o gnr/bin/GLCameraMediator2D.o gnr/bin/GLCameraMediator3D.o gnr/bin/GLCameraMediator.o gnr/bin/GLCanvas2D.o gnr/bin/GLCanvas3D.o gnr/bin/GLCanvas.o gnr/bin/GLCanvasPreview.o gnr/bin/GLNotifyEvent.o gnr/bin/GLScreenshot.o gnr/bin/HelpFrame.o gnr/bin/ImportFile.o gnr/bin/LibraryCategory.o gnr/bin/Library.o gnr/bin/LibraryEntry.o gnr/bin/LineDrawEvent.o gnr/bin/MainFrame.o gnr/bin/Material.o gnr/bin/MaterialLibrary.o gnr/bin/md5.o gnr/bin/Mediator.o gnr/bin/MouseController.o gnr/bin/NotifyEvent.o gnr/bin/OaxExport.o gnr/bin/OaxImport.o gnr/bin/ObjectImport.o gnr/bin/ObjOaxConverter.o gnr/bin/ObjOaxConverterFrame.o gnr/bin/OpxExport.o gnr/bin/OpxImport.o gnr/bin/PrimitiveCreator.o gnr/bin/ProgressFrame.o gnr/bin/Scene.o gnr/bin/TCoord.o gnr/bin/Tests.o gnr/bin/TreeControlEvent.o gnr/bin/TreeLibraryController.o gnr/bin/TreeLibraryCtrl.o gnr/bin/TreeLibraryItemData.o gnr/bin/TreePanelLibrary.o gnr/bin/TreePanelMyScene.o gnr/bin/TreeSceneController.o gnr/bin/TreeSceneCtrl.o gnr/bin/TreeSceneItemData.o gnr/bin/UndoRedo.o gnr/bin/Vertex.o gnr/bin/VNT.o gnr/bin/WallMediator.o
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
