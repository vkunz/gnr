/**
 * defines the UndoRedo class
 * @name        UndoRedo.h
 * @date        2008-10-29
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef UNDOREDO_H
#define UNDOREDO_H

#include <stack>
#include "Command.h"
#include <wx/event.h>

class UndoRedo: public wxEvtHandler
{
public:
	static UndoRedo* getInstance();
	void enqueue(Command* command);
	void undo();
	void redo();
	virtual ~UndoRedo();
protected:
	UndoRedo();
	UndoRedo(const UndoRedo&);
	UndoRedo& operator= (const UndoRedo&);
private:
	static UndoRedo* pinstance;
	
	std::stack<Command*> m_undo;
	std::stack<Command*> m_redo;
	
	void emptyRedoStack();
	
};

#endif // UNDOREDO_H
