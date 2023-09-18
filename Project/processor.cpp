#include "Processor.h"


Processor::Processor(scheduler* Sched)
{
	busy = false;
	sumCT = 0;
	busyTime = 0;
	idleTime = 0;
	running = nullptr;
	Manager = Sched;//added
}


bool Processor::isbusy()
{
	return busy;
}

void Processor::makebusy(bool b)
{
	busy = b;
}

void Processor::UpdateBusyIdleTime()
{
	if (busy)
		busyTime++;
	else
		idleTime++;
}

int Processor::getSumCT()
{
	return sumCT;

}

void Processor::setSumCT(int a)
{
	sumCT = a;
}

int Processor::getBusyTime()
{
	return busyTime;
}

int Processor::getIdleTime()
{
	return idleTime;
}



//process* Processor::getmigrated(int x)
//{
//	return nullptr;
//}

void Processor::migRotation()
{

}

process* Processor::getRunning()
{
	return running;
}

Processor::~Processor(void)
{
}


