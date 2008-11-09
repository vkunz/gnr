#ifndef TreeSceneItemData_H
#define TreeSceneItemData_H

#include <wx/treectrl.h>
#include <wx/string.h>

#include "Assembly.h"

class TreeSceneItemData: public wxTreeItemData
{
public:
	TreeSceneItemData();
	virtual ~TreeSceneItemData();
	
	void setAssembly(Assembly* assembly);
	
	Assembly* getAssembly();
	Assembly* getMaster();
protected:
private:
	Assembly* m_assembly;
};

#endif // TreeSceneItemData_H
