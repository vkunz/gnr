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
#include "MaterialLibrary.h"
#include <iostream>
#include <fstream>

#include <GL/gl.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

using std::ofstream;

/**
 * constructor of generic assembly
 * @param[in]      name         name of assembly
 */
Assembly::Assembly(const wxString& name):
		m_scale(1.0f, 1.0f, 1.0f),
		m_type(IS_ROOT), m_name(name),
		m_visible(true), m_kill_dl(false),
		m_parent(NULL), m_origin(NULL),
		m_dl_object(0), m_dl_shadow(0),
		m_md5_obj_xml(wxEmptyString), m_ptype(OTHER)
{
}

/**
 * copy constructor of generic assembly
 * @param[in]       Assembly& a         Assembly
 */
Assembly::Assembly(Assembly& a):
		m_position(a.m_position), m_rotation(a.m_rotation), m_scale(a.m_scale),
		m_cuboid(a.m_cuboid), m_cylinder(a.m_cylinder), m_radius(a.m_radius),
		m_type(a.m_type), m_name(a.m_name), m_parent(a.m_parent),
		m_dl_object(a.m_dl_object), m_dl_shadow(a.m_dl_shadow),
		m_md5_obj_xml(a.m_md5_obj_xml), m_ptype(a.m_ptype)
{
	if (a.m_origin == NULL)
	{
		//if a is original, set origin pointer
		m_origin = &a;
	}
	else
	{
		//else set same origin, is clone from clone
		m_origin = a.m_origin;
	}

	// copy the children
	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		// draw the Child
		Assembly* a_copy = new Assembly(wxT("Kopie"));
		(*a_copy) = (**it);
		addPart(a_copy);
	}

	// copy the tags
	for (list<wxString>::const_iterator it_tags = m_tags.begin(); it_tags != m_tags.end(); ++it_tags)
	{
		wxString a_tag = (*it_tags);
		addTag(a_tag);
	}
}

/**
 * constructor of generic assembly with parent
 * @param[in]        parent   	    pointer to parent Assembly*
 * @param[in]        name         	wxString name of assembly
 */
Assembly::Assembly(Assembly* parent, const wxString& name):
		m_scale(1.0f, 1.0f, 1.0f),
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
		m_scale(1.0f, 1.0f, 1.0f),
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
	//m_part.clear();
	//m_child_dl.clear();
}

/* GETTER - SETTER */

/**
 * get position
 * @return 		const Vertex&	position in meters
 */
const Vertex& Assembly::position() const
{
	return m_position;
}

/**
 * set position
 * @return 		Vertex&	position in meters
 */
Vertex& Assembly::position()
{
	return m_position;
}

/**
 * get rotation
 * @return 		const Vertex&	rotation in degrees
 */
const Vertex& Assembly::rotation() const
{
	return m_rotation;
}

/**
 * set rotation
 * @return 		Vertex&	rotation in degrees
 */
Vertex& Assembly::rotation()
{
	return m_rotation;
}

/**
 * get scale
 * @return 		const Vertex&	scale
 */
const Vertex& Assembly::scale() const
{
	return m_scale;
}

/**
 * set scale
 * @return 		Vertex&	rotation in degrees
 */
Vertex& Assembly::scale()
{
	return m_scale;
}

/**
 * get dimension of the surrounding cube
 * @return 		const Vertex&	dimension
 */
const Vertex& Assembly::dimension() const
{
	return m_dimension;
}

/**
 * set dimension of the surrounding cube
 * @return 		const Vertex&	dimension
 */
Vertex& Assembly::dimension()
{
	return m_dimension;
}

/**
 * get the world dimension of the surrounding cube
 * @return 		Vertex	dimension
 */
Vertex Assembly::world_dimension() const
{
	Vertex tmp(
	    m_scale.getX() * m_dimension.getX(),
	    m_scale.getY() * m_dimension.getY(),
	    m_scale.getZ() * m_dimension.getZ()
	);

	return tmp;
}

void Assembly::move(const Vertex& dir)
{
	m_position += dir;
}

/**
 * get visibility
 * @return 		bool		is visible
 */
