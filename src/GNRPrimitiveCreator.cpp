/**
 * This class creates assemblies of primitives types
 * @name        GNRPrimitiveCreator.cpp
 * @date        2008-10-31
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRPrimitiveCreator.h"

#include "GNRVNT.h"
#include "GNRTCoord.h"
#include "GNRMaterialLibrary.h"

/**
 * constructor of GNRPrimitiveCreator
 */
GNRPrimitiveCreator::GNRPrimitiveCreator():m_primitive(NULL)
{
	GNRMaterialLibrary m_matlib = GNRMaterialLibrary();
}

/**
 * destructor of GNRPrimitiveCreator
 */
GNRPrimitiveCreator::~GNRPrimitiveCreator()
{
}

/**
 * return ready to use object
 * @return    GNRAssembly*   pointer to object
 */
GNRAssembly* GNRPrimitiveCreator::getPrimitive()
{
	//return build primitive
	return m_primitive;
}

/**
 * creates a new cuboid assembly, calculates the vertexes, normals and sets position and angles
 * @param   	position  		position of the assembly
 * @param   	angles  		rotation of the assembly
 * @param   	dimension  		dimensions of the assembly
 */
void GNRPrimitiveCreator::createCuboid(const GNRVertex& position, const GNRVertex& angles, const GNRVertex& dimension)
{
	m_primitive = new GNRAssembly(wxT("noname"));
	
	//set it to atomic, is smallest part i'll produce
	m_primitive->setType(IS_ATOMIC);
	
	// set position of the cuboid
	m_primitive->setCuboid(position.getX(),position.getY(),position.getZ(),dimension.getX(),dimension.getY(),dimension.getZ());
	
	// set rotation of the cuboid
	m_primitive->setPhi(angles.getX());
	m_primitive->setTheta(angles.getY());
	m_primitive->setRho(angles.getZ());
	
	// prepare points
	float x = dimension.getX() / 2.0;
	float y = dimension.getY() / 2.0;
	float z = dimension.getZ() / 2.0;
	
	// create front face
	GNRVertex topLeft(-x, y, z);
	GNRVertex bottomLeft(-x, -y, z);
	GNRVertex bottomRight(x, -y, z);
	GNRVertex topRight(x, y, z);
	GNRVertex normal(0, 0, 1);
	m_primitive->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create right face
	topLeft.setXYZ(x, y, z);
	bottomLeft.setXYZ(x, -y, z);
	bottomRight.setXYZ(x, -y, -z);
	topRight.setXYZ(x, y, -z);
	normal.setXYZ(1, 0, 0);
	m_primitive->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create back face
	topLeft.setXYZ(x, y, -z);
	bottomLeft.setXYZ(x, -y, -z);
	bottomRight.setXYZ(-x, -y, -z);
	topRight.setXYZ(-x, y, -z);
	normal.setXYZ(0, 0, -1);
	m_primitive->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create left face
	topLeft.setXYZ(-x, y, -z);
	bottomLeft.setXYZ(-x, -y, -z);
	bottomRight.setXYZ(-x, -y, z);
	topRight.setXYZ(-x, y, z);
	normal.setXYZ(-1, 0, 0);
	m_primitive->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create upper face
	topLeft.setXYZ(-x, y, -z);
	bottomLeft.setXYZ(-x, y, z);
	bottomRight.setXYZ(x, y, z);
	topRight.setXYZ(x, y, -z);
	normal.setXYZ(0, 1, 0);
	m_primitive->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create bottom face
	bottomLeft.setXYZ(-x, -y, -z);
	topLeft.setXYZ(-x, -y, z);
	topRight.setXYZ(x, -y, z);
	bottomRight.setXYZ(x, -y, -z);
	
	normal.setXYZ(0, -1, 0);
	m_primitive->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
}

void GNRPrimitiveCreator::setMaterial(GNRAssembly* parent, const string& name)
{
	//tell the parent what color his child has got
	parent->setChildMaterial(m_primitive, m_matlib.getMaterial(name));
}

/**
 * creates quadratic faces, out of vertexes and normals
 * @param   	topLeft  		top-left point of the quad
 * @param   	bottomLeft  	bottom-left point of the quad
 * @param   	bottomRight  	bottom-right point of the quad
 * @param   	topRight  		top-right point of the quad
 * @param   	normale	  	normal of the quad
 */
GNRFace* GNRPrimitiveCreator::createFace(GNRVertex& topLeft, GNRVertex& bottomLeft, GNRVertex& bottomRight,
        GNRVertex& topRight, GNRVertex& normale)
{

	GNRFace* face = new GNRFace();
	
	GNRVertex* vector = new GNRVertex(topLeft);
	GNRVertex* normal = new GNRVertex(normale);
	GNRTCoord* tcoord = new GNRTCoord(0, 1);
	GNRVNT vnt(vector, normal ,tcoord);
	face->addVNT(vnt);
	
	vector = new GNRVertex(bottomLeft);
	normal = new GNRVertex(normale);
	tcoord = new GNRTCoord(0, 0);
	GNRVNT vnt2(vector, normal, tcoord);
	face->addVNT(vnt2);
	
	vector = new GNRVertex(bottomRight);
	normal = new GNRVertex(normale);
	tcoord = new GNRTCoord(1, 0);
	GNRVNT vnt3(vector, normal,tcoord);
	face->addVNT(vnt3);
	
	vector = new GNRVertex(topRight);
	normal = new GNRVertex(normale);
	tcoord = new GNRTCoord(1, 1);
	GNRVNT vnt4(vector, normal, tcoord);
	face->addVNT(vnt4);
	
	return face;
}
