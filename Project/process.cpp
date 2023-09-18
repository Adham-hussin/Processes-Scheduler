
#include "process.h"
#include "scheduler.h"


process :: process(int a, int id , int c, int cnt)
{
	AT = a;
	PID = id;
	CT = c;
	total_io = cnt;
	remTimeCount = c; //added
	lastTimeSlice = c;
	WT = 0;
	rchild = nullptr;
	lchild = nullptr;
	blktime = 0;
	firstTime = true;
	forked = false;// added
}

void process::insertio(int a)
{
	io_pairs.enqueue(a);
}


process* process::fork(int a, int id, int c, int rorl)//
{
	if (rorl == 0)
	{
		lchild = new process(a, id, c, 0);
		lchild->setForked(true);
	}
	else if (rorl == 1)
	{
		rchild = new process(a, id, c, 0);
		rchild->setForked(true);
	}
	forkedcnt++;
	return (rorl == 0 ? lchild : rchild);
}

int process::getAT()
{
	return AT;
}

int process::getPID() //added
{
	return PID;
}

int process::getCT()
{
	return CT;
}

int process::getRemTime() //added
{
	return remTimeCount;
}

void process::setTT(int a)
{
	TT = a;
}

void process::setWT(int a)
{
	WT = a;
}

void process::setTRT(int a)
{
	TRT = a;
}

void process::setForked(bool a)
{
	forked = a;
}

void process::resetBlkTime()
{
	blktime = 0;
}

void process::updateBlkTime()
{
	blktime--;
}

int process::getCurrIO_D()
{
	return currIO_D;
}

int process::getTotIO_D()
{
	return totIO_D;
}

int process::getBlkTime()
{
	return blktime;
}

bool process::isForked()
{
	return forked;
}

void process::decreaseRemTime()//to be thought about
{
	remTimeCount--;
}

int process::getWT()
{
	return WT;
}

int process::isFirstTime()
{
	return firstTime;
}

void process::setFirstTime()
{
	firstTime = false;
}

int process::getTT()
{
	return TT;
}

int process::getTRT()
{
	return TRT;
}

int process::getRT()
{
	return RT;
}





//process* process::killOrphans(process* parent)
//{
//	if (parent == nullptr) return;
//	process* tmp = killOrphans(parent->getchild());
//	
//}

bool process::isIOTime()
{

	if (io_pairs.getLength() && CT - remTimeCount == io_pairs.peekFront())
	{
		io_pairs.dequeue();
		currIO_D = io_pairs.peekFront();
		blktime = currIO_D;
		totIO_D += currIO_D;
		io_pairs.dequeue();
		//second dequeue for adham
		return true;
	}
	return false;
}
bool process::timeSliceDone(int rrt)
{
	if (lastTimeSlice - remTimeCount == rrt)
	{
		lastTimeSlice = remTimeCount;
		return true;
	}
	return false;
}

process* process::getrchild()
{
	return rchild;
}

process* process::getlchild()
{
	return lchild;
}

int process::getForkedCnt()
{
	return forkedcnt;
}

void process::setForkedCnt()
{
	forkedcnt++;
}

bool process::operator>(process &p)
{
	return CT >= p.CT;
}

process::~process()
{
	while (!io_pairs.isEmpty())
		io_pairs.dequeue();
}

void process::setRT(int a)
{
	RT = a;
}
