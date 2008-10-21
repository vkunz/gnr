/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRImportFile
 * @name        GNRImportFile.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRIMPORTFILE_H_
#define _GNRIMPORTFILE_H_

#include "GNRAssembly.h"
#include "GNRVertex.h"
#include "GNRFace.h"

class GNRImportFile
{
public:
	virtual GNRAssembly* read(const string& fname) = 0;
};

#endif // _GNRIMPORTFILE_H_
