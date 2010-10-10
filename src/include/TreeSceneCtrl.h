/**
 * TreeSceneCtrl
 * @name                TreeSceneCtrl.h
 * @date                2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _TREESCENECTRL_H_
#define _TREESCENECTRL_H_

#include <wx/treectrl.h>

class AssemblyDataFrame;
class TreeSceneItemData;

class TreeSceneCtrl : public wxTreeCtrl
{
public:
	TreeSceneCtrl(wxWindow *parent, const wxWindowID id, const wxPoint& pos, const wxSize& size, long style,
	              const wxValidator &validator=wxDefaultValidator, const wxString &name=wxTreeCtrlNameStr);
	virtual ~TreeSceneCtrl();
protected:
private:
	void OnKeyDown(wxKeyEvent& event);
	void OnItemMenu(wxTreeEvent& event);
	void OnItemActivated(wxTreeEvent& event);
	void OnEdit(wxCommandEvent& WXUNUSED(event));
	void OnRename(wxCommandEvent& WXUNUSED(event));
	void OnVisible(wxCommandEvent& WXUNUSED(event));
	void OnHide(wxCommandEvent& WXUNUSED(event));
	void OnSelect(wxCommandEvent& WXUNUSED(event));
	void OnDeselect(wxCommandEvent& WXUNUSED(event));
	void OnDelete(wxCommandEvent& WXUNUSED(event));
	void OnUndelete(wxCommandEvent& WXUNUSED(event));
	void OnEmptyTrash(wxCommandEvent& WXUNUSED(event));

	void buildMenu(const wxPoint& pt);
	void createAssemblyDataFrame();
	void renameItem();

	wxTreeItemId m_currentTreeID;
	TreeSceneItemData* m_treeItemData;

	AssemblyDataFrame* m_assemblyDataFrame;

	static const long idMenuEdit;
	static const long idMenuRename;
	static const long idMenuVisible;
	static const long idMenuHide;
	static const long idMenuSelect;
	static const long idMenuDeselect;
	static const long idMenuDelete;
	static const long idMenuUndelete;
	static const long idMenuEmptyTrash;

	DECLARE_EVENT_TABLE()
};

#endif // _TREESCENECTRL_H_
