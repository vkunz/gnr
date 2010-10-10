/**
 * defines the PrimitiveCreator
 * @name        PrimitiveCreator.h
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _PRIMITIVECREATOR_H_
#define _PRIMITIVECREATOR_H_

#include <string>

#include "GlobalDefine.h"

class Assembly;
class Vertex;

class PrimitiveCreator
{
public:
	PrimitiveCreator();
	virtual ~PrimitiveCreator();
	void createCuboid(const Vertex& position, const Vertex& angles, const Vertex& dimension,const std::string& matname = DEFAULT_IMPORT_COLOR);
	void createSphere(float radius, const std::string& matname = DEFAULT_IMPORT_COLOR);
	Assembly* getPrimitive();
protected:
private:
	Assembly* m_primitive;
};

#endif // _PRIMITIVECREATOR_H_
