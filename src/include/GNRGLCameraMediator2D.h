/**
 * GNRGLCameraMediator2D
 * @note        [FINISHED]
 * @name        GNRGLCameraMediator2D.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRGLCAMERAMEDIATOR2D_H
#define GNRGLCAMERAMEDIATOR2D_H

#include "GNRGLCameraMediator.h"

class GNRGLCameraMediator2D: public GNRGLCameraMediator
{

private:

	void MoveXY(GNRGLNotifyEvent& event);
	void MoveXZ(GNRGLNotifyEvent& event);
	void RotateXY(GNRGLNotifyEvent& event);
	void RotateXZ(GNRGLNotifyEvent& event);
	void ZoomIn(GNRGLNotifyEvent& event);
	
};

#endif // GNRGLCAMERAMEDIATOR_H
