#include "FCFS.h"
#include <ctime>
FCFS::FCFS(scheduler* manager) : Processor(manager)
{
}


void FCFS::insertProcess(process* p)
{
	RdyList.insert(RdyList.getLength() + 1, p);//added 1 because of 1 indexed list
	sumCT += p->getRemTime();
	//0   5   rem = 3 
}

process* FCFS::killOrphans(process* child)
{
	process* tmp = child;
	if (child != nullptr)
	{
		//Manager->terminate(child);
		child = nullptr;
	}
	return tmp;
}
void FCFS::terminate(bool& found, int pid)
{
	if (pid == 0)//here we delete the ff process that ended its ct           // i addeed here running because of the weird problem
	{
		//if (running->getRemTime() == 0)
		bool b;
		process* tmpr = killOrphans(running->getrchild());//it returns the right child if exist , if not it reutrns null
		if (tmpr)
			Manager->killchild(tmpr->getPID());//here we terminate the child and if the child has another one it terminates it also		
		process* tmpl = killOrphans(running->getlchild());//it returns the right child if exist , if not it reutrns null
		if (tmpl)
			Manager->killchild(tmpl->getPID());//here we terminate the child and if the child has another one it terminates it also	
		Manager->terminate(running);
		this->makebusy(false);
		running = nullptr;
	}
	else//here we kill specific signals if we found it 
	{
		bool b;
		int i = RdyList.searchID(pid);
		if (running && i == 0 && running->getPID() == pid)
		{
			found = true;
			terminate(b, 0);
		}
		if (i > 0)
		{
			process* tmp2 = nullptr;
			process* tmp3 = nullptr;
			found = true;
			process* tmp = RdyList.getEntry(i);
			RdyList.remove(i);
			sumCT -= tmp->getRemTime();//first negative sumct
			bool b;
			if (tmp)
				tmp2 = killOrphans(tmp->getrchild());//it returns the child if exist , if not it reutrns null
			if (tmp2)
				Manager->killchild(tmp2->getPID());//here we terminate the child and if the child has another one it terminates it also
			if (tmp)
				tmp3 = killOrphans(tmp->getlchild());
			if (tmp3)
				Manager->killchild(tmp3->getPID());
			Manager->terminate(tmp);
		}
	}
}



void FCFS::ScheduleAlgo()
{
	updateWT();
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
			Manager->fork(this);
			running->decreaseRemTime();
		}
	}
	else if (!busy && RdyList.getLength())
	{
		running = RdyList.getEntry(1);
		RdyList.remove(1);
		sumCT -= running->getRemTime();
		busy = true;
	}
}



void FCFS::print()
{
	RdyList.print();
}

void FCFS::updateWT()
{
	for (size_t i = 1; i <= RdyList.getLength(); i++)
	{
		process* p = RdyList.getEntry(i);
		p->setWT(p->getWT() + 1);
	}
}

//process* FCFS::getmigrated(int maxw)
//{
//	for (size_t i = 1; i <= RdyList.getLength(); i++)
//	{
//		if (RdyList.getEntry(i)->getWT() > maxw)
//		{
//			process* tmp = RdyList.getEntry(i);
//			RdyList.remove(i);
//			return tmp;
//		}
//	}
//	return nullptr;
//}

int FCFS::getNumOfProcesses()
{
	return RdyList.getLength();
}

FCFS::~FCFS(void)
{
}

process* FCFS::stealtop()
{
	process* tmp = nullptr;
	if (RdyList.getLength())
	{
		tmp = RdyList.getEntry(1);
		RdyList.remove(1);
		sumCT -= tmp->getRemTime();
	}
	return tmp;
}

void FCFS::migRotation()
{
	running = nullptr;
	if (RdyList.getLength())
	{
		running = RdyList.getEntry(1);
		RdyList.remove(1);
		sumCT -= running->getRemTime();
		busy = true;
	}
}

