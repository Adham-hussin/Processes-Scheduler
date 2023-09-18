#ifndef PROCESS_H
#define PROCESS_H
#include "list.h"
#include "queue.h"
#include "pqueue.h"
enum state {
	NEW, 
	RDY, 
	RUN, 
	BLK, 
	TRM,
	ORPH  
};


class process
{
private:
	state s;
	int PID;
	int AT;
	int RT;
	int CT;
	int TT;
	int TRT;
	int WT;
	bool firstTime;
	int remTimeCount; //added, starts from CT and goes down to zero
	int lastTimeSlice;
	LinkedQueue <int> io_pairs;
	int total_io;
	process* rchild;
	process* lchild;
	bool forked;
	int forkedcnt;
	int blktime;
	int currIO_D;
	int totIO_D;

public:
	process(int a, int p, int c, int cnt);
	void insertio(int a);
	process* fork(int a, int p, int c, int d);
	int getAT();
	int getPID();
	int getCT();
	int getRemTime();
	void decreaseRemTime();
	~process();
	void setRT(int a);
	void setWT(int a);
	void setTT(int a);
	int getCurrIO_D();
	int getTotIO_D();
	void setTRT(int a);
	void setForked(bool);
	void resetBlkTime();
	void updateBlkTime();
	int getBlkTime();
	bool isForked();
	int getWT();
	int isFirstTime();
	void setFirstTime();
	int getTT();
	int getTRT();
	int getRT();
	//process* killOrphans(process* parent);
	bool isIOTime();
	bool timeSliceDone(int rrt);
	process* getrchild();
	process* getlchild();
	int getForkedCnt();
	void setForkedCnt();
	friend ostream& operator<<(ostream& cout, const process& p);
	bool operator> (process &p);
};
#endif
