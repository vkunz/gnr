/**
 * GNRAssembly
 * @name                GNRAssembly.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRASSEMBLY_H_
#define _GNRASSEMBLY_H_

#ifdef _WIN32
#include <gl/glu.h>
#endif

#include <list>
#include <vector>
#include <map>
#include <wx/string.h>

#include "GNREnum.h"
#include "GNRFace.h"
#include "GNRVertex.h"
#include "GNRMaterial.h"

using std::list;
using std::vector;
using std::map;
using std::pair;

class GNRAssembly
{
public:

	GNRAssembly(const wxString& name);
	GNRAssembly(GNRAssembly* parent, const wxString& name);
	GNRAssembly(const assemblyType& type, const wxString& name);
	GNRAssembly(GNRAssembly& assembly);
	
	virtual ~GNRAssembly();
	
	bool isVisible() const;
	float getX() const;
	float getY() const;
	float getZ() const;
	
	float getRadiusTop() const;
	float getRadiusMiddle() const;
	float getRadiusBottom() const;
	
	float getHeight() const;
	float getWidth() const;
	float getDepth() const;
	float getMaximumSize() const;
	GNRVertex getCenterVertex() const;
	GNRVertex getRotateVertex() const;
	
	void setVisible(bool status);
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);
	void setXY(const float x,const float y);
	void setXZ(const float x,const float z);
	void setXYZ(const float x, const float y, const float z);
	void setCenterVertex(const GNRVertex& center);
	void setRotateVertex(const GNRVertex& rotation);
	void move(const GNRVertex& center);
	
	void setRadiusBottom(const float r);
	void setRadiusMiddle(const float r);
	void setRadiusTop(const float r);
	
	void setCone(const float x,const float y,const float z, const float height, const float r_top, const float r_bottom);
	void setCylinder(const float x,const float y,const float z, const float height, const float radius);
	void setSphere(const float x,const float y,const float z, const float radius);
	void setCuboid(const float x,const float y,const float z, const float width,const float height,const float depth);
	
	void setHeight(const float height);
	void setWidth(const float width);
	void setDepth(const float depth);
	void setSize(const float width,const float height,const float depth);
	
	float getPhi() const;
	float getRho() const;
	float getTheta() const;
	
	void setPhi(const float phi);
	void setRho(const float rho);
	void setTheta(const float theta);
	void setPhiTheta(const float phi,const float theta);
	void setPhiRho(const float phi,const float rho);
	
	float getScaleX() const;
	float getScaleY() const;
	float getScaleZ() const;
	
	float getWidthMeters() const;
	float getHeightMeters() const;
	float getDepthMeters() const;
	
	void setScaleX(const float x);
	void setScaleY(const float y);
	void setScaleZ(const float z);
	void setScale(const float x,const float y,const float z);
	
	void addFace(const GNRFace& newface);
	void addPart(GNRAssembly* part);
	void delPart(GNRAssembly* part);
	
	void setChildMaterial(const GNRAssembly* child, const GNRMaterial& mat);
	void setChildDisplayList(const GNRAssembly* child, const GLuint& dl);
	
	void setName(const wxString& name);
	void setName(const string& name);
	const wxString& getName() const;
	
	void setType(const assemblyType& type);
	assemblyType getType() const;
	bool isType(const assemblyType& type);
	
	const wxString& getHash() const;
	void setHash(const wxString& hash);
	
	GNRAssembly* clone();
	GNRAssembly* cloneDisplayListFrom(GNRAssembly* assembly);
	GNRAssembly* getOrigin() const;
	GNRAssembly* getParent() const;
	GNRAssembly* getMaster() const;
	void setParent(GNRAssembly* p);
	
	float getOverGround() const;
	void putOnGround();
	void setNormals();
	void resetOnGround();
	
	void draw();
	void drawShadow();
	
	void debugInfo() const;
	list<GNRAssembly*> getPartList();
	
	// add a new Tag
	void addTag(wxString tag);
	list<wxString> getTagList();
	
private:
	float m_x, m_y, m_z;
	
	//Rotation along X-, Y-, and Z-Axis
	float m_phi, m_theta, m_rho;
	
	//scale factor for dimension correction
	float m_scale_x, m_scale_y, m_scale_z;
	
	//whole size of assembly surrounding cube
	float m_width, m_height, m_depth;
	
	//radius (middle = sphere, bottom & top = cone, cylinder)
	float m_radius_bottom, m_radius_middle, m_radius_top;
	
	assemblyType m_type;
	wxString m_name;
	
	//visible flag
	bool m_visible;
	
	GNRAssembly* m_parent;
	GNRAssembly* m_origin;
	
	//my display list and shadows
	GLuint m_dl_object;
	GLuint m_dl_shadow;
	
	wxString m_md5_obj_xml;
	
	list<GNRFace>      m_face;
	list<GNRAssembly*> m_part;
	
	//ChildPtr ==> GNRMaterial
	map<const GNRAssembly* const, GNRMaterial> m_child_mat;
	
	//ChildPtr ==> display list
	map<const GNRAssembly* const, GLuint> m_child_dl;
	
	// list of tags
	list<wxString> m_tags;
};

#endif // _GNRASSEMBLY_H_
