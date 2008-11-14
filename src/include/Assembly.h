#ifndef _GNRASSEMBLY_H_
#define _GNRASSEMBLY_H_

/**
 * Assembly
 * @name                Assembly.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <GL/glu.h>

#include <list>
#include <vector>
#include <map>
#include <wx/string.h>

#include "Enum.h"
#include "Face.h"
#include "Vertex.h"
#include "MaterialLibrary.h"


using std::cout;
using std::endl;
using std::fstream;
using std::list;
using std::vector;
using std::map;
using std::pair;

class Assembly
{
public:
	friend class ObjectImport;
	friend class PrimitiveCreator;
	
	Assembly(const wxString& name);
	Assembly(Assembly* parent, const wxString& name);
	Assembly(const assemblyType& type, const wxString& name);
	Assembly(Assembly& assembly);
	
	virtual ~Assembly();
	
	void Assembly::dump2stream(ostream& os, int depth) const;
	
	bool findCloneOf(const Assembly* origin) const;
	bool findHash(const wxString& hash) const;
	bool isOriginal() const;
	bool isSelected() const;
	bool isVisible() const;
	
	// getter and setter for the position of the Assembly
	const Vertex& position() const;
	Vertex& position();
	
	// getter and setter for the rotation angles of the Assembly
	const Vertex& rotation() const;
	Vertex& rotation();
	
	// getter and setter for the scaling factors of the Assembly
	const Vertex& scale() const;
	Vertex& scale();
	
	// getter for the dimensions of the Assembly surrounding cube
	const Vertex& dimension() const;
	Vertex& dimension();
	
	// getter for the world-dimensions of the Assembly surrounding cube
	Vertex world_dimension() const;
	
	// getter and setter for dimensions of the Cuboid
	const Vertex& cuboid_dimension() const;
	Vertex& cuboid_dimension();
	
	// getter and setter for the dimensions of the Cylinder
	// height, r_top, r_bottom
	const Vertex& cylinder_dimension() const;
	Vertex& cylinder_dimension();
	
	// getter and setter for the radius of the Sphere
	float sphere_radius() const;
	float& sphere_radius();
	
	float getMaximumSize() const;
	
	void setVisible(bool status);
	
	// move the Assembly with the offset
	void move(const Vertex& offset);
	
	void setCylinder(float x, float y, float z, float height, float r_top, float r_bottom);
	void setSphere(float x, float y, float z, float radius);
	void setCuboid(float x, float y, float z, float width, float height, float depth);
	
	void addFace(Face* newface);
	void addPart(Assembly* part);
	void delPart(Assembly* part);
	
	void setChildMaterial(const Assembly* child, const Material& mat);
	void setChildDisplayList(const Assembly* child, const GLuint& dl);
	
	void setName(const wxString& name);
	void setName(const string& name);
	const wxString& getName() const;
	
	void setType(const assemblyType& type);
	assemblyType getType() const;
	bool isType(const assemblyType& type);
	void setPrimitiveType(const primitiveType ptype);
	primitiveType getPrimitiveType() const;
	
	const wxString& getHash() const;
	void setHash(const wxString& hash);
	
	void cloneDisplayListFrom(Assembly* assembly);
	Assembly* clone();
	Assembly* getOrigin() const;
	Assembly* getParent() const;
	Assembly* getMaster() const;
	Assembly* getHashOriginal(const wxString& hash) const;
	void setParent(Assembly* p);
	
	float getOverGround() const;
	void putOnGround();
	void setNormals();
	void resetOnGround();
	
	void draw();
	void drawShadow();
	
#if defined(__ATHOS_DEBUG__)
	void debugInfo() const;
	void dump(wxString str);
#endif
	list<Assembly*> getPartList();
	
	// add a new Tag
	void addTag(wxString tag);
	list<wxString> getTagList();
	
	void setMaterial(const string& mat);
	
	void ObjExport(const string& fname);
	
private:
	// translate the origin, scale, then rotate
	// with the Translate-Scale-Rotate-Matrix,
	// eventually do the deep dump of the object
	void ObjExport(ostream& ss, const Matrix4D& parent_tsr, int& vc, int& nc);
	// do the flat dump of the TSR'd object, counting vertex and normals
	void dump_me(ostream& ss, const Matrix4D& parent_tsr, int& vc, int& nc);
	
	// position, rotation and scale of the Assembly
	Vertex m_position, m_rotation, m_scale;
	// dimensions of the cube surrounding the assembly
	Vertex m_dimension;
	
	// dimensions of the Cuboid
	Vertex m_cuboid;
	// dimensions of the Cylinder
	Vertex m_cylinder;
	// radius of the Sphere
	float m_radius;
	
	assemblyType m_type;
	wxString m_name;
	
	//visible flag
	bool m_visible;
	
	//kill display lists
	bool m_kill_dl;
	
	Assembly* m_parent;
	Assembly* m_origin;
	
	//my display list and one for the shadow
	GLuint m_dl_object;
	GLuint m_dl_shadow;
	
	wxString m_md5_obj_xml;
	
	list<Assembly*> m_part;
	list<Face*> m_face;
	vector<Vertex*> m_vertex;
	vector<Vertex*> m_normal;
	
	//ChildPtr ==> display list
	map<const Assembly* const, GLuint> m_child_dl;
	
	// list of tags
	list<wxString> m_tags;
	
	//type of primitive
	primitiveType m_ptype;
	string m_matname;
};

#endif // _GNRASSEMBLY_H_
