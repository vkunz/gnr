#ifndef GNRTreeSceneItemData_H
#define GNRTreeSceneItemData_H

#include <wx/treectrl.h>
#include <wx/string.h>

#include "GNRAssembly.h"

class GNRTreeSceneItemData: public wxTreeItemData
{
public:
	GNRTreeSceneItemData();
	virtual ~GNRTreeSceneItemData();
	
	void setAssembly(GNRAssembly* assembly);
	void setName(wxString name);
	
	GNRAssembly* getAssembly();
	wxString getName();
protected:
private:
	GNRAssembly* m_assembly;
	wxString m_name;
};

#endif // GNRTreeSceneItemData_H
