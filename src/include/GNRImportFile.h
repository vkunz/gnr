/**
 * GNRImportFile
 * @name        GNRImportFile.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRAssembly.h"

class GNRImportFile
{
public:
	GNRImportFile();
	virtual ~GNRImportFile();
	
	virtual GNRAssembly* read(const string& fname) = 0;
};
