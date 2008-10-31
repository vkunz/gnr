#include "GNRPrimitiveCreator.h"

#include "GNRVNT.h"
#include "GNRTCoord.h"

GNRPrimitiveCreator::GNRPrimitiveCreator()
{
	//ctor
}

GNRPrimitiveCreator::~GNRPrimitiveCreator()
{
	//dtor
}

GNRAssembly* GNRPrimitiveCreator::createCuboid(const GNRVertex& position, const GNRVertex& angles, const GNRVertex& dimension)
{
	GNRAssembly* cuboid = new GNRAssembly("cuboid");
	
	// set position of the cuboid
	cuboid->setX(position.getX());
	cuboid->setY(position.getY());
	cuboid->setZ(position.getZ());
	
	// set rotation of the cuboid
	cuboid->setPhi(angles.getX());
	cuboid->setTheta(angles.getY());
	cuboid->setRho(angles.getZ());
	
	// set size of the cuboid
	cuboid->setWidth(dimension.getX());
	cuboid->setHeight(dimension.getY());
	cuboid->setDepth(dimension.getZ());
	
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
	cuboid->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create right face
	topLeft.setXYZ(x, y, z);
	bottomLeft.setXYZ(x, -y, z);
	bottomRight.setXYZ(x, -y, -z);
	topRight.setXYZ(x, y, -z);
	normal.setXYZ(1, 0, 0);
	cuboid->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create back face
	topLeft.setXYZ(x, y, -z);
	bottomLeft.setXYZ(x, -y, -z);
	bottomRight.setXYZ(-x, -y, -z);
	topRight.setXYZ(-x, y, -z);
	normal.setXYZ(0, 0, -1);
	cuboid->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create left face
	topLeft.setXYZ(-x, y, -z);
	bottomLeft.setXYZ(-x, -y, -z);
	bottomRight.setXYZ(-x, -y, z);
	topRight.setXYZ(-x, y, z);
	normal.setXYZ(-1, 0, 0);
	cuboid->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create upper face
	topLeft.setXYZ(-x, y, -z);
	bottomLeft.setXYZ(-x, y, z);
	bottomRight.setXYZ(x, y, z);
	topRight.setXYZ(x, y, -z);
	normal.setXYZ(0, 1, 0);
	cuboid->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	// create bottom face
	bottomLeft.setXYZ(-x, -y, -z);
	topLeft.setXYZ(-x, -y, z);
	topRight.setXYZ(x, -y, z);
	bottomRight.setXYZ(x, -y, -z);
	
	normal.setXYZ(0, -1, 0);
	cuboid->addFace(*createFace(topLeft, bottomLeft, bottomRight, topRight, normal));
	
	return cuboid;
}

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
