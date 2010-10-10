#ifndef _TREESCENEITEMDATA_H_
#define _TREESCENEITEMDATA_H_

#include <wx/treectrl.h>
#include <wx/string.h>

class Assembly;

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

#endif // _TREESCENEITEMDATA_H_
