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

//defined event types
enum eventType    { GLREFRESH = 0,
                    NEWROOM,
                    OPXOPEN,
                    OPXSAVE,
                    OAXIMPORT,
                    OAXEXPORT,
                    OBJIMPORT,
                    OBJEXPORT,
                    TOOLBARCHANGE,
                    RESETCAMERA,
                    SNAPTOGRID,
                    PANELSIZE,
                    SCREENSHOT,
                    UNDO,
                    REDO,
                    SETUNDOENABLED,
                    SETREDOENABLED,
                    CREATEGROUP,
                    MODIFYGROUP,
                    DELETESELECTED,
                    DISPLAYLENGTH,
                    CLONESELECTED,
                    COPYSELECTED,
                    INSERTCOPY,
                    CUTSELECTED,
                    HIDESELECTED,
                    CANCELCONVERTION,
                    TOGGLESHADOWS,
                    REFRESHSCENETREE,
                    EMPTYTRASH,
                    RESETOBJECT,
                    CREATECUBOID,
                    CREATESPHERE,
                    CREATECONE,
                    CREATECYLINDER,
                    CREATEPYRAMIDE
                  };

//defined tree event types
enum treeEventType { LIBRARYDELETE,
                     LIBRARYPASTE,
                     LIBRARYEXPORT,
                     LIBRARYNEWCAT,
                     LIBRARYRENAME,
                     LIBRARYMENURENAME,
                     SCENEVISIBLE,
                     SCENEHIDE,
                     SCENESELECT,
                     SCENEDESELECT,
                     SCENEDELETE,
                     SCENEUNDELETE
                   };

//defined translation types
enum transType    { MOVEXZ = 0,
                    MOVEXY,
                    ROTATEXY,
                    ROTATEXZ,
                    DRAWWALL
                  };

//defined button types
enum buttonType   { LEFT_BUTTON = 1,
                    MIDDLE_BUTTON,
                    RIGHT_BUTTON
                  };

//defined canvas types
enum canvasType   { NONE = 1,
                    CANVAS2D,
                    CANVAS3D,
                    CANVASPREVIEW
                  };

//defined assembly types
enum assemblyType { IS_ROOT = 0,
                    IS_SELECTED,
                    IS_TRASH,
                    IS_ATOMIC,
                    IS_WALL,
                    IS_PRIMITIVE,
                    IS_GROUP,
                    IS_OBJECT,
                    IS_WRAPPER,
                    IS_ORIGINAL,
                    IS_DUPLICATOR
                  };

//defined primitive types
enum primitivesType { CUBOID = 0,
                      CYLINDER,
                      CONE,
                      SPHERE,
                      PYRAMIDE
                    };

//defined for better reading formulas
enum { X, Y, Z, W };
enum { A, B, C, D };
enum { RED, GREEN, BLUE, ALPHA };

#endif // GNRENUM_H
