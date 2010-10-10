/**
 * defines the CommandTransform-class
 * @name        CommandTransform.h
 * @date        2008-10-29
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _COMMANDTRANSFORM_H_
#define _COMMANDTRANSFORM_H_

#include "Command.h"

class Assembly;
class Vertex;

class CommandTransform: public Command
{
public:
	CommandTransform();
	virtual ~CommandTransform();
	void execute();
	void unexecute();
	void setAssembly(Assembly* assembly);
	void setOldPosition(Vertex& old_pos);
	void setOldAngles(Vertex& old_angles);
	void setNewPosition(Vertex& new_pos);
	void setNewAngles(Vertex& new_angles);

protected:
private:
	Assembly* m_usedAssembly;
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

#endif // _COMMANDTRANSFORM_H_
