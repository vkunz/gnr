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
	m_fileName = (wxFileName::GetCwd() + wxFileName::GetPathSeparator() + wxT("library.gnr"));
	
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
		
		// if there are more than xml, copy
		if (inzip.GetTotalEntries() > 1)
		{
			// copy all entries
			outzip.CopyEntry(entry, inzip);
		}
		
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
		if (!entry->GetName() == reference)
		{
			// copy entry
			outzip.CopyEntry(entry, inzip);
			
			// get next entry
			entry = inzip.GetNextEntry();
		}
		
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

unsigned int Library::getParentId(unsigned int cat_id)
{
	// tmp int
	unsigned int parentId = 0;
	
	// iterator
	std::vector<LibraryCategory>::iterator it;
	
	// walk through all entrys, look for name
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		if (it->getCatId() == cat_id)
		{
			parentId = it->getParentId();
		}
	}
	
	return parentId;
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
	// store cat id
	unsigned int cat_id;
	
	// store name
	wxString name;
	
	// store reference
	wxString reference;
	
	// store id
	unsigned int categoryId = 1;
	
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
		
		// set parentId to 0
		m_parentId = 0;
		
		// walk through all next nodes
		while (node)
		{
			// walk through all children
			while (node)
			{
				// prop to name
				prop = node->GetProperties();
				
				// get value of name
				name = prop->GetValue();
				
				// prop to categoryid
				prop = prop->GetNext();
				
				// get value of categoryId
				categoryId = wxAtoi(prop->GetValue());
				
				// add new category
				addCategory(name, categoryId, m_parentId);
				
				// check if there are children
				if (node->GetChildren() != NULL)
				{
					// set new parentId
					m_parentId = categoryId;
					
					// set to next children
					node = node->GetChildren();
				}
				
				// another children
				else if (node->GetNext() != NULL)
				{
					// node to next
					node = node->GetNext();
				}
				// no children anymore
				else
				{
					// set node to parent
					node = node->GetParent();
					
					// check if categories
					if (node->GetProperties())
					{
						// get first property
						prop = node->GetProperties();
						
						// get next
						prop = prop->GetNext();
						
						// get cat id
						cat_id = wxAtoi(prop->GetValue());
						
						// get parentId
						m_parentId = getParentId(cat_id);
					}
					// if not possible, parent => 0
					else
					{
						m_parentId = 0;
					}
					
					// leave loop
					break;
				}
			}
			
			// check if next exist
			if (node->GetNext() != NULL)
			{
				// exist, set node to next
				node = node->GetNext();
				
				// check if finisched with categories
				if (node->GetName() == wxT("entries"))
				{
					// leave loop
					break;
				}
			}
			// next does not exist
			else
			{
				// set node to parent
				node = node->GetParent();
				
				// get first property
				prop = node->GetProperties();
				
				// prop to cat id
				prop = prop->GetNext();
				
				// get parentId
				m_parentId = getParentId(wxAtoi(prop->GetValue()));
				
				// set node to next
				node = node->GetNext();
			}
		}
	}
	else
	{
		// set node to entries
		node = node->GetNext();
	}
	
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
		categoryId = wxAtoi(prop->GetValue());
		
		// add new entry
		addEntry(name, reference, categoryId);
		
		// check if next node exist
		if (node->GetNext())
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
	newChild->AddProperty(wxT("name"), m_ptrEntries->back().getName());
	newChild->AddProperty(wxT("reference"), m_ptrEntries->back().getReference());
	wxString tmp;
	tmp << m_ptrEntries->back().getCategoryId();
	newChild->AddProperty(wxT("categoryId"), tmp);
	
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
	
	// walk through all next nodes
	while (node)
	{
		// walk through all children
		while (node)
		{
			// prop to name
			prop = node->GetProperties();
			
			// prop to cat id
			prop = prop->GetNext();
			
			// look if proper cat
			if (wxAtoi(prop->GetValue()) == cat_id)
			{
				prop = node->GetProperties();
				
				// set new name
				prop->SetValue(newName);
			}
			
			// check if there are children
			if (node->GetChildren() != NULL)
			{
				// set to next children
				node = node->GetChildren();
			}
			
			// another children
			else if (node->GetNext() != NULL)
			{
				// node to next
				node = node->GetNext();
			}
			// no children anymore
			else
			{
				// set node to parent
				node = node->GetParent();
				
				// leave loop
				break;
			}
		}
		
		// check if next exist
		if (node->GetNext() != NULL)
		{
			// exist, set node to next
			node = node->GetNext();
			
			// check if finisched with categories
			if (node->GetName() == wxT("entries"))
			{
				// leave loop
				break;
			}
		}
		// next does not exist
		else
		{
			// set node to parent
			node = node->GetParent();
			
			// set node to next
			node = node->GetNext();
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
			// prop toname
			prop = node->GetProperties();
			
			// set name
			prop->SetValue(newName);
		}
		
		// check if there are children
		if (node->GetChildren() != NULL)
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
