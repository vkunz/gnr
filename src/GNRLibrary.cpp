
#include <wx/sstream.h>
#include <wx/wfstream.h>
#include <wx/xml/xml.h>
#include <wx/zipstrm.h>

#if defined(__ATHOS_DEBUG__)
#include <wx/log.h>
#endif

#include "GNRLibrary.h"
#include "md5.h"

// ctor
GNRLibrary::GNRLibrary()
{
	// set filename to standard lib
	m_fileName = (wxFileName::GetCwd() + wxFileName::GetPathSeparator() + wxT("data") + wxFileName::GetPathSeparator() + wxT("library.gnr"));
	
	// new categories vector
	m_ptrCategories = new std::vector<GNRLibraryCategory>;
	
	// new entries vector
	m_ptrEntries = new std::vector<GNRLibraryEntry>;
	
	// open library
	openLibrary();
}

GNRLibrary::GNRLibrary(wxString filename)
{
	// set library to file
	m_fileName.Assign(filename);
	
	// open library
	openLibrary();
}

// dtor
GNRLibrary::~GNRLibrary()
{
}

std::vector<GNRLibraryCategory>* GNRLibrary::getCategories()
{
	return m_ptrCategories;
}

std::vector<GNRLibraryEntry>* GNRLibrary::getEntries()
{
	return m_ptrEntries;
}

void GNRLibrary::addEntry(wxInputStream& inStream)
{
	// strings to store md5-hash
	wxString objHash;
	wxString xmlHash;
	
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
			// do not copy entry, set next entry
			entry = inzip.GetNextEntry();
		}
		
		// copy all entries
		outzip.CopyEntry(entry, inzip);
		
		// get next entry
		entry = inzip.GetNextEntry();
	}
	
	// make zip of inputStream
	wxZipInputStream inZip(inStream);
	
	// entry to first inZip entry
	entry = inZip.GetNextEntry();
	
	// walk through all entrys and push them into vector
	while (entry)
	{
		// check if .xml
		if (entry->GetName().Matches(wxT("*.xml")))
		{
			// make string of inputstream
			wxStringOutputStream strout(&xmlHash);
			
			// open zip stream
			inZip.OpenEntry(*entry);
			
			// read and write to strout
			inZip.Read(strout);
			
#if defined(__ATHOS_DEBUG__)
			wxLogDebug(xmlHash);
#endif
			// close zip entry
			inZip.CloseEntry();
			
			// get hash
			xmlHash = MD5wxString(xmlHash);
		}
		
		if (entry->GetName().Matches(wxT("*.obj")))
		{
			// make string of inputstream
			wxStringOutputStream strout(&objHash);
			
			// open zip entry
			inZip.OpenEntry(*entry);
			
			// read and write to strout
			inZip.Read(strout);
			
			// close zip entry
			inZip.CloseEntry();
			
			// get hash
			objHash = MD5wxString(objHash);
		}
		
		// get next Entry
		entry = inZip.GetNextEntry();
	}
	
	// reset stream position to read again
	inStream.SeekI(0);
	
	// new entry
	outzip.PutNextEntry(objHash + xmlHash + wxT(".oax"));
	
	// copy d ata
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

unsigned int GNRLibrary::getParentId(wxString name)
{
	// tmp int
	unsigned int parentId;
	
	// iterator
	std::vector<GNRLibraryCategory>::iterator it;
	
	// walk through all entrys, look for name
	for (it = m_ptrCategories->begin(); it != m_ptrCategories->end(); it++)
	{
		if (it->getName() == name)
		{
			parentId = it->getParentId();
		}
	}
	
	return parentId;
}

void GNRLibrary::openLibrary()
{
	// string to store groupname
	wxString Name;
	
	// integer to store groupId
	unsigned int groupId;
	
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

void GNRLibrary::createEmptyLibrary()
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

void GNRLibrary::LoadXml(wxInputStream& inStream)
{
	// store name
	wxString name;
	
	// store reference
	wxString reference;
	
	// store id
	unsigned int categoryId;
	
	// open m_zipEntry
	//m_inZip->OpenEntry(*m_zipEntry);
	
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
						
						// get value
						name = prop->GetValue();
						
						// get parentId
						m_parentId = getParentId(name);
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
				
				// get value
				name = prop->GetValue();
				
				// get parentId
				m_parentId = getParentId(name);
				
				// set node to next
				node = node->GetNext();
			}
		}
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

void GNRLibrary::addCategory(wxString& name, unsigned int& categoryId, unsigned int& parentId)
{
	m_ptrCategories->push_back(GNRLibraryCategory(name, categoryId, parentId));
}

void GNRLibrary::addEntry(wxString& name, wxString& reference, unsigned int& categoryId)
{
	m_ptrEntries->push_back(GNRLibraryEntry(name, reference, categoryId));
}