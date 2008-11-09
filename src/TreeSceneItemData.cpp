/**
 * TreeSceneItemData
 * @name        	TreeSceneItemData.cpp
 * @date        	2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "TreeSceneItemData.h"

TreeSceneItemData::TreeSceneItemData()
{
	//ctor
}

TreeSceneItemData::~TreeSceneItemData()
{
	//dtor
}

void TreeSceneItemData::setAssembly(Assembly* assembly)
{
	m_assembly = assembly;
}

Assembly* TreeSceneItemData::getAssembly()
{
	return m_assembly;
}

Assembly* TreeSceneItemData::getMaster()
{
	return m_assembly->getMaster();
}
