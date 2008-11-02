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
#include "GNRMaterial.h"

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
		m_radius_bottom(0.0), m_radius_middle(0.0), m_radius_top(0.0),
		m_type(IS_ROOT), m_name(name), m_parent(NULL)
{
}

/**
 * copy constructor of generic assembly
 * @param       string         name of assembly
 * @access      public
 */
GNRAssembly::GNRAssembly(const GNRAssembly& assembly)
{
	m_x       = assembly.m_x;
	m_y       = assembly.m_y;
	m_z       = assembly.m_z;
	m_phi     = assembly.m_phi;
	m_theta   = assembly.m_theta;
	m_rho     = assembly.m_rho;
	m_scale_x = assembly.m_scale_x;
	m_scale_y = assembly.m_scale_y;
	m_scale_z = assembly.m_scale_z;
	m_width   = assembly.m_width;
	m_height  = assembly.m_height;
	m_depth   = assembly.m_depth;
	m_type    = assembly.m_type;
	m_name    = assembly.m_name;
	m_parent  = assembly.m_parent;
	m_radius_bottom = assembly.m_radius_bottom;
	m_radius_middle = assembly.m_radius_middle;
	m_radius_top    = assembly.m_radius_top;
	
	// copy my faces
	for (list<GNRFace>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
	{
		GNRFace a_face = (*it);
		addFace(a_face);
	}
	
	// copy the children
	for (list<GNRAssembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		// draw the Child
		GNRAssembly* a_copy = new GNRAssembly("copy");
		(*a_copy) = (**it);
		addPart(a_copy);
		
		// set Child-Material
		map<const GNRAssembly* const, GNRMaterial>::const_iterator it_mat = m_child_mat.find(*it);
		if (it_mat != m_child_mat.end())
		{
			GNRMaterial a_mat = it_mat->second;
			setChildMaterial(a_copy, a_mat);
		}
	}
	
	// copy the tags
	for (list<wxString>::const_iterator it_tags = m_tags.begin(); it_tags != m_tags.end(); ++it_tags)
	{
		wxString a_tag = (*it_tags);
		addTag(a_tag);
	}
}

/**
 * clone of generic assembly
 * @return      GNRAssembly*         pointer to assembly
 * @access      public
 */
GNRAssembly* GNRAssembly::clone()
{
	GNRAssembly* m_clone = new GNRAssembly("clone");
	
	m_clone->m_x       = m_x;
	m_clone->m_y       = m_y;
	m_clone->m_z       = m_z;
	m_clone->m_phi     = m_phi;
	m_clone->m_theta   = m_theta;
	m_clone->m_rho     = m_rho;
	m_clone->m_scale_x = m_scale_x;
	m_clone->m_scale_y = m_scale_y;
	m_clone->m_scale_z = m_scale_z;
	m_clone->m_width   = m_width;
	m_clone->m_height  = m_height;
	m_clone->m_depth   = m_depth;
	m_clone->m_type    = m_type;
	m_clone->m_name    = m_name;
	m_clone->m_parent  = m_parent;
	m_clone->m_radius_bottom = m_radius_bottom;
	m_clone->m_radius_middle = m_radius_middle;
	m_clone->m_radius_top    = m_radius_top;
	
	// copy my faces
	for (list<GNRFace>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
	{
		GNRFace a_face = (*it);
		m_clone->addFace(a_face);
	}
	
	// copy the children
	for (list<GNRAssembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		// draw the Child
		GNRAssembly* a_copy = (*it)->clone();
		m_clone->addPart(a_copy);
		
		// set Child-Material
		map<const GNRAssembly* const, GNRMaterial>::const_iterator it_mat = m_child_mat.find(*it);
		if (it_mat != m_child_mat.end())
		{
			GNRMaterial a_mat = it_mat->second;
			m_clone->setChildMaterial(a_copy, a_mat);
		}
	}
	
	// copy the tags
	for (list<wxString>::const_iterator it_tags = m_tags.begin(); it_tags != m_tags.end(); ++it_tags)
	{
		wxString a_tag = (*it_tags);
		m_clone->addTag(a_tag);
	}
	
	return m_clone;
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
		m_radius_bottom(0.0), m_radius_middle(0.0), m_radius_top(0.0),
		m_type(IS_ROOT), m_name(name), m_parent(parent)
{
}

/**
 * constructor of generic assembly with type
 * @param       assemblyType   type of assembly
 * @param       GNRAssembly*   pointer to parent
 * @access      public
 */
GNRAssembly::GNRAssembly(const assemblyType& type, const string& name = "unnamed"):
		m_x(0.0), m_y(0.0), m_z(0.0),
		m_phi(0.0), m_theta(0.0), m_rho(0.0),
		m_scale_x(1.0), m_scale_y(1.0), m_scale_z(1.0),
		m_width(1.0), m_height(1.0), m_depth(1.0),
		m_radius_bottom(0.0), m_radius_middle(0.0), m_radius_top(0.0),
		m_type(type), m_name(name), m_parent(NULL)
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
 * get top radius of cylinder (maybe for cone if zero)
 * @access      public
 */
float GNRAssembly::getRadiusTop() const
{
	return m_radius_top;
}

/**
 * get middle radius of sphere
 * @access      public
 */
float GNRAssembly::getRadiusMiddle() const
{
	return m_radius_middle;
}

/**
 * get bottom radius of cylinder (maybe for cone if zero)
 * @access      public
 */
float GNRAssembly::getRadiusBottom() const
{
	return m_radius_bottom;
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
	return (m_height*m_scale_y)/2.0;
}

/**
 * get master id of current assembly
 * @return      GNRAssembly*         pointer to master
 * @access      public
 */
GNRAssembly* GNRAssembly::getMaster() const
{
	GNRAssembly* master = m_parent;
	
	//while parent exists and type is not ROOT,
	// SELECTED, HIDDEN or TRASH, move upwards
	while (master->m_parent != NULL && master->m_parent->m_type > IS_TRASH)
	{
		master = master->m_parent;
	}
	
	//return master pointer
	return master;
}

/**
 * get maximum size of object
 * @return      float         size in meter
 * @access      public
 */
float GNRAssembly::getMaximumSize() const
{
	float max = m_height;
	if (m_width > max)
	{
		max = m_width;
	}
	if (m_depth > max)
	{
		max = m_depth;
	}
	return max;
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
 * set top radius for cylinder or cone
 * @param       float       r
 * @access      public
 */
void GNRAssembly::setRadiusTop(const float r)
{
	m_radius_top = r;
}

/**
 * set middle radius for sphere
 * @param       float       r
 * @access      public
 */
void GNRAssembly::setRadiusMiddle(const float r)
{
	m_radius_middle = r;
}

/**
 * set bottom radius for cylinder or cone
 * @param       float       r
 * @access      public
 */
void GNRAssembly::setRadiusBottom(const float r)
{
	m_radius_bottom = r;
}

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
 * set position value x, y and z
 * @param       float       x
 * @param       float       y
 * @param       float       z
 * @access      public
 */
void GNRAssembly::setXYZ(const float x, const float y, const float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void GNRAssembly::setCone(const float x,const float y,const float z, const float height, const float r_top, const float r_bottom)
{
	m_x = x;
	m_y = y;
	m_z = z;
	
	m_radius_top    = r_top;
	m_radius_middle = (r_top+r_bottom)/2.0;
	m_radius_bottom = r_bottom;
	
	if (r_top > r_bottom)
	{
		m_width = r_top*2.0;
	}
	else
	{
		m_width = r_bottom*2.0;
	}
	
	m_height = height;
	m_depth  = m_width;
}

void GNRAssembly::setCylinder(const float x,const float y,const float z, const float height, const float radius)
{
	m_x = x;
	m_y = y;
	m_z = z;
	
	m_radius_top    = radius;
	m_radius_middle = radius;
	m_radius_bottom = radius;
	
	m_height = height;
	m_depth  = radius*2.0;
	m_width  = m_depth;
}

void GNRAssembly::setSphere(const float x,const float y,const float z, const float radius)
{
	m_x = x;
	m_y = y;
	m_z = z;
	
	m_radius_top    = 0.0;
	m_radius_middle = radius;
	m_radius_bottom = 0.0;
	
	m_height = radius*2.0;
	m_depth  = m_height;
	m_width  = m_height;
}

void GNRAssembly::setCuboid(const float x,const float y,const float z, const float width,const float height,const float depth)
{
	m_x = x;
	m_y = y;
	m_z = z;
	
	m_width  = width;
	m_height = height;
	m_depth  = depth;
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
 * set vertex position
 * @param       GNRVertex      vertex to center
 * @access      public
 */
void GNRAssembly::setCenterVertex(const GNRVertex& center)
{
	m_x = center.getX();
	m_y = center.getY();
	m_z = center.getZ();
}

/**
 * set vertex rotation
 * @param       GNRVertex      vertex to rotate
 * @access      public
 */
void GNRAssembly::setRotateVertex(const GNRVertex& rotation)
{
	m_phi   = rotation.getX();
	m_theta = rotation.getY();
	m_rho   = rotation.getZ();
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
 * delete part in assembly
 * @param       GNRAssembly      part to remove
 * @access      public
 */
void GNRAssembly::delPart(GNRAssembly* part)
{
	m_part.remove(part);
}

/**
 * get vertex position
 * @return      GNRVertext      vertex to center of object
 * @access      public
 */
GNRVertex GNRAssembly::getCenterVertex() const
{
	GNRVertex position(m_x, m_y, m_z);
	return position;
}

/**
 * get vertex rotation
 * @return      GNRVertext      vertex rotation of object
 * @access      public
 */
GNRVertex GNRAssembly::getRotateVertex() const
{
	GNRVertex rotation(m_phi, m_theta, m_rho);
	return rotation;
}

/**
 * get pointer to partlist for iteration
 * @return      list<GNRAssembly*>      pointer to part list
 * @access      public
 */
list<GNRAssembly*> GNRAssembly::getPartList()
{
	return m_part;
}

void GNRAssembly::addTag(wxString tag)
{
	m_tags.push_back(tag);
}

list<wxString> GNRAssembly::getTagList()
{
	return m_tags;
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

void GNRAssembly::setChildMaterial(const GNRAssembly* child, const GNRMaterial& mat)
{
	m_child_mat.insert(pair<const GNRAssembly*, GNRMaterial>(child, mat));
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
	else if (m_parent != NULL)
	{
		float glowcolor[4] = {0.0,0.0,0.0,0.0};
		
		//if selected paint in different colors
		if (m_parent->m_type == IS_SELECTED)
		{
			if (m_type != IS_GROUP)
			{
				//paint blue glowing
				glowcolor[0] = 0.0;
				glowcolor[1] = 0.0;
				glowcolor[2] = 1.0;
				glowcolor[3] = 1.0;
			}
			
			if (m_type == IS_GROUP)
			{
				//paint blue glowing
				glowcolor[0] = 1.0;
				glowcolor[1] = 0.0;
				glowcolor[2] = 0.0;
				glowcolor[3] = 1.0;
			}
			
			//if parent type group or selected, draw square on floor
			if (glowcolor[3] > 0.0)
			{
				glMaterialfv(GL_FRONT, GL_EMISSION, glowcolor);
			}
		}
		else if (m_parent->m_type == IS_ROOT)
		{
			//reset glow value for objects in root
			glMaterialfv(GL_FRONT, GL_EMISSION, glowcolor);
		}
	}
	
	glPushMatrix();
	{
		glTranslatef(m_x, m_y, m_z);
		glScalef(m_scale_x, m_scale_y, m_scale_z);
		
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
			// set Child-Material
			map<const GNRAssembly* const, GNRMaterial>::const_iterator it_mat = m_child_mat.find(*it);
			if (it_mat != m_child_mat.end())
			{
				it_mat->second.set();
			}
			
			// draw the Child
			(*it)->draw();
		}
	}
	glPopMatrix();
}

/**
 * draw shadow of this assembly and all his children and push ID to glLoadName, if its atomic
 * @access      public
 */
void GNRAssembly::drawShadow() const
{
	glPushMatrix();
	{
		glTranslatef(m_x, m_y, m_z);
		glScalef(m_scale_x, m_scale_y, m_scale_z);
		
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
			// draw the Child
			(*it)->drawShadow();
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
	m_y = (m_height*m_scale_y)/2.0;
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
