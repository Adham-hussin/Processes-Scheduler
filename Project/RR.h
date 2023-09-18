#ifndef RR_H
#define RR_H
#include "processor.h"
#include"process.h"
#include"scheduler.h"

class RR :
	public Processor
{
private:
	int timeSlice;
	LinkedQueue<process*> RdyList;
public:
	RR(scheduler*, int rrt);
	virtual void terminate(bool &b, int pid = 0);
	virtual void insertProcess(process * p);
	virtual void print();
	//virtual process* getmigrated(int rtf);              to be done
	virtual int getNumOfProcesses();
	virtual void ScheduleAlgo();
	void migRotation();
	virtual process* stealtop();

	~RR(void);
};
#endif
