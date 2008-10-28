#ifndef GNRENUM_H
#define GNRENUM_H

enum eventType  { GLREFRESH = 0, NEWROOM, OPXOPEN, OPXSAVE, OAXIMPORT, OAXEXPORT, OBJIMPORT, OBJEXPORT, TOOLBARCHANGE, RESETCAMERA, SNAPTOGRID, PANELSIZE };
enum transType  { MOVEXZ = 0, MOVEXY, ROTATEXY, ROTATEXZ, DRAWWALL };
enum buttonType { LEFT_BUTTON = 1, MIDDLE_BUTTON, RIGHT_BUTTON };
enum canvasType { NONE = 1, CANVAS2D, CANVAS3D };

#endif // GNRENUM_H
