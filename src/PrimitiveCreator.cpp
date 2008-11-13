/**
 * This class creates assemblies of primitives types
 * @name        PrimitiveCreator.cpp
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "PrimitiveCreator.h"

#include "VNT.h"
#include "TCoord.h"
#include "MaterialLibrary.h"

/**
 * constructor of PrimitiveCreator
 */
PrimitiveCreator::PrimitiveCreator():m_primitive(NULL)
{
}

/**
 * destructor of PrimitiveCreator
 */
PrimitiveCreator::~PrimitiveCreator()
{
}

/**
 * return ready to use object
 * @return    Assembly*   pointer to object
 */
Assembly* PrimitiveCreator::getPrimitive()
{
	//return build primitive
	return m_primitive;
}

/**
 * creates a new cuboid assembly, calculates the vertices, normals and sets position and angles
 * @param   	position  		position of the assembly
 * @param   	angles  		rotation of the assembly
 * @param   	dimension  		dimensions of the assembly
 */
void PrimitiveCreator::createCuboid(const Vertex& position, const Vertex& angles, const Vertex& dimension)
{
	m_primitive = new Assembly(wxT("noname"));
	
	//set it to atomic, is smallest part i'll produce
	m_primitive->setType(IS_ATOMIC);
	
	// set position of the cuboid
	m_primitive->setCuboid(position.getX(), position.getY(), position.getZ(), dimension.getX(), dimension.getY(), dimension.getZ());
	
	// set rotation of the cuboid
	m_primitive->rotation() = angles;
	
	// prepare points
	float x = dimension.getX() / 2.0;
	float y = dimension.getY() / 2.0;
	float z = dimension.getZ() / 2.0;
	
	// create front face
	Vertex topLeft(-x, y, z);
	Vertex bottomLeft(-x, -y, z);
	Vertex bottomRight(x, -y, z);
	Vertex topRight(x, y, z);
	Vertex normal(0, 0, 1);
	m_primitive->addFace(createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create right face
	topLeft.setAll(x, y, z);
	bottomLeft.setAll(x, -y, z);
	bottomRight.setAll(x, -y, -z);
	topRight.setAll(x, y, -z);
	normal.setAll(1, 0, 0);
	m_primitive->addFace(createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create back face
	topLeft.setAll(x, y, -z);
	bottomLeft.setAll(x, -y, -z);
	bottomRight.setAll(-x, -y, -z);
	topRight.setAll(-x, y, -z);
	normal.setAll(0, 0, -1);
	m_primitive->addFace(createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create left face
	topLeft.setAll(-x, y, -z);
	bottomLeft.setAll(-x, -y, -z);
	bottomRight.setAll(-x, -y, z);
	topRight.setAll(-x, y, z);
	normal.setAll(-1, 0, 0);
	m_primitive->addFace(createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create upper face
	topLeft.setAll(-x, y, -z);
	bottomLeft.setAll(-x, y, z);
	bottomRight.setAll(x, y, z);
	topRight.setAll(x, y, -z);
	normal.setAll(0, 1, 0);
	m_primitive->addFace(createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create bottom face
	bottomLeft.setAll(-x, -y, -z);
	topLeft.setAll(-x, -y, z);
	topRight.setAll(x, -y, z);
	bottomRight.setAll(x, -y, -z);
	
	normal.setAll(0, -1, 0);
	m_primitive->addFace(createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
}

void PrimitiveCreator::setMaterial(Assembly* parent, const string& name)
{
	//tell the parent what color his child has got
//	parent->setChildMaterial(m_primitive, m_matlib.getMaterial(name));
}

/**
 * creates quadratic faces, out of vertices and normals
 * @param   	topLeft  		top-left point of the quad
 * @param   	bottomLeft  	bottom-left point of the quad
 * @param   	bottomRight  	bottom-right point of the quad
 * @param   	topRight  		top-right point of the quad
 * @param   	normale	  	normal of the quad
 */
Face* PrimitiveCreator::createFace(Vertex& topLeft, Vertex& bottomLeft, Vertex& bottomRight,
                                   Vertex& topRight, Vertex& normale)
{
	Face* face;
	return face;
}
