/**
 * GNRGlobalDefine
 * @name       GNRGlobalDefine
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRGLOBALDEFINE_H
#define GNRGLOBALDEFINE_H

#define SNAP_IN_DEFAULT_GRID    500           //  500mm default
#define SNAP_IN_DEFAULT_ANGLE    10           //   45° default
#define SNAP_IN_MAXIMUM_UNIT   5000           // 5000mm maximum grid snap
#define SNAP_IN_MINIMUM_UNIT     10           //   10cm minimum grid snap
#define SNAP_IN_MAXIMUM_DEGREE   90           //   90° maximum degree
#define SNAP_IN_MINIMUM_DEGREE   10           //   10° minimum degree
#define SNAP_APPROACH_PERC        0.25f       //   25% of reached snap value

#define CAMERA_HEIGHT_MIN         1.00        //   10cm minimum height of cam
#define CAMERA_DISTANCE_MIN       1.00        //  100cm minimum distance of cam

#define DEFAULT_FLOOR_SIZE       64
#define DEFAULT_IMPORT_COLOR    "archwhite2"

#define ZNEAR                     0.001f      // near clipping plane of GL
#define ZFAR                    100.0f        // far clipping plane of GL
#define GLU_PERSPECTIVE          30.0f        // gluPerspective

#define WALLHIGHT                2.0          // hight of a wall
#define WALLDEPTH                0.2          // thickness of a wall

#endif // GNRENUM_H
