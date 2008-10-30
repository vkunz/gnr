/**
 * GNRAssembly
 * @name        GNRAssembly.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssembly.h"

#include <GL/gl.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif
/**
 * constructor of generic assembly
 * @param       string         name of assembly
 * @access      public
 */
GNRAssembly::GNRAssembly(const string& name = "unnamed"):
		m_x(0.0), m_y(0.0), m_z(0.0),
		m_phi(0.0), m_theta(0.0), m_rho(0.0),
		m_scale_x(1.0), m_scale_y(1.0), m_scale_z(1.0),
		m_width(1.0), m_height(1.0), m_depth(1.0),
		m_type(IS_ROOT),
		m_name(name), m_parent(NULL)
{
}

/**
 * constructor of generic assembly with parent
 * @param       string         name of assembly
 * @param       GNRAssembly*   pointer to parent
 * @access      public
 */
GNRAssembly::GNRAssembly(GNRAssembly* parent, const string& name = "unnamed"):
		m_x(0.0), m_y(0.0), m_z(0.0),
		m_phi(0.0), m_theta(0.0), m_rho(0.0),
		m_scale_x(1.0), m_scale_y(1.0), m_scale_z(1.0),
		m_width(1.0), m_height(1.0), m_depth(1.0),
		m_type(IS_ROOT),
		m_name(name), m_parent(parent)
{
}

/**
 * destructor of generic assembly kills all his children
 * @access      public
 */
GNRAssembly::~GNRAssembly()
{
	for (list<GNRAssembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		delete *it;
	}
}

/* ******* GETTER METHODS FOLLOWING ***** */
/**
 * get position value x
 * @access      public
 */
float GNRAssembly::getX() const
{
	return m_x;
}

/**
 * get position value y
 * @access      public
 */
float GNRAssembly::getY() const
{
	return m_y;
}

/**
 * get position value z
 * @access      public
 */
float GNRAssembly::getZ() const
{
	return m_z;
}

/**
 * get height of whole assembly
 * @access      public
 */
float GNRAssembly::getHeight() const
{
	return m_height;
}

/**
 * get width of whole assembly
 * @access      public
 */
float GNRAssembly::getWidth() const
{
	return m_width;
}

/**
 * get depth of whole assembly
 * @access      public
 */
float GNRAssembly::getDepth() const
{
	return m_depth;
}

/**
 * get degree value of rotation in x
 * @access      public
 */
float GNRAssembly::getPhi() const
{
	return m_phi;
}

/**
 * get degree value of rotation in y
 * @access      public
 */
float GNRAssembly::getRho() const
{
	return m_rho;
}

/**
 * get degree value of rotation in z
 * @access      public
 */
float GNRAssembly::getTheta() const
{
	return m_theta;
}

/**
 * get scale factor in dimension x
 * @return      float       x scale
 * @access      public
 */
float GNRAssembly::getScaleX() const
{
	return m_scale_x;
}

/**
 * get scale factor in dimension y
 * @return      float       y scale
 * @access      public
 */
float GNRAssembly::getScaleY() const
{
	return m_scale_y;
}

/**
 * get scale factor in dimension z
 * @return      float       z scale
 * @access      public
 */
float GNRAssembly::getScaleZ() const
{
	return m_scale_z;
}

/**
 * get name of assembly
 * @return      string      name of assembly
 * @access      public
 */
const string& GNRAssembly::getName() const
{
	return m_name;
}

/**
 * get pointer to parent assembly
 * @return      GNRAssembly*      pointer to parent
 * @access      public
 */
GNRAssembly* GNRAssembly::getParent() const
{
	return m_parent;
}

/**
 * get assembly type
 * @return      assemblyType      type of assembly
 * @access      public
 */
assemblyType GNRAssembly::getType() const
{
	return m_type;
}

/**
 * get assembly height over ground
 * @return      float      height over floor
 * @access      public
 */
float GNRAssembly::getOverGround() const
{
	return (m_height * m_scale_y) / 2.0;
}

/**
 * get master id of current assembly
 * @return      int         int ID of master
 * @access      public
 */
int GNRAssembly::getMasterID()
{
	GNRAssembly* p = m_parent;
	while (p->m_parent != NULL && p->m_parent->m_type != IS_ROOT)
	{
		p = p->m_parent;
	}
	return (int)p;
}

/**
 * compare type of assembly
 * @param       assemblyType    type of assembly
 * @return      boolean         is of type
 * @access      public
 */
bool GNRAssembly::isType(const assemblyType& type)
{
	return (m_type == type);
}

/* ******* SETTER METHODS FOLLOWING ***** */
/**
 * set position value x
 * @param       float       x
 * @access      public
 */
void GNRAssembly::setX(const float x)
{
	m_x = x;
}

/**
 * set position value y
 * @param       float       y
 * @access      public
 */
void GNRAssembly::setY(const float y)
{
	m_y = y;
}

/**
 * set position value z
 * @param       float       z
 * @access      public
 */
void GNRAssembly::setZ(const float z)
{
	m_z = z;
}

/**
 * set position value x and y
 * @param       float       x
 * @param       float       y
 * @access      public
 */
void GNRAssembly::setXY(const float x, const float y)
{
	m_x = x;
	m_y = y;
}

/**
 * set position value x and z
 * @param       float       x
 * @param       float       z
 * @access      public
 */
void GNRAssembly::setXZ(const float x, const float z)
{
	m_x = x;
	m_z = z;
}

/**
 * set degree value of rotation in x
 * @param       float        rotation degree in x
 * @access      public
 */
void GNRAssembly::setPhi(const float phi)
{
	m_phi = phi;
}

/**
 * set degree value of rotation in y
 * @param       float        rotation degree in y
 * @access      public
 */
