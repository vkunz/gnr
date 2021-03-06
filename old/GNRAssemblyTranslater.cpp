/**
 * GNRAssemblyTranslater
 * @name        GNRAssemblyTranslater.cpp
 * @date        2008-10-09
 * @author      Konstantin Balabin  <k.balabin@googlemail.com>
 * @author      Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author      Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author      Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/math.h>

#include "GNRAssembly.h"
#include "GNRAssemblyTranslater.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of GNRAssemblyTranslater
 * @access      public
 */
GNRAssemblyTranslater::GNRAssemblyTranslater(GNRGLCamera* camera)
{
	init();
	m_glcamera = camera;
}

/**
 * destructor of GNRAssemblyTranslater
 * @access      public
 */
GNRAssemblyTranslater::~GNRAssemblyTranslater()
{
}

/**
 * init method for setting up the mouse controller
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      public
 */
void GNRAssemblyTranslater::setWindow(GNRGLNotifyEvent& event)
{
	window_w = event.getWinX();
	window_h = event.getWinY();
}

/**
 * set moving direction
 * @param       int         direction xz(0), xy(1) or rotation(2)
 * @access      public
 */
void GNRAssemblyTranslater::setDirection(transType dir)
{
	status = dir;
//	switch (dir)
//	{
//	case MOVEXZ:
//		status = MOVEXZ;
//		break;
//	case MOVEXY:
//		status = MOVEXY;
//		break;
//	case ROTATEXY:
//		status = ROTATEXY;
//		break;
//	case ROTATEXZ:
//		status = ROTATEXZ;
//		break;
//	default:
//		status = MOVEXZ;
//		break;
//	}
}

/**
 * init method for setting up the mouse controller
 * @access      protected
 */
void GNRAssemblyTranslater::init()
{
	//controller not in use
	in_use = false;
	
	//set default to move XZ axis
	status = MOVEXZ;
	
	//my_object to null pointer
	my_object = NULL;
}

/**
 * set assembly pointer
 * @param       GNRAssembly     pointer to assembly object
 * @access      public
 */
void GNRAssemblyTranslater::setAssembly(GNRAssembly* assembly)
{
	//store object pointer
	if ((int)assembly != 0)
	{
		my_object = (GNRAssembly*) assembly;
	}
}

/**
 * fetches control of mouse class
 * @param       GNRGLNotifyEvent    event from GLNotify
 * @return      boolean             status of get action
 * @access      public
 */
bool GNRAssemblyTranslater::getControl(GNRGLNotifyEvent& event)
{
	//if in use return false
	if (in_use)
	{
		return false;
	}
	//set usage true
	in_use = true;
	
	//store old position + rotation values
	if (event.getMouseEvent().ButtonDown(1))
	{
		window_w = event.getWinX();
		window_h = event.getWinY();
		
		old_x = my_object->getX();
		old_y = my_object->getY();
		old_z = my_object->getZ();
		
		phi_old   = my_object->getPhi();
		theta_old = my_object->getTheta();
		rho_old   = my_object->getRho();
		
		gl_xmax = event.getWorldXmax();
		gl_ymax = event.getWorldYmax();
		gl_xmin = event.getWorldXmin();
		gl_ymin = event.getWorldYmin();
	}
	
	//store actual mouse coords on control
	m_mouse_x = event.getMouseEvent().m_x;
	m_mouse_y = event.getMouseEvent().m_y;
	
	return true;
}

/**
 * frees the controler for other clients
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      public
 */
void GNRAssemblyTranslater::dropControl(GNRGLNotifyEvent& event)
{
	//set in use false
	in_use = false;
}

/**
 * transforming selected object on mouse event
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      public
 */
void GNRAssemblyTranslater::ObjectTransform(GNRGLNotifyEvent& event)
{
	if (in_use)
	{
		switch (status)
		{
		case MOVEXZ:
			ObjectMoveXZ(event);
			break;
		case MOVEXY:
			ObjectMoveXY(event);
			break;
		case ROTATEXY:
			ObjectRotateXY(event);
			break;
		case ROTATEXZ:
			ObjectRotateXZ(event);
			break;
		default:
			ObjectMoveXZ(event);
			break;
		}
	}
	if (event.getMouseEvent().ButtonIsDown(2))
	{
		// moving the camera needs to update mouse-coordinates every mouse-move event
		m_mouse_x = event.getMouseEvent().GetX();
		m_mouse_y = event.getMouseEvent().GetY();
	}
}

/**
 * rotate the object on XY axis
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      protected
 */
