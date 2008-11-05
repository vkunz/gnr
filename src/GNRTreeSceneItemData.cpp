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

void GNRTreeSceneItemData::setName(wxString name)
{
	m_name = name;
}

wxString GNRTreeSceneItemData::getName()
{
	return m_name;
}
