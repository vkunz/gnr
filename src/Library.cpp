#include <wx/sstream.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>
#include <wx/zipstrm.h>

#include <memory>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "Library.h"
#include "md5.h"

// set id
unsigned int Library::m_categoryId = 0;

// ctor
Library::Library()
{
	// set filename to standard lib
	m_fileName = ((wxFileName::GetCwd() + wxFileName::GetPathSeparator() + wxT("library.gnr")));
	
	// new categories vector
	m_ptrCategories = new std::vector<LibraryCategory>;
	
	// new entries vector
	m_ptrEntries = new std::vector<LibraryEntry>;
	
	// open library
	openLibrary();
}

// dtor
Library::~Library()
{
}

std::vector<LibraryCategory>* Library::getCategories()
{
	return m_ptrCategories;
}

std::vector<LibraryEntry>* Library::getEntries()
{
	return m_ptrEntries;
}

void Library::addCategory(wxString& name, unsigned int parentId)
{
	// empty xml document
	wxXmlDocument xml;
	
	// set parentId
	m_parentId = parentId;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// input file to open library
	std::auto_ptr<wxFFileInputStream> inFile(new wxFFileInputStream(m_fileName.GetFullPath()));
	
	// temp output file to store new lib
	wxTempFileOutputStream outFile(m_fileName.GetFullPath());
	
	// zip input stream
	wxZipInputStream inzip(*inFile);
	
	// zip output stream
	wxZipOutputStream outzip(outFile);
	
	// copy meta data
	outzip.CopyArchiveMetaData(inzip);
	
	// get first entry of inzip
	entry = inzip.GetNextEntry();
	
	// copy all entries
	while (entry)
	{
		// copy all entries except the old xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			//open entry
			inzip.OpenEntry(*entry);
			
			// new xml
			xml.Load(inzip);
			
			// close entry
			inzip.CloseEntry();
			
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
			
			// add entry into xml
			addXmlCategory(xml, outzip, name);
		}
		
		// if no next entry exist, break
		if (inzip.Eof())
		{
			break;
		}
		
		// copy entry
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// close entry
	outzip.CloseEntry();
	
	// close outzip
	outzip.Close();
	
	// close file
	inFile.reset();
	
	// generate new file
	outFile.Commit();
}

void Library::addEntry(wxString reference, wxInputStream& inStream)
{
	// empty xml document
	wxXmlDocument xml;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// input file to open library
	std::auto_ptr<wxFFileInputStream> inFile(new wxFFileInputStream(m_fileName.GetFullPath()));
	
	// temp output file to store new lib
	wxTempFileOutputStream outFile(m_fileName.GetFullPath());
	
	// zip input stream
	wxZipInputStream inzip(*inFile);
	
	// zip output stream
	wxZipOutputStream outzip(outFile);
	
	// copy meta data
	outzip.CopyArchiveMetaData(inzip);
	
	// get first entry of inzip
	entry = inzip.GetNextEntry();
	
	// copy all entries
	while (entry)
	{
		// copy all entries except the old xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			//open entry
			inzip.OpenEntry(*entry);
			
			// new xml
			xml.Load(inzip);
			
			// close entry
			inzip.CloseEntry();
			
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
			
			// add entry into xml
			addXmlEntry(xml, outzip);
		}
		
		// if end of file reached, break
		if (inzip.Eof())
		{
			break;
		}
		
		// copy all entries
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// new entry
	outzip.PutNextEntry(reference);
	
	// copy data
	inStream.Read(outzip);
	
	// close entry
	outzip.CloseEntry();
	
	// close outzip
	outzip.Close();
	
	// close file
	inFile.reset();
	
	// generate new file
	outFile.Commit();
}

