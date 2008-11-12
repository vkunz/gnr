/**
 * Assembly
 * @name        Assembly.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <wx/string.h>
#include "Assembly.h"
#include "Material.h"

#include <GL/gl.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of generic assembly
 * @param[in]      name         name of assembly
 */
Assembly::Assembly(const wxString& name):
		m_x(0.0), m_y(0.0), m_z(0.0),
		m_phi(0.0), m_theta(0.0), m_rho(0.0),
		m_scale_x(1.0), m_scale_y(1.0), m_scale_z(1.0),
		m_width(1.0), m_height(1.0), m_depth(1.0),
		m_radius_bottom(0.0), m_radius_middle(0.0), m_radius_top(0.0),
		m_type(IS_ROOT), m_name(name),
		m_visible(true), m_kill_dl(false),
		m_parent(NULL), m_origin(NULL),
		m_dl_object(0), m_dl_shadow(0),
		m_md5_obj_xml(wxEmptyString), m_ptype(OTHER)
{
}

/**
 * copy constructor of generic assembly
 * @param[in]       assembly         Assembly
 */
Assembly::Assembly(Assembly& assembly)
{
	if (assembly.m_origin == NULL)
	{
		//if assembly is original, set origin pointer
		m_origin = &assembly;
	}
	else
	{
		//else set same origin, is clone from clone
		m_origin = assembly.m_origin;
	}
	
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
	m_dl_object     = assembly.m_dl_object;
	m_dl_shadow     = assembly.m_dl_shadow;
	m_md5_obj_xml   = assembly.m_md5_obj_xml;
	m_ptype         = assembly.m_ptype;
	
	// copy the children
	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		// draw the Child
		Assembly* a_copy = new Assembly(wxT("Kopie"));
		(*a_copy) = (**it);
		addPart(a_copy);
		
		// set Child-Material
		map<const Assembly* const, Material>::const_iterator it_mat = m_child_mat.find(*it);
		if (it_mat != m_child_mat.end())
		{
			Material a_mat = it_mat->second;
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
 * clone only display lists
 * @return      GNRAssembly*         pointer to assembly
 */
void Assembly::cloneDisplayListFrom(Assembly* assembly)
{
	//copy display list ids
	m_dl_object = assembly->m_dl_object;
	m_dl_shadow = assembly->m_dl_shadow;
	
	//point to origin (faces backup)
	m_origin = assembly;
	
	//free memory
	m_face.clear();
}

/**
 * clone of generic assembly
 * @return      Assembly*         pointer to assembly
 */
Assembly* Assembly::clone()
{
	Assembly* m_clone = new Assembly(wxT("Kopie"));
	
	if (m_origin == NULL)
	{
		//if assembly is original, set origin pointer
		m_clone->m_origin = this;
	}
	else
	{
		//else set same origin, is clone from clone
		m_clone->m_origin = m_origin;
	}
	
	m_clone->m_x             = m_x;
	m_clone->m_y             = m_y;
	m_clone->m_z             = m_z;
	m_clone->m_phi           = m_phi;
	m_clone->m_theta         = m_theta;
	m_clone->m_rho           = m_rho;
	m_clone->m_scale_x       = m_scale_x;
	m_clone->m_scale_y       = m_scale_y;
	m_clone->m_scale_z       = m_scale_z;
	m_clone->m_width         = m_width;
	m_clone->m_height        = m_height;
	m_clone->m_depth         = m_depth;
	m_clone->m_type          = m_type;
	m_clone->m_name          = m_name;
	m_clone->m_parent        = m_parent;
	m_clone->m_radius_bottom = m_radius_bottom;
	m_clone->m_radius_middle = m_radius_middle;
	m_clone->m_radius_top    = m_radius_top;
	m_clone->m_dl_object     = m_dl_object;
	m_clone->m_dl_shadow     = m_dl_shadow;
	m_clone->m_md5_obj_xml   = m_md5_obj_xml;
	m_clone->m_ptype         = m_ptype;
	
	// copy the children
	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		// draw the Child
		Assembly* a_copy = (*it)->clone();
		m_clone->addPart(a_copy);
		
		// set Child-Material
		map<const Assembly* const, Material>::const_iterator it_mat = m_child_mat.find(*it);
		if (it_mat != m_child_mat.end())
		{
			Material a_mat = it_mat->second;
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
 * @param[in]        parent   	    pointer to parent Assembly*
 * @param[in]        name         	wxString name of assembly
 */
Assembly::Assembly(Assembly* parent, const wxString& name):
		m_x(0.0), m_y(0.0), m_z(0.0),
		m_phi(0.0), m_theta(0.0), m_rho(0.0),
		m_scale_x(1.0), m_scale_y(1.0), m_scale_z(1.0),
		m_width(1.0), m_height(1.0), m_depth(1.0),
		m_radius_bottom(0.0), m_radius_middle(0.0), m_radius_top(0.0),
		m_type(IS_ROOT), m_name(name),
		m_visible(true), m_kill_dl(false),
		m_parent(parent), m_origin(NULL),
		m_dl_object(0), m_dl_shadow(0),
		m_md5_obj_xml(wxEmptyString), m_ptype(OTHER)
{
}

/**
 * constructor of generic assembly with type
 * @param       type   		type of assembly
 * @param       name   		wxString name of assembly
 */
Assembly::Assembly(const assemblyType& type, const wxString& name):
		m_x(0.0), m_y(0.0), m_z(0.0),
		m_phi(0.0), m_theta(0.0), m_rho(0.0),
		m_scale_x(1.0), m_scale_y(1.0), m_scale_z(1.0),
		m_width(1.0), m_height(1.0), m_depth(1.0),
		m_radius_bottom(0.0), m_radius_middle(0.0), m_radius_top(0.0),
		m_type(type), m_name(name),
		m_visible(true), m_kill_dl(false),
		m_parent(NULL), m_origin(NULL),
		m_dl_object(0), m_dl_shadow(0),
		m_md5_obj_xml(wxEmptyString), m_ptype(OTHER)
{
}

/**
 * destructor of generic assembly kills all his children
 */
Assembly::~Assembly()
{
	for (list<Assembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		if (m_type <= IS_SELECTED || m_kill_dl)
		{
			(*it)->m_kill_dl = true;
		}
		
		//delete child
		delete *it;
	}
	
	//if it should kill his DL
	if (m_kill_dl)
	{
		glDeleteLists(m_dl_object, 1);
		glDeleteLists(m_dl_shadow, 1);
	}
	
	//kill partlist and childlists
	m_part.clear();
	m_child_dl.clear();
	m_child_mat.clear();
}

/* ******* GETTER METHODS FOLLOWING ***** */

/**
 * get visibility
 * @return 		bool		is visible
 */
bool Assembly::isVisible() const
{
	return m_visible;
}

/**
 * ask is he's a clone or not
 * @return 		bool		is original
 */
bool Assembly::isOriginal() const
{
	return (m_origin == NULL);
}

/**
 * get primitive type
 * @return 		primitiveType		type of primitive or 0
 */
primitiveType Assembly::getPrimitiveType() const
{
	return m_ptype;
}

/**
 * get position value x
 * @return 		float		center x in meters
 */
float Assembly::getX() const
{
	return m_x;
}

/**
 * get position value y
 * @return 		float		center y in meters
 */
float Assembly::getY() const
{
	return m_y;
}

/**
 * get position value z
 * @return 		float		center y in meters
 */
float Assembly::getZ() const
{
	return m_z;
}

/**
 * get position value z
 * @return 		float		center z
 */
const wxString& Assembly::getHash() const
{
	return m_md5_obj_xml;
}

/**
 * get top radius of cylinder (maybe for cone if zero)
 * @return 		float		radius top (cone, cylinder)
 */
float Assembly::getRadiusTop() const
{
	return m_radius_top;
}

/**
 * get middle radius of sphere
 * @return 		float		radius middle (sphere)
 */
float Assembly::getRadiusMiddle() const
{
	return m_radius_middle;
}

/**
 * get bottom radius of cylinder (maybe for cone if zero)
 * @return 		float		radius bottom (cone, cylinder)
 */
float Assembly::getRadiusBottom() const
{
	return m_radius_bottom;
}

/**
 * get height of whole assembly
 * @return 		float		height in meters
 */
float Assembly::getHeight() const
{
	return m_height;
}

/**
 * get width of whole assembly
 * @return 		float		width in meters
 */
float Assembly::getWidth() const
{
	return m_width;
}

/**
 * get depth of whole assembly
 * @return 		float		depth in meters
 */
float Assembly::getDepth() const
{
	return m_depth;
}

/**
 * get degree value of rotation in x
 * @return 		float		angle rotation in x-axis
 */
float Assembly::getPhi() const
{
	return m_phi;
}

/**
 * get degree value of rotation in y
 * @return 		float		angle rotation in y-axis
 */
float Assembly::getRho() const
{
	return m_rho;
}

/**
 * get degree value of rotation in z
 * @return 		float		angle rotation in z-axis
 */
float Assembly::getTheta() const
{
	return m_theta;
}

/**
 * get scale factor in dimension x
 * @return      float       x scale
 */
float Assembly::getScaleX() const
{
	return m_scale_x;
}

/**
 * get scale factor in dimension y
 * @return      float       y scale
 */
float Assembly::getScaleY() const
{
	return m_scale_y;
}

/**
 * get scale factor in dimension z
 * @return      float       z scale
 */
float Assembly::getScaleZ() const
{
	return m_scale_z;
}

/**
 * get name of assembly
 * @return      wxString      name of assembly
 */
const wxString& Assembly::getName() const
{
	return m_name;
}

/**
 * get real width in meters
 * @return      float      original width in meters with scale
 */
float Assembly::getWidthMeters() const
{
	return m_scale_x*m_width;
}

/**
 * get real height in meters
 * @return      float      original height in meters with scale
 */
float Assembly::getHeightMeters() const
{
	return m_scale_y*m_height;
}

/**
 * get real depth in meters
 * @return      float      original depth in meters with scale
 */
float Assembly::getDepthMeters() const
{
	return m_scale_z*m_depth;
}

/**
 * get pointer to parent assembly
 * @return      Assembly*      pointer to parent assembly
 */
Assembly* Assembly::getParent() const
{
	return m_parent;
}

/**
 * get assembly type
 * @return      assemblyType      type of assembly
 */
assemblyType Assembly::getType() const
{
	return m_type;
}

/**
 * get assembly height over ground
 * @return      float      height over floor in meters
 */
float Assembly::getOverGround() const
{
	return (m_height*m_scale_y)/2.0;
}

/**
 * get master id of current assembly
 * @return      Assembly*         pointer to master
 */
Assembly* Assembly::getMaster() const
{
	Assembly* master = m_parent;
	
	//while parent exists and type is not ROOT,
	// SELECTED, HIDDEN or TRASH, move upwards
	while (master->m_parent != NULL && master->m_parent->m_type > IS_SELECTED)
	{
		master = master->m_parent;
	}
	
	//return master pointer
	return master;
}

/**
 * get master id of current assembly
 * @return      bool         if is in selected group
 */
bool Assembly::isSelected() const
{
	Assembly* parent = m_parent;
	
	//while parent exists and type is not ROOT,
	// move upwards and head for selected container
	while (parent->m_parent != NULL && parent->m_parent->m_type != IS_SELECTED)
	{
		parent = parent->m_parent;
	}
	
	//return true, if parent type = selected
	return (parent->m_parent != NULL && parent->m_parent->m_type == IS_SELECTED);
}

/**
 * get origin id of current assembly
 * @return      Assembly*         pointer to origin
 */
Assembly* Assembly::getOrigin() const
{
	//return origin pointer
	return m_origin;
}

/**
 * get maximum size of object
 * @return      float         maximum size in meter
 */
float Assembly::getMaximumSize() const
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
 * @param[in]       type 		    type of assembly (assemblyType)
 * @return          boolean         is of type
 */
bool Assembly::isType(const assemblyType& type)
{
	return (m_type == type);
}

/* ******* SETTER METHODS FOLLOWING ***** */
/**
 * set top radius for cylinder or cone
 * @param        r 		float radius top
 */
void Assembly::setRadiusTop(const float r)
{
	m_radius_top = r;
}

/**
 * set middle radius for sphere
 * @param        r 		float radius middle
 */
void Assembly::setRadiusMiddle(const float r)
{
	m_radius_middle = r;
}

/**
 * set bottom radius for cylinder or cone
 * @param        r 		float radius bottom
 */
void Assembly::setRadiusBottom(const float r)
{
	m_radius_bottom = r;
}

/**
 * set visibility
 * @param        status 		visible  (true|false)
 */
void Assembly::setVisible(bool status)
{
	m_visible = status;
}

/**
 * set primitive type
 * @param[in] 		ptype       primitiveType of primitive
 */
void Assembly::setPrimitiveType(const primitiveType ptype)
{
	m_ptype = ptype;
}

/**
 * set position value x
 * @param       x       float value for x
 */
void Assembly::setX(const float x)
{
	m_x = x;
}

/**
 * set position value y
 * @param       y       float value for y
 */
void Assembly::setY(const float y)
{
	m_y = y;
}

/**
 * set position value z
 * @param       z       float value for z
 */
void Assembly::setZ(const float z)
{
	m_z = z;
}

/**
 * get position value z
 */
void Assembly::setHash(const wxString& hash)
{
	m_md5_obj_xml = hash;
}

/**
 * set position value x and y
 * @param       x       float value for x
 * @param       y       float value for y
 */
void Assembly::setXY(const float x, const float y)
{
	m_x = x;
	m_y = y;
}

/**
 * set position value x and z
 * @param       x       float value for x
 * @param       z       float value for z
 */
void Assembly::setXZ(const float x, const float z)
{
	m_x = x;
	m_z = z;
}

/**
 * set position value x, y and z
 * @param       x       float value for x
 * @param       y       float value for y
 * @param       z       float value for z
 */
void Assembly::setXYZ(const float x, const float y, const float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void Assembly::setCone(const float x,const float y,const float z, const float height, const float r_top, const float r_bottom)
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

void Assembly::setCylinder(const float x,const float y,const float z, const float height, const float radius)
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

void Assembly::setSphere(const float x,const float y,const float z, const float radius)
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

void Assembly::setCuboid(const float x,const float y,const float z, const float width,const float height,const float depth)
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
 * @param       phi        rotation degree in x
 */
void Assembly::setPhi(const float phi)
{
	m_phi = phi;
}

/**
 * set degree value of rotation in y
 * @param       rho        rotation degree in y
 */
void Assembly::setRho(const float rho)
{
	m_rho = rho;
}

/**
 * set degree value of rotation in z
 * @param       theta        rotation degree in z
 */
void Assembly::setTheta(const float theta)
{
	m_theta = theta;
}

/**
 * set degree value of rotation in x
 * @param       phi             rotation degree in x
 * @param       theta           rotation degree in y
 */
void Assembly::setPhiTheta(const float phi, const float theta)
{
	m_phi   = phi;
	m_theta = theta;
}

/**
 * set degree value of rotation in x
 * @param       phi        rotation degree in x
 * @param       rho        rotation degree in z
 */
void Assembly::setPhiRho(const float phi, const float rho)
{
	m_phi = phi;
	m_rho = rho;
}

/**
 * set scale factor in x dimension
 * @param       x        float scale factor for x
 */
void Assembly::setScaleX(const float x)
{
	m_scale_x = x;
}

/**
 * set scale factor in y dimension
 * @param       y        float scale factor for y
 */
void Assembly::setScaleY(const float y)
{
	m_scale_y = y;
}

/**
 * set scale factor in z dimension
 * @param       z        float scale factor for z
 */
void Assembly::setScaleZ(const float z)
{
	m_scale_z = z;
}

/**
 * set height of assembly
 * @param       height       float height of assembly
 */
void Assembly::setHeight(const float height)
{
	m_height = height;
}

/**
 * set width of assembly
 * @param       width       float width of assembly
 */
void Assembly::setWidth(const float width)
{
	m_width = width;
}

/**
 * set depth of assembly
 * @param       depth       float depth of assembly
 */
void Assembly::setDepth(const float depth)
{
	m_depth = depth;
}

/**
 * set depth of assembly
 * @param       width           width  (x)
 * @param       height          height (y)
 * @param       depth           depth  (z)
 */
void Assembly::setSize(const float width,const float height,const float depth)
{
	m_width  = width;
	m_height = height;
	m_depth  = depth;
}

/**
 * set scale factor s for x, y and z
 * @param       x        factor for x
 * @param       y        factor for y
 * @param       z        factor for z
 */
void Assembly::setScale(const float x,const float y,const float z)
{
	m_scale_x = x;
	m_scale_y = y;
	m_scale_z = z;
}

/**
 * set name of assembly
 * @param       name        string name of assembly
 */
void Assembly::setName(const wxString& name)
{
	m_name = name;
}

/**
 * set name of assembly
 * @param       name        string name of assembly
 */
void Assembly::setName(const string& name)
{
	wxString new_name(name.c_str(), wxConvUTF8);
	m_name = new_name;
}

/**
 * set pointer to parent assembly
 * @param       p         Assembly* pointer to parent
 */
void Assembly::setParent(Assembly* p)
{
	m_parent = p;
}

/**
 * set type of assembly
 * @param       type       boolean is obj
 */
void Assembly::setType(const assemblyType& type)
{
	m_type = type;
}

/**
 * move assembly by vertex
 * @param       center      vertex to center
 */
void Assembly::move(const Vertex& center)
{
	m_x = m_x + center.getX();
	m_y = m_y + center.getY();
	m_z = m_z + center.getZ();
}

/**
 * set vertex position
 * @param       center      vertex to center
 */
void Assembly::setCenterVertex(const Vertex& center)
{
	m_x = center.getX();
	m_y = center.getY();
	m_z = center.getZ();
}

/**
 * set vertex rotation
 * @param       rotation      vertex to rotate
 */
void Assembly::setRotateVertex(const Vertex& rotation)
{
	m_phi   = rotation.getX();
	m_theta = rotation.getY();
	m_rho   = rotation.getZ();
}

/**
 * add face to assembly
 * @param       face      face to add
 */
void Assembly::addFace(const Face& face)
{
	m_face.push_back(face);
}

/**
 * add part to assembly
 * @param       part      Assembly* part to add
 */
void Assembly::addPart(Assembly* part)
{
	part->setParent(this);
	m_part.push_back(part);
}

/**
 * delete part in assembly
 * @param       part      Assembly* part to remove
 */
void Assembly::delPart(Assembly* part)
{
	m_part.remove(part);
}

/**
 * get vertex position
 * @return      Vertex      vertex to center of object
 */
Vertex Assembly::getCenterVertex() const
{
	Vertex position(m_x, m_y, m_z);
	return position;
}

/**
 * get vertex rotation
 * @return      Vertex      vertex rotation of object
 */
Vertex Assembly::getRotateVertex() const
{
	Vertex rotation(m_phi, m_theta, m_rho);
	return rotation;
}

/**
 * get pointer to partlist for iteration
 * @return      list<Assembly*>      pointer to part list
 */
list<Assembly*> Assembly::getPartList()
{
	return m_part;
}

/**
 * set tag
 * @param      tag        wxStrings tag
 */
void Assembly::addTag(wxString tag)
{
	m_tags.push_back(tag);
}

/**
 * get tags list
 * @return      list<wxString>        wxStrings list of tags
 */
list<wxString> Assembly::getTagList()
{
	return m_tags;
}

/**
 * calculate normals for all faces (incl. parts)
 */
void Assembly::setNormals()
{
	// set normals on own faces
	for (list<Face>::iterator it = m_face.begin(); it != m_face.end(); ++it)
	{
		it->setNormal();
	}
	
	// let children set their normals
	for (list<Assembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		(*it)->setNormals();
	}
}

/**
 * setChildMaterial
 * @param[in]       child           Assembly* to child
 * @param[in]       mat             Material to set for child
 */
void Assembly::setChildMaterial(const Assembly* child, const Material& mat)
{
	m_child_mat[child] = mat;
}

/**
 * setChildDisplayList
 * @param[in]       child           Assembly* to child
 * @param[in]       dl              gluint display list for child
 */
void Assembly::setChildDisplayList(const Assembly* child, const GLuint& dl)
{
	m_child_dl.insert(pair<const Assembly*, GLuint>(child, dl));
}

/**
 * draw this assembly and all his children and push ID to glLoadName, if its atomic
 */
void Assembly::draw()
{
	//if hidden, abort draw
	if (!m_visible)
	{
		return;
	}
	
	//start drawing glow colors on selection
	if (m_type == IS_ATOMIC)
	{
		//if its an atomic part, set name
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
				glMaterialfv(GL_FRONT, GL_AMBIENT, glowcolor);
			}
		}
		else if (m_parent->m_type == IS_ROOT)
		{
			//reset glow value for objects in root
			glMaterialfv(GL_FRONT, GL_EMISSION, glowcolor);
			glMaterialfv(GL_FRONT, GL_AMBIENT, glowcolor);
		}
	}
	
	glPushMatrix();
	{
		//first translate to position
		glTranslatef(m_x, m_y, m_z);
		
		//rotate in object center
		glRotatef(m_phi, 1, 0, 0);
		glRotatef(m_theta, 0, 1, 0);
		glRotatef(m_rho, 0, 0, 1);
		
		//finally scale on place
		glScalef(m_scale_x, m_scale_y, m_scale_z);
		
		if (glIsList(m_dl_object) || !isOriginal())
		{
			//if no valid display list...
			if (!glIsList(m_dl_object))
			{
				//...clone it from origin
				cloneDisplayListFrom(m_origin);
			}
			//call display list of objects
			glCallList(m_dl_object);
		}
		else
		{
			//create new display list for myself
			m_dl_object = glGenLists(1);
			
			//setup new display list
			glNewList(m_dl_object,GL_COMPILE);
			{
				// draw myself to display list
				for (list<Face>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
				{
					it->draw();
				}
			}
			glEndList();
		}
		
		// draw the children
		for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
		{
			// set Child-Material
			map<const Assembly* const, Material>::iterator it_mat = m_child_mat.find(*it);
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
 * find clone of origin and return true if found
 * @param[in]       origin             Assembly* to find in origins
 * @return          bool               found? true or false
 */
bool Assembly::findCloneOf(const Assembly* origin) const
{
	//search for the clone of origin
	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		if (origin == (*it)->getOrigin())
		{
			return true;
		}
	}
	return false;
}

/**
 * find hash string and return true if found
 * @param[in]   hash             wxString hash of assembly
 * @return      bool             found? true or false
 */
bool Assembly::findHash(const wxString& hash) const
{
	//search for the same hash and return
	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		if (hash == (*it)->getHash())
		{
			return true;
		}
	}
	return false;
}

/**
 * find original object for hash string and return null or pointer
 * @param[in]   hash             wxString hash of assembly
 * @return      Assembly*        pointer to original
 */
Assembly* Assembly::getHashOriginal(const wxString& hash) const
{
	//search for the same hash and return
	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		//found a group? cascade...
		if ((*it)->isType(IS_GROUP))
		{
			Assembly* sub = (*it)->getHashOriginal(hash);
			if (sub != NULL)
			{
				return sub;
			}
		}
		
		//found a copy? continue
		if (!(*it)->isOriginal())
		{
			continue;
		}
		
		//found a non-object? again...
		if (!(*it)->isType(IS_OBJECT))
		{
			continue;
		}
		
		//finally check hash, and get pointer
		if (hash == (*it)->getHash())
		{
			return (*it);
		}
	}
	
	//nothing found
	return NULL;
}

/**
 * draw shadow of this assembly and all his children and push ID to glLoadName, if its atomic
 */
void Assembly::drawShadow()
{
	//if hidden, abort draw
	if (!m_visible)
	{
		return;
	}
	
	//draw shadows, if object visible
	glPushMatrix();
	{
		//first translate to position
		glTranslatef(m_x, m_y, m_z);
		
		//rotate in object center
		glRotatef(m_phi, 1, 0, 0);
		glRotatef(m_theta, 0, 1, 0);
		glRotatef(m_rho, 0, 0, 1);
		
		//finally scale on place
		glScalef(m_scale_x, m_scale_y, m_scale_z);
		
		if (glIsList(m_dl_shadow) || !isOriginal())
		{
			//if no valid display list...
			if (!glIsList(m_dl_shadow))
			{
				//...clone it from origin
				cloneDisplayListFrom(m_origin);
			}
			//call display list of objects
			glCallList(m_dl_shadow);
		}
		else
		{
			//create new display list for my shadows
			m_dl_shadow = glGenLists(1);
			
			//setup new display list
			glNewList(m_dl_shadow,GL_COMPILE);
			{
				// draw my shadows to display list
				for (list<Face>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
				{
					it->draw();
				}
			}
			glEndList();
		}
		
		// draw the children
		for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
		{
			// draw the Child
			(*it)->drawShadow();
		}
	}
	glPopMatrix();
}

/**
 * correct y-position over ground
 */
void Assembly::putOnGround()
{
	m_y = (m_height*m_scale_y)/2.0;
}

/**
 * correct y-position over ground
 */
void Assembly::resetOnGround()
{
	m_y     = (m_height*m_scale_y)/2.0;
	m_phi   = 0.0;
	m_theta = 0.0;
	m_rho   = 0.0;
}

#if defined(__ATHOS_DEBUG__)
/**
 * get infos about assembly
 */
void Assembly::debugInfo() const
{
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
}

/**
 * dump structure
 * @param[in]       str         wxString for lines
 */
void Assembly::dump(wxString str)
{
	wxString out(wxEmptyString);
	out << str << wxT("-<") << (int)this << wxT("> TYP=") << m_type << wxT(" NAME=") << m_name;
	
	//dont print smallest parts
	if (isType(IS_ATOMIC) || isType(IS_WRAPPER))
	{
		return;
	}
	
	//output to debug window
	wxLogDebug(out);
	
	//increase level prefix
	str << wxT("-");
	
	//print ever lower level with +
	for (list<Assembly*>::iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		(*it)->dump(str);
	}
}
#endif
