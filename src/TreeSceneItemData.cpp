/**
 * TreeSceneItemData
 * @name        	TreeSceneItemData.cpp
 * @date        	2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "Assembly.h"
#include "TreeSceneItemData.h"

/**
 * constructor of TreeSceneItemData
 */
TreeSceneItemData::TreeSceneItemData()
{
}

/**
 * destructor of TreeSceneItemData
 */
TreeSceneItemData::~TreeSceneItemData()
{
}

/**
 * set current assembly
 * @param[in]       assembly        pointer to actual assembly
 */
void TreeSceneItemData::setAssembly(Assembly* assembly)
{
	m_assembly = assembly;
}

/**
 * get assembly from tree
 * @return      Assembly*           pointer to actual assembly
 */
Assembly* TreeSceneItemData::getAssembly()
{
	return m_assembly;
}

/**
 * get master assembly from tree
 * @return      Assembly*           pointer to actual master assembly
 */
Assembly* TreeSceneItemData::getMaster()
{
	return m_assembly->getMaster();
}