void Library::deleteEntry(wxString reference)
{
	// empty xml document
	wxXmlDocument xml;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// input file to open library
	std::auto_ptr<wxFFileInputStream> inFile(new wxFFileInputStream(m_fileName.GetFullPath()));
	
	// temp output file to store new lib
	wxTempFileOutputStream outFile(m_fileName.GetFullPath());
	
	// zip input stream
	wxZipInputStream inzip(*inFile);
	
	// zip output stream
	wxZipOutputStream outzip(outFile);
	
	// copy meta data
	outzip.CopyArchiveMetaData(inzip);
	
	// get first entry of inzip
	entry = inzip.GetNextEntry();
	
	// copy all entries
	while (entry)
	{
		// copy all entries except the old xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			//open entry
			inzip.OpenEntry(*entry);
			
			// new xml
			xml.Load(inzip);
			
			// close entry
			inzip.CloseEntry();
			
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
			
			// delete entry in xml
			deleteXmlEntry(xml, outzip, reference);
		}
		
		// copy all entries except the one, to be deleted
		if (entry->GetName() == reference)
		{
			// get next entry
			entry = inzip.GetNextEntry();
		}
		
		// copy entry
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// close outzip
	outzip.Close();
	
	// close file
	inFile.reset();
	
	// generate new file
	outFile.Commit();
}

wxMemoryOutputStream* Library::getEntryData(wxString reference)
{
	// wxZipEntry pointer
	wxZipEntry* entry;
	
	// fileinput
	wxFFileInputStream inFile(m_fileName.GetFullPath());
	
	// zip input
	wxZipInputStream inZip(inFile);
	
	// memoryoutputstream to return
	wxMemoryOutputStream* memOut = new wxMemoryOutputStream;
	
	// get first entry
	entry = inZip.GetNextEntry();
	
	// walk through all entries
	while (entry)
	{
		// check if entry found
		if (entry->GetName() == reference)
		{
			// open entry
			inZip.OpenEntry(*entry);
			
			// copy data into memOut
			inZip.Read(*memOut);
			
			// close entry
			inZip.CloseEntry();
			
			// found
			break;
		}
		
		// get next entry
		entry = inZip.GetNextEntry();
	}
	
	return memOut;
}

void Library::renameCategory(unsigned int cat_id, wxString new_name)
{
	// empty xml document
	wxXmlDocument xml;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// input file to open library
	std::auto_ptr<wxFFileInputStream> inFile(new wxFFileInputStream(m_fileName.GetFullPath()));
	
	// temp output file to store new lib
	wxTempFileOutputStream outFile(m_fileName.GetFullPath());
	
	// zip input stream
	wxZipInputStream inzip(*inFile);
	
	// zip output stream
	wxZipOutputStream outzip(outFile);
	
	// copy meta data
	outzip.CopyArchiveMetaData(inzip);
	
	// get first entry of inzip
	entry = inzip.GetNextEntry();
	
	// copy all entries
	while (entry)
	{
		// copy all entries except the old xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			//open entry
			inzip.OpenEntry(*entry);
			
			// new xml
			xml.Load(inzip);
			
			// close entry
			inzip.CloseEntry();
			
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
			
			// delete entry in xml
			renameXmlCategory(xml, outzip, cat_id, new_name);
		}
		
		// if not available
		if (inzip.Eof())
		{
			break;
		}
		
		// copy entry
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// close outzip
	outzip.Close();
	
	// close file
	inFile.reset();
	
	// generate new file
	outFile.Commit();
}

void Library::renameEntry(wxString reference, wxString newName)
{
	// empty xml document
	wxXmlDocument xml;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// input file to open library
	std::auto_ptr<wxFFileInputStream> inFile(new wxFFileInputStream(m_fileName.GetFullPath()));
	
	// temp output file to store new lib
	wxTempFileOutputStream outFile(m_fileName.GetFullPath());
	
	// zip input stream
	wxZipInputStream inzip(*inFile);
	
	// zip output stream
	wxZipOutputStream outzip(outFile);
	
	// copy meta data
	outzip.CopyArchiveMetaData(inzip);
	
	// get first entry of inzip
	entry = inzip.GetNextEntry();
	
	// copy all entries
	while (entry)
	{
		// copy all entries except the old xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			//open entry
			inzip.OpenEntry(*entry);
			
			// new xml
			xml.Load(inzip);
			
			// close entry
			inzip.CloseEntry();
			
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
			
			// delete entry in xml
			renameXmlEntry(xml, outzip, reference, newName);
		}
		
		// copy entry
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// close outzip
	outzip.Close();
	
	// close file
	inFile.reset();
	
	// generate new file
	outFile.Commit();
}

