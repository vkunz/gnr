/**
 * VNT
 * @name        VNT.h
 * @date        2008-10-05
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef __GNRVNT_H__
#define __GNRVNT_H__

#include "Vertex.h"
#include "TCoord.h"

class VNT
{
public:
	VNT(Vertex* v, Vertex* n, TCoord* t);
	VNT(const VNT& other);
	
	~VNT();
	
	const Vertex* getV() const;
	const Vertex* getN() const;
	const TCoord* getT() const;
	
	void setV(Vertex* v);
	void setN(Vertex* n);
	void setT(TCoord* t);
	
	void draw() const;
	
private:
	Vertex* m_v, *m_n;
	TCoord* m_t;
};

#endif
