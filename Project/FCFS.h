#ifndef FCFS_H
#define FCFS_H
#include "processor.h"
#include"process.h"
#include"scheduler.h"
#include "specialList.h"
class FCFS :
	public Processor
{
private:
	LinkedProcess RdyList;
public:
	FCFS(scheduler* manager);
	virtual void insertProcess(process * p);
	virtual void terminate(bool &found, int pid = 0);
	virtual void print();
	void updateWT();
	//virtual process* getmigrated(int maxw);
	virtual int getNumOfProcesses();
	virtual void ScheduleAlgo();
	process* killOrphans(process* parent);
	~FCFS(void);
	virtual process* stealtop();
	void migRotation();
};
#endif