void Library::addNewCategory(const wxString& newName, const unsigned int parentId)
{
	// empty xml document
	wxXmlDocument xml;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// input file to open library
	std::auto_ptr<wxFFileInputStream> inFile(new wxFFileInputStream(m_fileName.GetFullPath()));
	
	// temp output file to store new lib
	wxTempFileOutputStream outFile(m_fileName.GetFullPath());
	
	// zip input stream
	wxZipInputStream inzip(*inFile);
	
	// zip output stream
	wxZipOutputStream outzip(outFile);
	
	// copy meta data
	outzip.CopyArchiveMetaData(inzip);
	
	// get first entry of inzip
	entry = inzip.GetNextEntry();
	
	// copy all entries
	while (entry)
	{
		// copy all entries except the old xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			//open entry
			inzip.OpenEntry(*entry);
			
			// new xml
			xml.Load(inzip);
			
			// close entry
			inzip.CloseEntry();
			
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
			
			// delete entry in xml
			addNewXmlCategory(xml, outzip, parentId, newName);
		}
		
		// if empty, leave
		if (inzip.Eof())
		{
			break;
		}
		
		// copy entry
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// close outzip
	outzip.Close();
	
	// close file
	inFile.reset();
	
	// generate new file
	outFile.Commit();
}

void Library::moveEntry(const wxString reference, const unsigned int new_parent_id)
{
	// empty xml document
	wxXmlDocument xml;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// input file to open library
	std::auto_ptr<wxFFileInputStream> inFile(new wxFFileInputStream(m_fileName.GetFullPath()));
	
	// temp output file to store new lib
	wxTempFileOutputStream outFile(m_fileName.GetFullPath());
	
	// zip input stream
	wxZipInputStream inzip(*inFile);
	
	// zip output stream
	wxZipOutputStream outzip(outFile);
	
	// copy meta data
	outzip.CopyArchiveMetaData(inzip);
	
	// get first entry of inzip
	entry = inzip.GetNextEntry();
	
	// copy all entries
	while (entry)
	{
		// copy all entries except the old xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			//open entry
			inzip.OpenEntry(*entry);
			
			// new xml
			xml.Load(inzip);
			
			// close entry
			inzip.CloseEntry();
			
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
			
			// delete entry in xml
			moveXmlEntry(xml, outzip, reference, new_parent_id);
		}
		
		// if empty, leave
		if (inzip.Eof())
		{
			break;
		}
		
		// copy entry
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// close outzip
	outzip.Close();
	
	// close file
	inFile.reset();
	
	// generate new file
	outFile.Commit();
}

void Library::moveCategory(const unsigned int catId, const unsigned int newParentId)
{
	// empty xml document
	wxXmlDocument xml;
	
	// pointer to wxZipEntry
	wxZipEntry* entry;
	
	// input file to open library
	std::auto_ptr<wxFFileInputStream> inFile(new wxFFileInputStream(m_fileName.GetFullPath()));
	
	// temp output file to store new lib
	wxTempFileOutputStream outFile(m_fileName.GetFullPath());
	
	// zip input stream
	wxZipInputStream inzip(*inFile);
	
	// zip output stream
	wxZipOutputStream outzip(outFile);
	
	// copy meta data
	outzip.CopyArchiveMetaData(inzip);
	
	// get first entry of inzip
	entry = inzip.GetNextEntry();
	
	// copy all entries
	while (entry)
	{
		// copy all entries except the old xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			//open entry
			inzip.OpenEntry(*entry);
			
			// new xml
			xml.Load(inzip);
			
			// close entry
			inzip.CloseEntry();
			
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
			
			// delete entry in xml
			moveXmlCategory(xml, outzip, catId, newParentId);
		}
		
		// if empty, leave
		if (inzip.Eof())
		{
			break;
		}
		
		// copy entry
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// close outzip
	outzip.Close();
	
	// close file
	inFile.reset();
	
	// generate new file
	outFile.Commit();
	
}

