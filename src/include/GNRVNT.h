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

	void draw() const;

private:
	GNRVertex* m_v, *m_n;
	GNRTCoord* m_t;
};

#endif
