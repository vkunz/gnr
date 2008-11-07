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
