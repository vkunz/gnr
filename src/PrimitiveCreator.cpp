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
void PrimitiveCreator::createCuboid(const Vertex& position, const Vertex& angles, const Vertex& dimension, const string& matname)
{
	//create main primitive container
	m_primitive = new Assembly(wxT("Cuboid"));

	//set specific tags on assembly
	m_primitive->setType(IS_PRIMITIVE);
	m_primitive->setPrimitiveType(CUBOID);
	m_primitive->setMaterial(matname);

	// set position of the cuboid
	m_primitive->position() = position;

	//put cuboid on ground
	m_primitive->dimension() = dimension;

	// set rotation of the cuboid
	m_primitive->rotation() = angles;

	//create small part in primitive container
	Assembly* atomic = new Assembly(wxT("atomic"));

	//set it to atomic, is smallest part i'll produce
	atomic->setType(IS_ATOMIC);
	atomic->setMaterial(matname);

	//add part to container
	m_primitive->addPart(atomic);


	float x, y, z;

	dimension.getAll(x,y,z);

	x /= 2.0f;
	y /= 2.0f;
	z /= 2.0f;

	atomic->m_vertex.resize(8);
	atomic->m_vertex[0] = new Vertex(-x, y, z);
	atomic->m_vertex[1] = new Vertex(-x, -y, z);
	atomic->m_vertex[2] = new Vertex(x, -y, z);
	atomic->m_vertex[3] = new Vertex(x, y, z);
	atomic->m_vertex[4] = new Vertex(x, -y, -z);
	atomic->m_vertex[5] = new Vertex(x, y, -z);
	atomic->m_vertex[6] = new Vertex(-x, -y, -z);
	atomic->m_vertex[7] = new Vertex(-x, y, -z);

	atomic->m_normal.resize(6);
	atomic->m_normal[0] = new Vertex(0.0f, 0.0f, 1.0f, 0.0f);
	atomic->m_normal[1] = new Vertex(1.0f, 0.0f, 0.0f, 0.0f);
	atomic->m_normal[2] = new Vertex(0.0f, 0.0f, -1.0f, 0.0f);
	atomic->m_normal[3] = new Vertex(-1.0f, 0.0f, 0.0f, 0.0f);
	atomic->m_normal[4] = new Vertex(0.0f, 1.0f, 0.0f, 0.0f);
	atomic->m_normal[5] = new Vertex(0.0f, -1.0f, 0.0f, 0.0f);

	// front
	Face* face = new Face(true);
	face->material() = matname;
	face->push_back(atomic->m_vertex[0], atomic->m_normal[0]);
	face->push_back(atomic->m_vertex[1], atomic->m_normal[0]);
	face->push_back(atomic->m_vertex[2], atomic->m_normal[0]);
	face->push_back(atomic->m_vertex[3], atomic->m_normal[0]);
	atomic->m_face.push_back(face);

	// right
	face = new Face(true);
	face->material() = matname;
	face->push_back(atomic->m_vertex[3], atomic->m_normal[1]);
	face->push_back(atomic->m_vertex[2], atomic->m_normal[1]);
	face->push_back(atomic->m_vertex[4], atomic->m_normal[1]);
	face->push_back(atomic->m_vertex[5], atomic->m_normal[1]);
	atomic->m_face.push_back(face);

	// back
	face = new Face(true);
	face->material() = matname;
	face->push_back(atomic->m_vertex[5], atomic->m_normal[2]);
	face->push_back(atomic->m_vertex[4], atomic->m_normal[2]);
	face->push_back(atomic->m_vertex[6], atomic->m_normal[2]);
	face->push_back(atomic->m_vertex[7], atomic->m_normal[2]);
	atomic->m_face.push_back(face);

	// left
	face = new Face(true);
	face->material() = matname;
	face->push_back(atomic->m_vertex[7], atomic->m_normal[3]);
	face->push_back(atomic->m_vertex[6], atomic->m_normal[3]);
	face->push_back(atomic->m_vertex[1], atomic->m_normal[3]);
	face->push_back(atomic->m_vertex[0], atomic->m_normal[3]);
	atomic->m_face.push_back(face);

	// top
	face = new Face(true);
	face->material() = matname;
	face->push_back(atomic->m_vertex[7], atomic->m_normal[4]);
	face->push_back(atomic->m_vertex[0], atomic->m_normal[4]);
	face->push_back(atomic->m_vertex[3], atomic->m_normal[4]);
	face->push_back(atomic->m_vertex[5], atomic->m_normal[4]);
	atomic->m_face.push_back(face);

	// bottom
	face = new Face(true);
	face->material() = matname;
	face->push_back(atomic->m_vertex[1], atomic->m_normal[5]);
	face->push_back(atomic->m_vertex[6], atomic->m_normal[5]);
	face->push_back(atomic->m_vertex[4], atomic->m_normal[5]);
	face->push_back(atomic->m_vertex[2], atomic->m_normal[5]);
	atomic->m_face.push_back(face);
}
