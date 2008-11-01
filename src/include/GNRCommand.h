/**
 * this header defines an interface, every class that handels an undo/redo-command has to implement
 * @name        GNRCommand.h
 * @date        2008-10-29
 * @author		Konstantin Balabin  <k.balabin@googlemail.com>
 * @author		Patrick Kracht      <patrick.kracht@googlemail.com>
 * @author		Thorsten Moll       <thorsten.moll@googlemail.com>
 * @author		Valentin Kunz       <athostr@googlemail.com>
 */

#ifndef _GNRCOMMAND_H_
#define _GNRCOMMAND_H_

class GNRCommand
{
public:
	virtual void execute() = 0;
	virtual void unexecute() = 0;
};

#endif // _GNRCOMMAND_H_
