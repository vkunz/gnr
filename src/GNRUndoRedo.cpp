#include "GNRUndoRedo.h"
#include "GNRNotifyEvent.h"
#include "GNREnum.h"

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

// initialize pointer
GNRUndoRedo* GNRUndoRedo::pinstance = 0;

GNRUndoRedo::GNRUndoRedo()
{
	//ctor
}

GNRUndoRedo::~GNRUndoRedo()
{
	//dtor
}

GNRUndoRedo* GNRUndoRedo::getInstance()
{
	if (pinstance == 0)
	{
		pinstance = new GNRUndoRedo;
	}
	return pinstance;
}

void GNRUndoRedo::enqueue(GNRCommand* command)
{
	emptyRedoStack();
	m_undo.push(command);
	
	// send event to enable undo button
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SETUNDOENABLED);
	gnrevent.SetInt(1);
	ProcessEvent(gnrevent);
}

void GNRUndoRedo::undo()
{
	if (!m_undo.empty())
	{
		// unexecute last command from undo stack and push on redo stack
		GNRCommand* command = m_undo.top();
		command->unexecute();
		m_redo.push(command);
		m_undo.pop();
	}
	
	// send event to enable redo button
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SETREDOENABLED);
	gnrevent.SetInt(1);
	ProcessEvent(gnrevent);
	
	// send event to diable undo button if undo-stack is empty
	if (m_undo.empty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(SETUNDOENABLED);
		gnrevent.SetInt(0);
		ProcessEvent(gnrevent);
	}
}

void GNRUndoRedo::redo()
{
	if (!m_redo.empty())
	{
		GNRCommand* command = m_redo.top();
		command->execute();
		m_undo.push(command);
		m_redo.pop();
	}
	
	// send event to enable undo button
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SETUNDOENABLED);
	gnrevent.SetInt(1);
	ProcessEvent(gnrevent);
	
	// send event to disable redo button if redo-stack is empty
	if (m_redo.empty())
	{
		GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
		gnrevent.setGNREventType(SETREDOENABLED);
		gnrevent.SetInt(0);
		ProcessEvent(gnrevent);
	}
}

void GNRUndoRedo::emptyRedoStack()
{
	GNRCommand* command;
	while (!m_redo.empty())
	{
		command = m_redo.top();
		delete command;
		m_redo.pop();
	}
	
	// send event to disable redo button
	GNRNotifyEvent gnrevent(wxEVT_COMMAND_GNR_NOTIFY);
	gnrevent.setGNREventType(SETREDOENABLED);
	gnrevent.SetInt(0);
	ProcessEvent(gnrevent);
	
}