void GNRAssembly::setRho(const float rho)
{
	m_rho = rho;
}

/**
 * set degree value of rotation in z
 * @param       float        rotation degree in z
 * @access      public
 */
void GNRAssembly::setTheta(const float theta)
{
	m_theta = theta;
}

/**
 * set degree value of rotation in x
 * @param       float        rotation degree in x
 * @param       float        rotation degree in y
 * @access      public
 */
void GNRAssembly::setPhiTheta(const float phi, const float theta)
{
	m_phi   = phi;
	m_theta = theta;
}

/**
 * set degree value of rotation in x
 * @param       float        rotation degree in x
 * @param       float        rotation degree in z
 * @access      public
 */
void GNRAssembly::setPhiRho(const float phi, const float rho)
{
	m_phi = phi;
	m_rho = rho;
}

/**
 * set scale factor in x dimension
 * @param       float        factor for x
 * @access      public
 */
void GNRAssembly::setScaleX(const float x)
{
	m_scale_x = x;
}

/**
 * set scale factor in y dimension
 * @param       float        factor for y
 * @access      public
 */
void GNRAssembly::setScaleY(const float y)
{
	m_scale_y = y;
}

/**
 * set scale factor in z dimension
 * @param       float        factor for z
 * @access      public
 */
void GNRAssembly::setScaleZ(const float z)
{
	m_scale_z = z;
}

/**
 * set height of assembly
 * @param       float       height
 * @access      public
 */
void GNRAssembly::setHeight(const float height)
{
	m_height = height;
}

/**
 * set width of assembly
 * @param       float       width
 * @access      public
 */
void GNRAssembly::setWidth(const float width)
{
	m_width = width;
}

/**
 * set depth of assembly
 * @param       float       depth
 * @access      public
 */
void GNRAssembly::setDepth(const float depth)
{
	m_depth = depth;
}

/**
 * set depth of assembly
 * @param       float       width  (x)
 * @param       float       height (y)
 * @param       float       depth  (z)
 * @access      public
 */
void GNRAssembly::setSize(const float width,const float height,const float depth)
{
	m_width  = width;
	m_height = height;
	m_depth  = depth;
}

/**
 * set scale factor s for x, y and z
 * @param       float        factor for x
 * @param       float        factor for y
 * @param       float        factor for z
 * @access      public
 */
void GNRAssembly::setScale(const float x,const float y,const float z)
{
	m_scale_x = x;
	m_scale_y = y;
	m_scale_z = z;
}

/**
 * set name of assembly
 * @param       string      name of assembly
 * @access      public
 */
void GNRAssembly::setName(const string& name)
{
	m_name = name;
}

/**
 * set pointer to parent assembly
 * @param       GNRAssembly*      pointer to parent
 * @access      public
 */
void GNRAssembly::setParent(GNRAssembly* p)
{
	m_parent = p;
}

/**
 * set type of assembly
 * @param       bool      is obj
 * @access      public
 */
void GNRAssembly::setType(const assemblyType& type)
{
	m_type = type;
}

/**
 * add face to assembly
 * @param       GNRFace      face to add
 * @access      public
 */
void GNRAssembly::addFace(const GNRFace& face)
{
	m_face.push_back(face);
}

/**
 * add part to assembly
 * @param       GNRAssembly      part to add
 * @access      public
 */
void GNRAssembly::addPart(GNRAssembly* part)
{
	part->setParent(this);
	m_part.push_back(part);
}

/**
 * calculate normals for all faces (incl. parts)
 * @access      public
 */
void GNRAssembly::setNormals()
{
	// set normals on own faces
	for (list<GNRFace>::iterator it = m_face.begin(); it != m_face.end(); ++it)
	{
		it->setNormal();
	}
	
	// let children set their normals
	for (list<GNRAssembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		(*it)->setNormals();
	}
}

/**
 * draw this assembly and all his children and push ID to glLoadName, if its atomic
 * @access      public
 */
void GNRAssembly::draw() const
{
	if (m_type == IS_ATOMIC)
	{
		glLoadName((int)this);
	}
	
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	{
		//if importer scale factor 1.0, then scale before translate
		glScalef(m_scale_x, m_scale_y, m_scale_z);
		glTranslatef(m_x, m_y, m_z);
		
		//rotate in object center
		glRotatef(m_phi, 1, 0, 0);
		glRotatef(m_theta, 0, 1, 0);
		glRotatef(m_rho, 0, 0, 1);
		
		// draw myself
		for (list<GNRFace>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
		{
			it->draw();
		}
		
		// draw the children
		for (list<GNRAssembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
		{
			(*it)->draw();
		}
	}
	glPopMatrix();
}

/**
 * correct y-position over ground
 * @access      public
 */
void GNRAssembly::putOnGround()
{
	m_y = (m_height * m_scale_y) / 2.0;
}

/**
 * get infos about assembly
 * @access      public
 */
void GNRAssembly::debugInfo() const
{
#if defined(__ATHOS_DEBUG__)
	wxString msg;
	msg << wxT(" x=") << m_x;
	msg << wxT(" y=") << m_y;
	msg << wxT(" z=") << m_z;
	msg << wxT("\nphi=") << m_phi;
	msg << wxT(" the=") << m_theta;
	msg << wxT(" rho=") << m_rho;
	msg << wxT("\nh=") << m_height;
	msg << wxT(" w=") << m_width;
	msg << wxT(" d=") << m_depth;
	msg << wxT("\nsx=") << m_scale_x;
	msg << wxT(" sy=") << m_scale_y;
	msg << wxT(" sz=") << m_scale_z;
	msg << wxT("\noG=") << (m_height * m_scale_y) / 2.0;
	wxLogDebug(msg);
#endif
}
