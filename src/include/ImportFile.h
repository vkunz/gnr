/**
 * ImportFile
 * @name        ImportFile.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include <string>

class Assembly;

class ImportFile
{
public:
	ImportFile();
	virtual ~ImportFile();

	Assembly* read(const std::string& fname);
};