void GNRAssemblyTranslater::ObjectRotateXY(GNRGLNotifyEvent& event)
{
	if (event.getMouseEvent().ButtonIsDown(1))
	{
		// rotate a single object
		my_object->setPhi(phi_old + 720.0f*((float)(m_mouse_y - event.getMouseEvent().m_y)/(float)window_h));
		my_object->setTheta(theta_old + 720.0f*((float)(m_mouse_x - event.getMouseEvent().m_x)/(float)window_w));
	}
	else if (event.getMouseEvent().ButtonIsDown(2))
	{
		// rotate the whole scene (by using the camera-class)
		m_glcamera->rotateX((float)(m_mouse_y - event.getMouseEvent().GetY())/-3.0f);
		m_glcamera->rotateY((float)(m_mouse_x - event.getMouseEvent().GetX())/-3.0f);
	}
}

/**
 * rotate the object on XZ axis
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      protected
 */
void GNRAssemblyTranslater::ObjectRotateXZ(GNRGLNotifyEvent& event)
{
	if (event.getMouseEvent().ButtonIsDown(1))
	{
		// rotate a single object
		my_object->setPhi(phi_old + 720.0f*((float)(m_mouse_y - event.getMouseEvent().m_y)/(float)window_h));
		my_object->setRho(rho_old + 720.0f*((float)(m_mouse_x - event.getMouseEvent().m_x)/(float)window_w));
	}
	else if (event.getMouseEvent().ButtonIsDown(2))
	{
		// rotate the whole scene (by using the camera-class)
		m_glcamera->rotateX((float)(m_mouse_y - event.getMouseEvent().GetY())/-3.0f);
		m_glcamera->rotateZ((float)(m_mouse_x - event.getMouseEvent().GetX())/-3.0f);
	}
}

/**
 * move the object in XY dimension
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      protected
 */
void GNRAssemblyTranslater::ObjectMoveXY(GNRGLNotifyEvent& event)
{
	if (event.getMouseEvent().ButtonIsDown(1))
	{
		// Moving a single object
		if (event.getCanvasID() == 2)
		{
			// klick is from 2D canvas
			float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().m_x)/(float)window_w;
			float new_y = old_y - (gl_ymax-gl_ymin)*(event.getMouseEvent().m_y - m_mouse_y)/(float)window_h*2.0;
			if (new_y < my_object->getOverGround())
			{
				new_y = my_object->getOverGround();
			}
			my_object->setX(new_x);
			my_object->setY(new_y);
		}
		else
		{
			// klick is from 3D canvas
			float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().m_x)/(float)window_w;
			float new_y = old_y - (gl_ymax-gl_ymin)*(event.getMouseEvent().m_y - m_mouse_y)/(float)window_h;
			if (new_y < my_object->getOverGround())
			{
				new_y = my_object->getOverGround();
			}
			my_object->setX(new_x);
			my_object->setY(new_y);
		}
	}
	else if (event.getMouseEvent().ButtonIsDown(2))
	{
		// Moving the whole scene (by using the camera-class)
		m_glcamera->moveUpward((float)(m_mouse_y - event.getMouseEvent().GetY())/-20.0f);
		m_glcamera->strafeRight((float)(m_mouse_x - event.getMouseEvent().GetX())/20.0f);
	}
}

/**
 * move the object in XZ dimension
 * @param       GNRGLNotifyEvent         event from GLNotify
 * @access      protected
 */
void GNRAssemblyTranslater::ObjectMoveXZ(GNRGLNotifyEvent& event)
{
	if (event.getMouseEvent().ButtonIsDown(1))
	{
		// Moving a single object
		if (event.getCanvasID() == 2)
		{
			// klick is from 2D canvas
			float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().m_x)/(float)window_w;
			float new_z = old_z - (gl_xmax-gl_xmin)/(float)window_w*(m_mouse_y - event.getMouseEvent().m_y);
			my_object->setX(new_x);
			my_object->setZ(new_z);
		}
		else
		{
			// klick is from 3D canvas
			float new_x = old_x - (gl_xmax-gl_xmin)*(m_mouse_x - event.getMouseEvent().m_x)/(float)window_w;
			float new_z = old_z - (m_mouse_y - event.getMouseEvent().m_y)/90.0f;
			my_object->setX(new_x);
			my_object->setZ(new_z);
		}
	}
	else if (event.getMouseEvent().ButtonIsDown(2))
	{
		// Moving the whole scene (by using the camera-class)
		m_glcamera->moveForward((float)(m_mouse_y - event.getMouseEvent().GetY())/15.0f);
		m_glcamera->strafeRight((float)(m_mouse_x - event.getMouseEvent().GetX())/20.0f);
	}
}

/**
 * check usage of mouse controller
 * @return      boolean         status of usage
 * @access      public
 */
bool GNRAssemblyTranslater::isInUse()
{
	return in_use;
}

/**
 * set pointer to camera
 * @access      public
 */
void GNRAssemblyTranslater::setGLCamera(GNRGLCamera* camera)
{
	m_glcamera = camera;
}
