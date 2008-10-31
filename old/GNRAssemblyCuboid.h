#ifndef __GNRASSEMBLY_CUBOID_H__
#define __GNRASSEMBLY_CUBOID_H__

/**
 * GNRAssemblyCuboid
 * @name                GNRAssemblyCuboid.h
 * @date                2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssembly.h"

class GNRAssemblyCuboid : public GNRAssembly
{
public:
	GNRAssemblyCuboid(const string& name);
	virtual ~GNRAssemblyCuboid();
	
	float getWidth() const;
	float getHeight() const;
	float getDepth() const;
	
	void setWidth(float width);
	void setHeight(float height);
	void setDepth(float depth);
	
	void genDL();
	
private:
	float m_width, m_height, m_depth;
};

#endif

