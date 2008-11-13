/**
 * This class handels all the information, needed to undo/redo a translation to an assembly
 * and also performs these operations
 * @note        [DONE]
 * @name        CommandTransform.cpp
 * @date        2008-10-29
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "CommandTransform.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

/**
 * constructor of CommandTransform
 */
CommandTransform::CommandTransform() {}

/**
 * destructor of CommandTransform
 */
CommandTransform::~CommandTransform() {}

/**
 * Performes the redo-operation and moves the object back to the new position
 */
void CommandTransform::execute()
{
	m_usedAssembly->position().setAll(new_x, new_y, new_z);
	m_usedAssembly->rotation().setAll(new_phi, new_theta, new_rho);
}

/**
 * Performes the undo-operation and moves the object back to the originally position
 */
void CommandTransform::unexecute()
{
	m_usedAssembly->position().setAll(old_x, old_y, old_z);
	m_usedAssembly->rotation().setAll(old_phi, old_theta, old_rho);
}

/**
 * sets the assembly, the transformation is done with
 * @param[in]           assembly            assembly, the transformation is done with
 */
void CommandTransform::setAssembly(Assembly* assembly)
{
	m_usedAssembly = assembly;
}

/**
 * sets the old position of the assembly, before the transformation
 * @param[in]           old_pos             old position of the assembly
 */
void CommandTransform::setOldPosition(Vertex& old_pos)
{
	old_x = old_pos.getX();
	old_y = old_pos.getY();
	old_z = old_pos.getZ();
}

/**
 * sets the old rotations of the assembly, before the transformation
 * @param[in]           old_angles          old angles of assembly
 */
void CommandTransform::setOldAngles(Vertex& old_angles)
{
	old_phi     = old_angles.getX();
	old_theta   = old_angles.getY();
	old_rho     = old_angles.getZ();
}

/**
 * sets the new position of the assembly, after the transformation
 * @param[in]           new_pos             new position of assembly
 */
void CommandTransform::setNewPosition(Vertex& new_pos)
{
	new_x = new_pos.getX();
	new_y = new_pos.getY();
	new_z = new_pos.getZ();
}

/**
 * sets the new rotations of the assembly, after the transformation
 * @param[in]           new_angles          new angles of assembly
 */
void CommandTransform::setNewAngles(Vertex& new_angles)
{
	new_phi     = new_angles.getX();
	new_theta   = new_angles.getY();
	new_rho     = new_angles.getZ();
}
