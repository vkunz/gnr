/**
 * Enum
 * @name       Enum.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _ENUM_H_
#define _ENUM_H_

//defined event types
enum eventType    { GLREFRESH = 0,
                    NEWROOM,
                    OPXOPEN,
                    OPXSAVE,
                    OAXIMPORT,
                    OAXEXPORT,
                    OBJOAXCONVERSION,
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
                    TOGGLECANVAS2DACTIVE,
                    REFRESHSCENETREE,
                    EMPTYTRASH,
                    RESETOBJECT,
                    CREATECUBOID,
                    CREATESPHERE,
                    CREATECYLINDER,
                    DEBUG1,
                    DEBUG2,
                    DEBUG3,
                    OPXIMPORTFINISHED
                  };

//defined tree event types
enum treeEventType { LIBRARYDELETEENTRY,
                     LIBRARYDELETECAT,
                     LIBRARYMOVE,
                     LIBRARYPASTE,
                     LIBRARYEXPORT,
                     LIBRARYNEWCAT,
                     LIBRARYMENURENAMEENTRY,
                     LIBRARYMENURENAMECAT,
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
                    DRAWWALL,
                    MEASURING
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
                    IS_TRASH,
                    IS_DUPLICATOR,
                    IS_SELECTED,
                    IS_PRIMITIVE,
                    IS_GROUP,
                    IS_OBJECT,
                    IS_WRAPPER,
                    IS_ATOMIC,
                    IS_WALL,
                    IS_ORIGINAL
                  };

//defined primitive types
enum primitiveType { OTHER = 0,
                     CUBOID,
                     CYLINDER,
                     SPHERE
                   };

//defined for better reading formulas
enum { X, Y, Z, W };
enum { A, B, C, D };
enum { RED, GREEN, BLUE, ALPHA };

#endif // _ENUM_H_
