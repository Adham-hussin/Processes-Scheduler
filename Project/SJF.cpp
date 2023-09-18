#include "SJF.h"


SJF::SJF(scheduler* manager) : Processor(manager)
{
}



void SJF::terminate(bool &b, int pid)//further implementation for forking will be added
{
	if (running->getRemTime() == 0)
	{
		Manager->terminate(running);
		busy = false;
		running = nullptr;
	}
}

void SJF::ScheduleAlgo()
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
		else
		{
			running->decreaseRemTime();
		}
	}
	else if (!busy && RdyList.GetSize())
	{
		running = RdyList.PeekFront();
		RdyList.Dequeue();
		sumCT -= running->getRemTime();
		busy = true;
	}
}

void SJF::migRotation()//ready to run
{

}


process* SJF::stealtop()
{
	process* tmp = nullptr;
	if (RdyList.GetSize())
	{
		tmp = RdyList.PeekFront();
		RdyList.Dequeue();
		sumCT -= tmp->getRemTime();
	}
	return tmp;
}


void SJF::insertProcess(process* p)
{
	RdyList.Enqueue(p);
	sumCT += p->getRemTime();
}

void SJF::print()
{
	RdyList.print();
}

int SJF::getNumOfProcesses()
{
	return RdyList.GetSize();
}

SJF::~SJF(void)
{
}
