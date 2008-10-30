#ifndef _GNRCOMMANDASSEMBLY_H
#define _GNRCOMMANDASSEMBLY_H

#include "GNRCommand.h"
#include "GNRAssembly.h"
#include "GNRVertex.h"


class GNRCommandAssembly: public GNRCommand
{
public:
	GNRCommandAssembly();
	virtual ~GNRCommandAssembly();
	void execute();
	void unexecute();
	void setAssembly(GNRAssembly* assembly);
	void setOldPosition(GNRVertex& old_pos);
	void setOldAngles(GNRVertex& old_angles);
	void setNewPosition(GNRVertex& new_pos);
	void setNewAngles(GNRVertex& new_angles);
	
protected:
private:
	GNRAssembly* m_usedAssembly;
	float old_x;
	float old_y;
	float old_z;
	float old_phi;
	float old_theta;
	float old_rho;
	
	float new_x;
	float new_y;
	float new_z;
	float new_phi;
	float new_theta;
	float new_rho;
};

#endif // _GNRCOMMANDASSEMBLY_H
