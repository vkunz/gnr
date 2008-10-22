/* vim: set expandtab sw=4 ts=4 sts=4: */
/**
 * GNRMaterialImport
 * @name        GNRMaterialImport.cpp
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#include "GNRMaterialImport.h"
#include "GNRMaterial.h"

#include <sstream>

using std::pair;
using std::stringstream;

#include <iostream>

using std::cout; using std::endl;



GNRMatLib* GNRMaterialImport::read(const string& fname)
{
    m_root = new GNRMatLib;
    m_matname = "default";

    m_ifs.open(fname.c_str());
    m_buf.clear();
    while (m_ifs.good())
    {
        m_material = new GNRMaterial;
        if (getName())
        {
            while (getData() && m_ifs.good());
        }
        m_root->insert(pair<string, GNRMaterial>(m_matname, *m_material));
        delete m_material;
    }
    m_ifs.close();
    cout << "Got " << m_root->size() << " colors" << endl;

    return m_root;
}

bool GNRMaterialImport::getName()
{
    bool found = m_buf.substr(0, 7) == "newmtl ";
    while (m_ifs.good() && !found)
    {
        getline(m_ifs, m_buf);
        found = m_buf.substr(0, 7) == "newmtl ";
    }
    if (found)
        m_matname = m_buf.substr(7, string::npos);
    return found;
}

bool GNRMaterialImport::getData()
{
    bool gotData = true;
    m_buf.clear();
    if (m_ifs.good())
    {
        getline(m_ifs, m_buf);
        gotData = m_buf.substr(0, 7) != "newmtl ";
    }
    if (gotData)
        parseData();
    return gotData;
}

void GNRMaterialImport::parseData()
{
    if (m_buf.size() < 2)
        return;

    float r = 0, g = 0, b = 0, a = 0, s = 0;
    stringstream ss(m_buf.substr(2, string::npos));

    switch (m_buf[0])
    {
    case 'K':
            ss >> r >> g >> b;
            switch (m_buf[1])
            {
            case 'a':
                m_material->setAmbient(r, g, b);
                break;
            case 'd':
                m_material->setDiffuse(r, g, b);
                break;
            case 's':
                m_material->setSpecular(r, g, b);
            default:
                break;
            }
    case 'd':
            ss >> a;
            m_material->setAlpha(a);
            break;
    case 'N':
            ss >> s;
            m_material->setShininess(s);
            break;
    default:
            break;
    }
}