void Library::openLibrary()
{
	// string to store groupname
	wxString Name;
	
	// check if file exist
	if (!wxFileExists(m_fileName.GetFullPath()))
	{
		// create new empty library
		createEmptyLibrary();
	}
	
	// get library.gnr as FileInputStream
	wxFFileInputStream inFile(m_fileName.GetFullPath());
	
	// get File as wxZipInputStream
	wxZipInputStream inZip(inFile);
	
	// m_zipEntry to first entry
	wxZipEntry* zipEntry = inZip.GetNextEntry();
	
	// walk through all entrys and look for an xml file
	while (zipEntry)
	{
		// lookfor *.xml
		if (zipEntry->GetName().Matches(wxT("*.xml")));
		{
			// open entry
			inZip.OpenEntry(*zipEntry);
			
			// load xml
			LoadXml(inZip);
			
			// close entry
			inZip.CloseEntry();
			
			//entry found
			break;
		}
		
		// get next Entry
		zipEntry = inZip.GetNextEntry();
	}
}

void Library::createEmptyLibrary()
{
	// create outputstream
	wxFFileOutputStream outFile(m_fileName.GetFullPath());
	
	// create zipoutputstream
	wxZipOutputStream outZip(outFile);
	
	// create new empty xml document
	wxXmlDocument xml;
	
	// set xml version
	xml.SetVersion(wxT("1.0"));
	
	// set file encoding
	xml.SetFileEncoding(wxT("utf-8"));
	
	// create root
	wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("gnr"));
	
	// set root
	xml.SetRoot(root);
	
	// create entries
	wxXmlNode* node = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxT("entries"));
	
	// create categoreis
	node = new wxXmlNode(root, wxXML_ELEMENT_NODE, wxT("categories"));
	
	// new zipEntry
	outZip.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(outZip);
	
	// close entry
	outZip.CloseEntry();
	
	// close zipStream
	outZip.Close();
	
	// close file
	outFile.Close();
}

void Library::LoadXml(wxInputStream& inStream)
{
	// store name
	wxString name;
	
	// store cat id
	unsigned int catId;
	
	// store parent id
	unsigned int parentId;
	
	// store reference
	wxString reference;
	
	// create xml document of m_inZip
	wxXmlDocument xml(inStream);
	
	// create pointer to node
	wxXmlNode* node;
	
	// create pointer to prop
	wxXmlProperty* prop;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	if (node->GetChildren() != NULL)
	{
		// node to first category
		node = node->GetChildren();
		
		// walk through all categories
		while (node)
		{
			// prop to name
			prop = node->GetProperties();
			
			// get name
			name = prop->GetValue();
			
			// prop to cat id
			prop = prop->GetNext();
			
			// get cat id
			catId = (unsigned int)wxAtoi(prop->GetValue());
			
			// prop to parent id
			prop = prop->GetNext();
			
			// get parent id
			parentId = (unsigned int)wxAtoi(prop->GetValue());
			
			// add category
			addCategory(name, catId, parentId);
			
			// check if next node exist
			if (node->GetNext() != NULL)
			{
				// everything ok, next exist
				node = node->GetNext();
			}
			// no next node
			else
			{
				// no next node, jump out
				break;
			}
		}
		
		// set node to categories
		node = node->GetParent();
		
		// set node to entries
		node = node->GetNext();
		
		if (node->GetChildren() != NULL)
		{
			// node to first entry
			node = node->GetChildren();
			
			// walk through all entries
			while (node)
			{
				// prop to name
				prop = node->GetProperties();
				
				// get name
				name = prop->GetValue();
				
				// prop to reference
				prop = prop->GetNext();
				
				// get reference
				reference = prop->GetValue();
				
				// prop to categoryid
				prop = prop->GetNext();
				
				// get categoryid
				catId = (unsigned int)wxAtoi(prop->GetValue());
				
				// add new entry
				addEntry(name, reference, catId);
				
				// check if next node exist
				if (node->GetNext() != NULL)
				{
					// everything ok, next exist
					node = node->GetNext();
				}
				// no next node
				else
				{
					// no next node, jump out
					break;
				}
			}
		}
	}
}

