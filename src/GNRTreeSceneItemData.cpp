/**
 * GNRTreeSceneItemData
 * @name        	GNRTreeSceneItemData.cpp
 * @date        	2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRTreeSceneItemData.h"

GNRTreeSceneItemData::GNRTreeSceneItemData()
{
	//ctor
}

GNRTreeSceneItemData::~GNRTreeSceneItemData()
{
	//dtor
}

void GNRTreeSceneItemData::setAssembly(GNRAssembly* assembly)
{
	m_assembly = assembly;
}

GNRAssembly* GNRTreeSceneItemData::getAssembly()
{
	return m_assembly;
}

GNRAssembly* GNRTreeSceneItemData::getMaster()
{
	return m_assembly->getMaster();
}
