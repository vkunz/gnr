/**
 * OpxImport
 * @name        OpxImport.h
 * @date        2008-10-26
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _OPXIMPORT_H_
#define _OPXIMPORT_H_

#include <wx/event.h>
#include <wx/thread.h>
#include <wx/tokenzr.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>
#include <wx/zipstrm.h>

class Assembly;
class GLCamera;
class Scene;
class TreeLibraryController;

/**
 * @class OpxImport
 *
 * This class creates a Scene of a opx-File.
 *
 * Internally a OaxImport is used.
 *
 * @see OaxImport
 */
class OpxImport: public wxThread, public wxEvtHandler
{
public:
	// ctor
	OpxImport();
	virtual ~OpxImport();

	OpxImport(TreeLibraryController* controller, wxString filename);

	virtual void *Entry();

protected:

private:
	// attributes
	// string to store filename of opx
	wxString m_filename;

	// pointer to librarycontroller to store oax
	TreeLibraryController* m_libctrl;

	// string to store obj-filename
	wxString m_objName;

	// pointer to Assembly
	Assembly* m_actual;

	// pointer of scene
	Scene* m_scene;

	// pointer of camera
	GLCamera* m_camera;

	// vector of all entrys
	std::vector<wxZipEntry*> m_vector;

	// string to store projectInformation -> ProjectName
	wxString m_name;

	// string to store projectInformation -> Author
	wxString m_author;

	// functions
	// loads file
	void Load(wxZipInputStream& stream);

	// load xml
	void loadXml(wxZipInputStream& stream);

	// load oax
	Assembly* loadOax(wxZipInputStream& stream, wxString reference);

	// create new assembly
	void CreateAssembly(wxZipInputStream& stream);

	// create new group
	void CreateGroup(wxZipInputStream& stream);

	void OnExit();
};

#endif // _OPXIMPORT_H_