void Library::addCategory(wxString& name, unsigned int& categoryId, unsigned int& parentId)
{
	m_ptrCategories->push_back(LibraryCategory(name, categoryId, parentId));
	m_categoryId = categoryId;
}

void Library::addEntry(wxString& name, wxString& reference, unsigned int& categoryId)
{
	m_ptrEntries->push_back(LibraryEntry(name, reference, categoryId));
}

void Library::addXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, wxString& newName)
{
	// node pointer
	wxXmlNode* node;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// new node
	wxXmlNode* newChild = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("category"));
	
	// add name to new category
	newChild->AddProperty(wxT("name"), newName);
	
	// add categoryId
	newChild->AddProperty(wxT("categoryId"), wxString() << m_categoryId);
	
	// add parentId
	newChild->AddProperty(wxT("parentId"), wxString() << m_parentId);
	
	// add new category
	node->AddChild(newChild);
	
	// new zipEntry
	out.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(out);
	
	// close entry
	out.CloseEntry();
}

void Library::addXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out)
{
	// node pointer
	wxXmlNode* node;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// node to entries
	node = node->GetNext();
	
	// new node
	wxXmlNode* newChild = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("entry"));
	
	// add attributes
	// add name
	newChild->AddProperty(wxT("name"), m_ptrEntries->back().getName());
	
	// add reference
	newChild->AddProperty(wxT("reference"), m_ptrEntries->back().getReference());
	
	// add cat id
	newChild->AddProperty(wxT("categoryId"), wxString() << m_ptrEntries->back().getCategoryId());
	
	// add child
	node->AddChild(newChild);
	
	// new zipEntry
	out.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(out);
	
	// close entry
	out.CloseEntry();
}

void Library::deleteXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference)
{
	// node pointer
	wxXmlNode* node = NULL;
	
	// node pointer
	wxXmlNode* delNode = NULL;
	
	// property pointer
	wxXmlProperty* prop;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// node to entries
	node = node->GetNext();
	
	// node to first entry
	node = node->GetChildren();
	
	// walk through all children
	while (node)
	{
		// prop to name
		prop = node->GetProperties();
		
		// prop to ref
		prop = prop->GetNext();
		
		// check if found
		if (prop->GetValue() == reference)
		{
			// set delNode to node
			delNode = node;
			
			// found
			break;
		}
		
		// check if next node exist
		if (node->GetNext() != NULL)
		{
			// everything ok, next exist
			node = node->GetNext();
		}
		// no next node
		else
		{
			// no next node, jump out
			break;
		}
	}
	
	// node to parent
	node = node->GetParent();
	
	// delete childen of node
	node->RemoveChild(delNode);
	
	// new zipEntry
	out.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(out);
	
	// close entry
	out.CloseEntry();
	
	// delete old node
	delete delNode;
}

void Library::renameXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, unsigned int cat_id, wxString& newName)
{
	// node pointer
	wxXmlNode* node;
	
	// property pointer
	wxXmlProperty* prop;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// node to first category
	node = node->GetChildren();
	
	// walk through all children
	while (node)
	{
		// prop to name
		prop = node->GetProperties();
		
		// prop to cat id
		prop = prop->GetNext();
		
		// look if proper cat
		if ((unsigned int)wxAtoi(prop->GetValue()) == cat_id)
		{
			// prop to name
			prop = node->GetProperties();
			
			// set new name
			prop->SetValue(newName);
		}
		
		// another children
		if (node->GetNext() != NULL)
		{
			// node to next
			node = node->GetNext();
		}
		// no children anymore
		else
		{
			// leave loop
			break;
		}
	}
	
	// new zipEntry
	out.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(out);
	
	// close entry
	out.CloseEntry();
}

