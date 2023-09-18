#ifndef SJF_H
#define SJF_H
#include "processor.h"
#include "scheduler.h"
class SJF :
	public Processor
{
private:
	PriorityQueue<process*> RdyList;//it is priority but i changed it for now
public:
	SJF(scheduler*);
	virtual void insertProcess(process* p);
	virtual void terminate(bool &b, int pid = 0);
	virtual void print();
	virtual int getNumOfProcesses();
	virtual void ScheduleAlgo();
	virtual void migRotation();
	virtual process* stealtop();
	~SJF(void);
};
#endif
