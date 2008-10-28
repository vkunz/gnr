/**
 * GNRVNT
 * @name        GNRVNT.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef __GNRVNT_H__
#define __GNRVNT_H__

#include "GNRVertex.h"
#include "GNRTCoord.h"

class GNRVNT
{
public:
	GNRVNT(GNRVertex* v, GNRVertex* n, GNRTCoord* t);
	GNRVNT(const GNRVNT& other);
	
	~GNRVNT();
	
	const GNRVertex* getV() const;
	const GNRVertex* getN() const;
	const GNRTCoord* getT() const;
	
	void setV(GNRVertex* v);
	void setN(GNRVertex* n);
	void setT(GNRVertex* t);
	
	void draw() const;
	
private:
	GNRVertex* m_v, *m_n;
	GNRTCoord* m_t;
};

#endif
