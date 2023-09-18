#pragma once
#include "processor.h"
#include <chrono>
#include <thread>

enum mode {
	INTERACTIVE = 1,
	STEPBYSTEP,
	SILENT
};

class UI
{
public:
	void printTimeStep(int t, int fcfs, int sjf, int rr, Processor** prolist, const LinkedQueue<process*> &blklist, const LinkedQueue<process*> &termlist, int mode);
	void printFinished(int mode);
	void printStarted(int mode);
	int getMode();
	string readfilename();
};