bool Assembly::isVisible() const
{
	return m_visible;
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
 * ask is he's a clone or not
 * @return 		bool		is original
 */
bool Assembly::isOriginal() const
{
	return (m_origin == NULL);
}

/**
 * get hash
 * @return 		const wxString&		hash value
 */
const wxString& Assembly::getHash() const
{
	return m_md5_obj_xml;
}

/**
 * set hash
 * @param[in] 		hash	hash to set
 */
void Assembly::setHash(const wxString& hash)
{
	m_md5_obj_xml = hash;
}

/**
 * get name of assembly
 * @return      wxString      name of assembly
 */
const wxString& Assembly::getName() const
{
	return m_name;
}

Assembly* Assembly::getParent() const
{
	return m_parent;
}

/**
 * get assembly height over ground
 * @return      float      height over floor in meters
 */
float Assembly::getOverGround() const
{
	return (m_dimension.getY()  * m_scale.getY()) / 2.0f;
}

void Assembly::setMaterial(const string& mat)
{
	m_matname = mat;
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
 * get the maximum dimension of object
 * @return      float         maximum size in meter
 */
float Assembly::getMaximumSize() const
{
	float x, y, z;
	m_dimension.getAll(x, y, z);

	float max = x;
	if (y > max)
	{
		max = y;
	}
	if (z > max)
	{
		max = z;
	}
	return max;
}

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
 * add face to assembly
 * @param       face      face to add
 */
void Assembly::addFace(Face* face)
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
	string act_matname = m_matname;

	// set object's material
	MaterialLibrary::mat_citer tmp = MaterialLibrary::getInstance()->get(m_matname);
	if (tmp != MaterialLibrary::getInstance()->end())
	{
		tmp->second.set();
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
		float x, y, z;
		m_position.getAll(x, y, z);
		glTranslatef(x, y, z);

		//rotate in object center
		m_rotation.getAll(x, y, z);
		glRotatef(x, 1, 0, 0);
		glRotatef(y, 0, 1, 0);
		glRotatef(z, 0, 0, 1);

		//finally scale on place
		m_scale.getAll(x, y, z);
		glScalef(x, y, z);

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
				for (list<Face*>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
				{
					const string& face_mat = (*it)->material();
					if (face_mat != act_matname)
					{
						MaterialLibrary::mat_citer tmp = MaterialLibrary::getInstance()->get(m_matname);
						if (tmp != MaterialLibrary::getInstance()->end())
						{
							// if face's material is different, set it
							tmp->second.set();
						}
					}

					(*it)->draw();
				}
			}
			glEndList();
		}

		// draw the children
		for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
		{
			// draw the Child
			(*it)->draw();
		}
	}
	glPopMatrix();
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

	m_clone->m_position     = m_position;
	m_clone->m_dimension    = m_dimension;
	m_clone->m_rotation     = m_rotation;
	m_clone->m_scale        = m_scale;

	m_clone->m_type         = m_type;
	m_clone->m_name         = m_name;
	m_clone->m_ptype        = m_ptype;
	m_clone->m_parent       = m_parent;

	m_clone->m_dl_object    = m_dl_object;
	m_clone->m_dl_shadow    = m_dl_shadow;
	m_clone->m_md5_obj_xml  = m_md5_obj_xml;

	m_clone->m_cuboid       = m_cuboid;
	m_clone->m_cylinder     = m_cylinder;
	m_clone->m_radius       = m_radius;

	m_clone->m_matname      = m_matname;

	// copy the children
	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		// draw the Child
		Assembly* a_copy = (*it)->clone();
		m_clone->addPart(a_copy);
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
		float x, y, z;
		m_position.getAll(x, y, z);
		glTranslatef(x, y, z);

		//rotate in object center
		m_rotation.getAll(x, y, z);
		glRotatef(x, 1, 0, 0);
		glRotatef(y, 0, 1, 0);
		glRotatef(z, 0, 0, 1);

		//finally scale on place
		m_scale.getAll(x, y, z);
		glScalef(x, y, z);

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
				for (list<Face*>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
				{
					(*it)->draw();
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
	m_position.setY(world_dimension().getY() / 2.0f);
}

/**
 * correct y-position over ground
 */
void Assembly::resetOnGround()
{
	putOnGround();
	m_rotation.setAll(0.0f, 0.0f, 0.0f);
}

#if defined(__ATHOS_DEBUG__)
/**
 * get infos about assembly
 */
void Assembly::debugInfo() const
{
	wxString msg;
	msg << wxT(" x=") << m_position.getX();
	msg << wxT(" y=") << m_position.getY();
	msg << wxT(" z=") << m_position.getZ();
	msg << wxT("\nrx=") << m_rotation.getX();
	msg << wxT(" ry=") << m_rotation.getY();
	msg << wxT(" rz=") << m_rotation.getZ();
	msg << wxT("\nw=") << m_dimension.getX();
	msg << wxT(" h=") << m_dimension.getY();
	msg << wxT(" d=") << m_dimension.getZ();
	msg << wxT("\nsx=") << m_scale.getX();
	msg << wxT(" sy=") << m_scale.getY();
	msg << wxT(" sz=") << m_scale.getZ();
	msg << wxT("\noG=") << (m_dimension.getY() * m_scale.getY()) / 2.0f;
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

void Assembly::dump2stream(ostream& os, int depth) const
{
	string placeholder(depth, '\t');
	os << placeholder << "o " << this << endl;
	os << placeholder << m_position << " " << m_rotation << endl;
	os << placeholder << "material:" << m_matname << endl;
	os << placeholder << "faces:" << endl;
	for (list<Face*>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
	{
		os << placeholder << (*it)->material() << " " << *it  << endl;
	}
	os << placeholder << "children: " << endl;
	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		os << placeholder << *it << " " << endl;
	}

	for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
	{
		(*it)->dump2stream(os, depth+1);
	}
	os << placeholder << this << " done" << endl;
}




#endif

// TODO
// TODO
// TODO
// TODO
// the really dirty stuff comes (OOP, OOA, OOD, Polymorphysm -- WHAT IS THAT?!)

/**
 * get radius of the Sphere
 * @return 		float		radius
 */
float Assembly::sphere_radius() const
{
	return m_radius;
}

/**
 * set radius of the Sphere
 * @return 		float		radius
 */
float& Assembly::sphere_radius()
{
	return m_radius;
}

/**
 * get dimension of the Cuboid
 * @return 		const Vertex&	dimension
 */
const Vertex& Assembly::cuboid_dimension() const
{
	return m_cuboid;
}

/**
 * set dimension of the Cuboid
 * @return 		Vertex&		dimension
 */
Vertex& Assembly::cuboid_dimension()
{
	return m_cuboid;
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
 * get assembly type
 * @return      assemblyType      type of assembly
 */
assemblyType Assembly::getType() const
{
	return m_type;
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

/**
 * set primitive type
 * @param[in] 		ptype       primitiveType of primitive
 */
void Assembly::setPrimitiveType(const primitiveType ptype)
{
	m_ptype = ptype;
}

void Assembly::setCylinder(float x, float y, float z, float height, float r_top, float r_bottom)
{
	m_position.setAll(x, y, z);
	m_cylinder.setAll(height, r_top, r_bottom);

	float r_max = r_top;
	if (r_bottom > r_max)
	{
		r_max = r_bottom;
	}
	float d = 2 * r_max;
	m_dimension.setAll(d, height, d);
}

void Assembly::setSphere(const float x,const float y,const float z, const float radius)
{
	m_position.setAll(x, y, z);
	m_radius = radius;

	float d = 2 * radius;
	m_dimension.setAll(d, d, d);
}

void Assembly::setCuboid(const float x,const float y,const float z, const float width,const float height,const float depth)
{
	m_position.setAll(x, y, z);
	m_cuboid.setAll(width, height, depth);
	m_dimension = m_cuboid;
}

/**
 * set type of assembly
 * @param       type       boolean is obj
 */
void Assembly::setType(const assemblyType& type)
{
	m_type = type;
}


/* rest methods */

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
	//m_face.clear();
}


void Assembly::ObjExport(const string& fname)
{
	string mat_fn(fname.substr(0, fname.find_last_of('.')) + ".mtl");
	ofstream ss_mat(mat_fn.c_str());
	ss_mat << *MaterialLibrary::getInstance() << endl;
	ss_mat.close();

	ofstream os(fname.c_str());
	Matrix4D tsr(m_position, m_scale, m_rotation);

    // vertex and normal counters
    int vc = 1, nc = 1;

    os << "o " << m_name << endl;
    dump_me(os, tsr, vc, nc);

    for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
    {
		os << endl << "o " << (*it)->m_name << endl;
        (*it)->ObjExport(os, tsr, vc, nc);
        os << endl;
	}
}

void Assembly::ObjExport(ostream& ss, const Matrix4D& parent_tsr, int& vc, int& nc)
{
        Matrix4D tsr(parent_tsr), my_translation(m_position, m_scale, m_rotation);
//      cout << "I'm " << m_name << ", parent has tsr:" << endl;
//      parent_tsr.print();
//      cout << "my tsr: " << endl;
//      my_translation.print();
        tsr *= my_translation;
//      cout << "result tsr:" << endl;
//      tsr.print();

        dump_me(ss, tsr, vc, nc);

        for (list<Assembly*>::const_iterator it = m_part.begin(); it != m_part.end(); ++it)
        {
                ss << endl << "o " << (*it)->m_name << endl;
                (*it)->ObjExport(ss, tsr, vc, nc);
        }
}

void Assembly::dump_me(ostream& ss, const Matrix4D& parent_tsr, int& vc, int& nc)
{
	map<const Vertex*, int> vmap, nmap;

	if (isOriginal())
	{
		string act_matname = m_matname;
		if (m_face.begin() != m_face.end())
		{
			ss << "usemtl " << m_matname << endl;
		}
		for (list<Face*>::const_iterator it = m_face.begin(); it != m_face.end(); ++it)
		{
			const string& face_mat = (*it)->material();
			if (face_mat != act_matname)
			{
				act_matname = face_mat;
				ss << "usemtl " << act_matname << endl;
			}
			ss << (*it)->toString(parent_tsr, vmap, nmap, vc, nc);
		}
	}
	else
	{
		Assembly* orig = getOrigin();
		string act_matname = m_matname;
		if (orig->m_face.begin() != orig->m_face.end())
		{
			ss << "usemtl " << m_matname << endl;
		}
		for (list<Face*>::const_iterator it = orig->m_face.begin(); it != orig->m_face.end(); ++it)
		{
			const string& face_mat = (*it)->material();
			if (face_mat != act_matname)
			{
				act_matname = face_mat;
				ss << "usemtl " << act_matname << endl;
			}
			ss << (*it)->toString(parent_tsr, vmap, nmap, vc, nc);
		}
	}
}
