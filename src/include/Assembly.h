/**
 * Assembly
 * @name                Assembly.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <GL/glu.h>

//#include <wx/string.h>

#include "Enum.h"
#include "Material.h"
#include "Vertex.h"

class Face;
class Matrix4D;

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

	void dump2stream(std::ostream& os, int depth) const;

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
	void setName(const std::string& name);
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
	std::list<Assembly*> getPartList();

	// add a new Tag
	void addTag(wxString tag);
	std::list<wxString> getTagList();

	void setMaterial(const std::string& mat);

	void ObjExport(const std::string& fname);

private:
	// translate the origin, scale, then rotate
	// with the Translate-Scale-Rotate-Matrix,
	// eventually do the deep dump of the object
	void ObjExport(std::ostream& ss, const Matrix4D& parent_tsr, int& vc, int& nc);
	// do the flat dump of the TSR'd object, counting vertex and normals
	void dump_me(std::ostream& ss, const Matrix4D& parent_tsr, int& vc, int& nc);

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

	std::list<Assembly*> m_part;
	std::list<Face*> m_face;
	std::vector<Vertex*> m_vertex;
	std::vector<Vertex*> m_normal;

	//ChildPtr ==> display list
	std::map<const Assembly* const, GLuint> m_child_dl;

	// list of tags
	std::list<wxString> m_tags;

	//type of primitive
	primitiveType m_ptype;
	std::string m_matname;
};

#endif // _ASSEMBLY_H_
