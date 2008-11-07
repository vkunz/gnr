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
	
	GNRAssembly* getAssembly();
	GNRAssembly* getMaster();
protected:
private:
	GNRAssembly* m_assembly;
};

#endif // GNRTreeSceneItemData_H
