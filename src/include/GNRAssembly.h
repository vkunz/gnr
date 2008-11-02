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

#include <list>
#include <vector>
#include <map>
#include <string>

#include "GNREnum.h"
#include "GNRFace.h"
#include "GNRVertex.h"
#include "GNRMaterial.h"

using std::list;
using std::vector;
using std::map;
using std::pair;
using std::string;

class GNRAssembly
{
public:

	GNRAssembly(const string& name);
	GNRAssembly(GNRAssembly* parent, const string& name);
	GNRAssembly(const assemblyType& type, const string& name);
	GNRAssembly(const GNRAssembly& assembly);
	
	virtual ~GNRAssembly();
	
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
	
	void setX(const float x);
	void setY(const float y);
	void setZ(const float z);
	void setXY(const float x,const float y);
	void setXZ(const float x,const float z);
	void setXYZ(const float x, const float y, const float z);
	void setCenterVertex(const GNRVertex& center);
	void setRotateVertex(const GNRVertex& rotation);
	
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
	
	void setScaleX(const float x);
	void setScaleY(const float y);
	void setScaleZ(const float z);
	void setScale(const float x,const float y,const float z);
	
	void addFace(const GNRFace& newface);
	void addPart(GNRAssembly* part);
	void delPart(GNRAssembly* part);
	
	void setChildMaterial(const GNRAssembly* child, const GNRMaterial& mat);
	
	void setName(const string& name);
	const string& getName() const;
	
	void setType(const assemblyType& type);
	assemblyType getType() const;
	bool isType(const assemblyType& type);
	
	GNRAssembly* clone();
	GNRAssembly* getParent() const;
	GNRAssembly* getMaster() const;
	void setParent(GNRAssembly* p);
	
	float getOverGround() const;
	void putOnGround();
	void setNormals();
	
	void draw() const;
	void drawShadow() const;
	
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
	string m_name;
	
	GNRAssembly* m_parent;
	
	list<GNRFace> m_face;
	list<GNRAssembly*> m_part;
	
	//  ChildPtr ==> material_name
	map<const GNRAssembly* const, GNRMaterial> m_child_mat;
	
	// list of tags
	list<wxString> m_tags;
};

#endif // _GNRASSEMBLY_H_
