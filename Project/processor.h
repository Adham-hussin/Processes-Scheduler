#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "process.h"

class scheduler;

class Processor
{
protected: //must be protected so that the children can use those members
	bool busy;
	int sumCT;
	int busyTime;
	int idleTime;
	//static int termCount; count is gotten from the ADT (Aprroved by TA)
	process * running;
	scheduler* Manager; //a pointer to the sceduler is a must as the scheduler only can access termination list
public:
	Processor(scheduler* Sched);

	

	virtual void insertProcess (process* p) = 0;
	virtual void terminate(bool &b, int pid = 0) = 0; //added
	virtual void ScheduleAlgo() = 0;

	bool isbusy();
	void makebusy(bool b);
	void UpdateBusyIdleTime();
	int getSumCT();
	void setSumCT(int a);
	int getBusyTime();
	int getIdleTime();
	virtual int getNumOfProcesses() = 0;
	//virtual process* getmigrated(int x);
	virtual void migRotation();
	process * getRunning();
	virtual void print() = 0;
	virtual ~Processor(void);
	virtual process* stealtop() = 0;
};





#endif
