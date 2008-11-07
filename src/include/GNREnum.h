/**
 * GNREnum
 * @name       GNREnum.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRENUM_H
#define GNRENUM_H

enum eventType  { GLREFRESH = 0, NEWROOM, OPXOPEN, OPXSAVE, OAXIMPORT, OAXEXPORT, OBJIMPORT, OBJEXPORT, TOOLBARCHANGE,
                  RESETCAMERA, SNAPTOGRID, PANELSIZE, SCREENSHOT, UNDO, REDO, SETUNDOENABLED, SETREDOENABLED, CREATEGROUP,
                  MODIFYGROUP, DELETESELECTED, DISPLAYLENGTH, CLONESELECTED, COPYSELECTED, INSERTCOPY,
                  CUTSELECTED, HIDESELECTED, CANCELCONVERTION, TOGGLESHADOWS, REFRESHSCENETREE, EMPTYTRASH, RESETOBJECT
                };

enum treeEventType { LIBRARYDELETE, LIBRARYPASTE, LIBRARYEXPORT, LIBRARYNEWCAT, LIBRARYRENAME, LIBRARYMENURENAME, SCENEVISIBLE, SCENEHIDE,
                     SCENESELECT, SCENEDESELECT, SCENEDELETE, SCENEUNDELETE
                   };
enum transType    { MOVEXZ = 0, MOVEXY, ROTATEXY, ROTATEXZ, DRAWWALL };
enum buttonType   { LEFT_BUTTON = 1, MIDDLE_BUTTON, RIGHT_BUTTON };
enum canvasType   { NONE = 1, CANVAS2D, CANVAS3D, CANVASPREVIEW };
enum assemblyType { IS_ROOT = 0, IS_SELECTED, IS_TRASH, IS_ATOMIC, IS_WALL, IS_PRIMITIVE, IS_GROUP, IS_OBJECT,
                    IS_WRAPPER, IS_DUPLICATOR
                  };
enum primitivesType { CUBOID = 0 };
enum { X, Y, Z, W };
enum { A, B, C, D };

#endif // GNRENUM_H
