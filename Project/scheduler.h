#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <string>
#include "processor.h"



class scheduler
{
private:
	Processor** prolist;
	LinkedQueue<process* > newlist;
	LinkedQueue<process* >blklist;
	LinkedQueue<process* >termlist;
	LinkedQueue <int> killerlist;
	float M;
	int RRT,RTF, MaxW, STL, Forkprob, Time;
	int migRTF, migMaxW, forkedcnt, killedcnt ,stolencnt, totIO_D;
	int NF, NJ, NR, NP; //processors number added
public:
	scheduler();
	int getTotTRT();
	void readIn(const std::string& filename, int& nf, int& ns, int& nr, int& rrt, int& rtf, int& maxw, int& stl, int& fork, float& m); //processors number added
	void sim();
	void killSig();
	void terminate(process* p);
	void migrate();
	void BlkToRdy();
	void RuntoBlk(process* p);
	void insertToShortest(process* p, bool forked);
	void steal();
	Processor* findShortest(bool forked);
	Processor* findLongest();
	void fork(Processor*);
	void NewToRdy();
	void outputFile(const string& filename);
	void killchild(int id);
	~scheduler();
};
#endif


