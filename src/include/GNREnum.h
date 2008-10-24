#ifndef GNRENUM_H
#define GNRENUM_H

enum eventType  { GLRefresh, XMLOpen, OBJImport, ToolbarChange, NewRoom, ResetCamera};
enum transType  { MOVEXZ = 0, MOVEXY, ROTATEXY, ROTATEXZ };
enum buttonType { LEFT_BUTTON = 1, MIDDLE_BUTTON, RIGHT_BUTTON };
enum canvasType { NONE = 1, CANVAS2D, CANVAS3D };

#endif // GNRENUM_H
