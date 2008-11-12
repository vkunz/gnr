/**
 * GlobalDefine
 * @name       GlobalDefine
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GLOBALDEFINE_H
#define GLOBALDEFINE_H

#define SNAP_IN_DEFAULT_GRID    500           //  500mm default
#define SNAP_IN_DEFAULT_ANGLE    45           //   45° default
#define SNAP_IN_MAXIMUM_UNIT   5000           // 5000mm maximum grid snap
#define SNAP_IN_MINIMUM_UNIT     10           //   10cm minimum grid snap
#define SNAP_IN_MAXIMUM_DEGREE   90           //   90° maximum degree
#define SNAP_IN_MINIMUM_DEGREE   10           //   10° minimum degree
#define SNAP_APPROACH_PERC        0.25f       //   25% of reached snap value

#define CAMERA_HEIGHT_MIN         0.010       //  10mm minimum height of cam, dont go negative
#define CAMERA_DISTANCE_MIN       0.010       //  10mm minimum distance of cam, dont go negative

#define DEFAULT_FLOOR_SIZE       128
#define DEFAULT_IMPORT_COLOR    "default"

#define ZNEAR                     0.001f      // near clipping plane of GL
#define ZFAR                    500.0f        // far clipping plane of GL
#define GLU_PERSPECTIVE          30.0f        // gluPerspective

#define WALLHEIGHT               2.0          // height of a wall
#define WALLDEPTH                0.2          // thickness of a wall

#define SIZE_MAXIMUM_VALUE   50000            // 50000mm = 50m
#define SIZE_MINIMUM_VALUE      10            // 10mm (smallest amount)

#define SOFTWARE_TITLE         "GNR 3D Raumplaner - Die Einrichtungssoftware"
#define SOFTWARE_VERSION       "0.5.4.2 BETA" //additional version info
#define SOFTWARE_WIN_WIDTH     800            //width of application window
#define SOFTWARE_WIN_HEIGHT    600            //height of application windows

#define SHADOWS_DEFAULT      false
#define SNAP_TO_GRID_DEFAULT  true

#endif // ENUM_H
