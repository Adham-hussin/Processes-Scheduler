#include "RR.h"


RR::RR(scheduler* manager, int rrt) : Processor(manager)
{
	timeSlice = rrt;
}





void RR::terminate(bool &b, int pid)//further implementation for forking will be added
{
	if (running->getRemTime() == 0)
	{
		Manager->terminate(running);
		busy = false;
		running = nullptr;
	}
}

void RR::ScheduleAlgo()
{
	if (busy)
	{
		if (running->isIOTime())
		{
			Manager->RuntoBlk(running);
			busy = false;
			running = nullptr;
		}
		else if (running->getRemTime() == 0)
		{
			bool found = false;
			terminate(found, 0);
		}
		else if (running->timeSliceDone(timeSlice))
		{
			Manager->insertToShortest(running, 0); //is this 0 right ??
			busy = false;
			running = nullptr;
		}
		else
		{
			running->decreaseRemTime();
		}
	}
	else if (!busy && RdyList.getLength())
	{
		running = RdyList.peekFront();
		RdyList.dequeue();
		sumCT -= running->getRemTime();
		busy = true;
	}
}

void RR::migRotation()
{
	running = nullptr;
	if (RdyList.getLength())
	{
		running = RdyList.peekFront();
		RdyList.dequeue();
		sumCT -= running->getRemTime();
		busy = true;
	}
}




//process* RR::getmigrated(int rtf)                       to be done
//{
//	if (RdyList.peekFront()->getRemTime() < rtf)
//	{
//		process* tmp = RdyList.peekFront();
//		RdyList.dequeue();
//		return tmp;
//	}
//}

process* RR::stealtop()
{
	process* tmp = nullptr;
	if (RdyList.getLength())
	{
		tmp = RdyList.peekFront();
		RdyList.dequeue();
		sumCT -= tmp->getRemTime();
	}
	return tmp;
}


void RR::insertProcess(process* p)
{
	RdyList.enqueue(p);
	sumCT += p->getRemTime();
}

void RR::print()
{
	RdyList.print();
}

int RR::getNumOfProcesses()
{
	return RdyList.getLength();
}

RR::~RR(void)
{
}
