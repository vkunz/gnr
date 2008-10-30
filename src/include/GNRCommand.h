#ifndef _GNRCOMMAND_H_
#define _GNRCOMMAND_H_

class GNRCommand
{
public:
	virtual void execute() = 0;
	virtual void unexecute() = 0;
};

#endif // _GNRCOMMAND_H_
