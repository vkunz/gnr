/**
 * UndoRedo-Singleton-Class handels all possible undo and redo operations that can
 * be done within the application. It manages the stacks and calls the derived command-classes
 * to un-/redo their operations
 * @name        UndoRedo.cpp
 * @date        2008-10-29
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "UndoRedo.h"
#include "NotifyEvent.h"
#include "Enum.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

// initialize pointer
UndoRedo* UndoRedo::pinstance = 0;

/**
 * constructor of UndoRedo
 */
UndoRedo::UndoRedo() {}

/**
 * destructor of UndoRedo
 */
UndoRedo::~UndoRedo() {}

/**
 * creates a new class if not instantiated or returns a pointer to the object if already
 * instantiated before
 * two cameras for 2D and 3D
 */
UndoRedo* UndoRedo::getInstance()
{
	if (pinstance == 0)
	{
		pinstance = new UndoRedo;
	}
	return pinstance;
}

/**
 * adds a new command-object with information to un-/redo the operation to the stack
 * @param   	command		Pointer to a class derived from Command that handels un-/redo information
 */
void UndoRedo::enqueue(Command* command)
{
	emptyRedoStack();
	m_undo.push(command);
	
	// send event to enable undo button
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SETUNDOENABLED);
	gnrevent.SetInt(1);
	ProcessEvent(gnrevent);
}

/**
 * unexecutes the last command, pushed to the undo-stack
 */
void UndoRedo::undo()
{
	if (!m_undo.empty())
	{
		// unexecute last command from undo stack and push on redo stack
		Command* command = m_undo.top();
		command->unexecute();
		m_redo.push(command);
		m_undo.pop();
	}
	
	// send event to enable redo button
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SETREDOENABLED);
	gnrevent.SetInt(1);
	ProcessEvent(gnrevent);
	
	// send event to diable undo button if undo-stack is empty
	if (m_undo.empty())
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(SETUNDOENABLED);
		gnrevent.SetInt(0);
		ProcessEvent(gnrevent);
	}
}

/**
 * executes the last command, pushed to redo-stack
 */
void UndoRedo::redo()
{
	if (!m_redo.empty())
	{
		Command* command = m_redo.top();
		command->execute();
		m_undo.push(command);
		m_redo.pop();
	}
	
	// send event to enable undo button
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SETUNDOENABLED);
	gnrevent.SetInt(1);
	ProcessEvent(gnrevent);
	
	// send event to disable redo button if redo-stack is empty
	if (m_redo.empty())
	{
		NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(SETREDOENABLED);
		gnrevent.SetInt(0);
		ProcessEvent(gnrevent);
	}
}

/**
 * deletes all command-objects from the redo stack
 */
void UndoRedo::emptyRedoStack()
{
	Command* command;
	while (!m_redo.empty())
	{
		command = m_redo.top();
		delete command;
		m_redo.pop();
	}
	
	// send event to disable redo button
	NotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SETREDOENABLED);
	gnrevent.SetInt(0);
	ProcessEvent(gnrevent);
	
}
