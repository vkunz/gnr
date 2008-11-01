/**
 * defines the UndoRedo class
 * @name        GNRUndoRedo.h
 * @date        2008-10-29
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef GNRUNDOREDO_H
#define GNRUNDOREDO_H

#include <stack>
#include "GNRCommand.h"
#include <wx/event.h>

class GNRUndoRedo: public wxEvtHandler
{
public:
	static GNRUndoRedo* getInstance();
	void enqueue(GNRCommand* command);
	void undo();
	void redo();
	virtual ~GNRUndoRedo();
protected:
	GNRUndoRedo();
	GNRUndoRedo(const GNRUndoRedo&);
	GNRUndoRedo& operator= (const GNRUndoRedo&);
private:
	static GNRUndoRedo* pinstance;
	
	std::stack<GNRCommand*> m_undo;
	std::stack<GNRCommand*> m_redo;
	
	void emptyRedoStack();
	
};

#endif // GNRUNDOREDO_H