void Library::renameXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, wxString& reference, wxString& newName)
{
	// node pointer
	wxXmlNode* node;
	
	// property pointer
	wxXmlProperty* prop;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// node to entries
	node = node->GetNext();
	
	// node to first entry
	node = node->GetChildren();
	
	while (node)
	{
		// prop to name
		prop = node->GetProperties();
		
		// prop to ref
		prop = prop->GetNext();
		
		// check if proper entry
		if (prop->GetValue() == reference)
		{
			// prop to name
			prop = node->GetProperties();
			
			// set name
			prop->SetValue(newName);
		}
		
		// check if next exist
		if (node->GetNext() != NULL)
		{
			// get next
			node = node->GetNext();
		}
		else
		{
			break;
		}
	}
	
	// new zipEntry
	out.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(out);
	
	// close entry
	out.CloseEntry();
}

void Library::addNewXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, const unsigned int parentId, const wxString& newName)
{
	// node pointer
	wxXmlNode* node;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// new node
	wxXmlNode* newChild = new wxXmlNode(wxXML_ELEMENT_NODE, wxT("category"));
	
	// add name
	newChild->AddProperty(wxT("name"), newName);
	
	// add category id
	newChild->AddProperty(wxT("categoryId"), wxString() << m_categoryId);
	
	// add parent id
	newChild->AddProperty(wxT("parentId"), wxString() << parentId);
	
	// add new child
	node->AddChild(newChild);
	
	// new zipEntry
	out.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(out);
	
	// close entry
	out.CloseEntry();
}

void Library::moveXmlEntry(wxXmlDocument& xml, wxZipOutputStream& out, const wxString& reference, const unsigned int new_parent_id)
{
	// node pointer
	wxXmlNode* node;
	
	// property pointer
	wxXmlProperty* prop;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// node to entries
	node = node->GetNext();
	
	// node to first entry
	node = node->GetChildren();
	
	while (node)
	{
		// prop to name
		prop = node->GetProperties();
		
		// prop to ref
		prop = prop->GetNext();
		
		// check if proper entry
		if (prop->GetValue() == reference)
		{
			// prop to name
			prop = node->GetProperties();
			
			// prop to reference
			prop = prop->GetNext();
			
			// prop to cat id
			prop = prop->GetNext();
			
			// set new cat id
			prop->SetValue(wxString() << new_parent_id);
		}
		
		// check if there are children
		if (node->GetNext() != NULL)
		{
			// set to next children
			node = node->GetNext();
		}
		else
		{
			break;
		}
	}
	
	// new zipEntry
	out.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(out);
	
	// close entry
	out.CloseEntry();
}

void Library::moveXmlCategory(wxXmlDocument& xml, wxZipOutputStream& out, const unsigned int catId, const unsigned int new_parent_id)
{
	// node pointer
	wxXmlNode* node;
	
	// node pointer
	wxXmlNode* storeNode;
	
	// property pointer
	wxXmlProperty* prop;
	
	// node to root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// node to first category
	node = node->GetChildren();
	
	// walk through all categories
	while (node)
	{
		// prop to name
		prop = node->GetProperties();
		
		// prop to catId
		prop = prop->GetNext();
		
		// check if proper property
		if ((unsigned int)wxAtoi(prop->GetValue()) == catId)
		{
			// store node to delete
			storeNode = node;
			
			// node to parent
			node = node->GetParent();
			
			// delete node
			node->RemoveChild(storeNode);
			
			// found
			break;
		}
		
		// check if there are children
		if (node->GetNext() != NULL)
		{
			// set to next children
			node = node->GetNext();
		}
		else
		{
			break;
		}
	}
	
	// get root
	node = xml.GetRoot();
	
	// node to categories
	node = node->GetChildren();
	
	// prop to name of storeNode
	prop = storeNode->GetProperties();
	
	// prop to cat id
	prop = prop->GetNext();
	
	// prop to parent id
	prop = prop->GetNext();
	
	// set new parent id
	prop->SetValue(wxString() << new_parent_id);
	
	// add child
	node->AddChild(storeNode);
	
	// new zipEntry
	out.PutNextEntry(wxT("library.xml"));
	
	// copy data into entry
	xml.Save(out);
	
	// close entry
	out.CloseEntry();
}
