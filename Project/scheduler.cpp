#include "scheduler.h"
#include "processor.h"
#include "FCFS.h"
#include "SJF.h"
#include"RR.h"
#include <fstream>
#include <ctime>
#include "UI.h"



scheduler::scheduler()
{
	srand(time(NULL));
	Time = 1;
	NF = 0;
	NR = 0;
	NJ = 0;
	NP = 0;
	RRT = 0;
	RTF = 0;
	MaxW = 0;
	STL = 0;
	Forkprob = 0;
	M = 0;
	migRTF = 0;
	migMaxW = 0;
	forkedcnt = 0;
	killedcnt = 0;
	stolencnt = 0;
	totIO_D = 0;
}

int scheduler::getTotTRT()
{
	return 0;
}

void scheduler::migrate()
{
	if (NR)
	{
		for (int i = 0; i < NF; i++)
		{
			while (prolist[i]->getRunning() && prolist[i]->getRunning()->getWT() > MaxW && !prolist[i]->getRunning()->isForked())
			{
				Processor* shortest = prolist[NF + NJ];
				int mintime = shortest->getSumCT();
				for (int i = NF + NJ + 1; i < NP; i++)
				{
					if (prolist[i]->getSumCT() < mintime)
					{
						shortest = prolist[i];
						mintime = shortest->getSumCT();
					}
				}
				shortest->insertProcess(prolist[i]->getRunning());
				migMaxW++;
				prolist[i]->makebusy(0);
				prolist[i]->migRotation();
			}
		}
	}

	if (NJ)
	{
		for (int i = NF + NJ; i < NP; i++)
		{
			while (prolist[i]->getRunning() && prolist[i]->getRunning()->getRemTime() < RTF)
			{
				Processor* shortest = prolist[NF];
				int mintime = shortest->getSumCT();
				for (int i = NF + 1; i < NF + NJ; i++)
				{
					if (prolist[i]->getSumCT() < mintime)
					{
						shortest = prolist[i];
						mintime = shortest->getSumCT();
					}
				}
				shortest->insertProcess(prolist[i]->getRunning());
				migRTF++;
				prolist[i]->makebusy(0);

				prolist[i]->migRotation();
			}
		}
	}
}

void scheduler::insertToShortest(process* p, bool forked)
{
	Processor* shortest = findShortest(forked);
	shortest->insertProcess(p);
}


void scheduler::BlkToRdy()
{
	if (blklist.getLength())
	{
		process* temp = blklist.peekFront();
		temp->updateBlkTime();
		if (temp->getBlkTime() == 0)
		{
			insertToShortest(temp, temp->isForked());
			blklist.dequeue();
		}
	}
}

void scheduler::RuntoBlk(process* p)
{
	if (p)
		blklist.enqueue(p);
}

void scheduler::fork(Processor* pro)
{
	int randomNumber;
	randomNumber = 1 + rand() % 100;
	if (pro->getRunning() && randomNumber <= Forkprob && pro->getRunning()->getForkedCnt() < 2)
	{
		process* toinsert;
		process* forked = pro->getRunning();
		if (pro->getRunning()->getForkedCnt() == 0)
			toinsert = forked->fork(Time, M + forkedcnt + 1, forked->getRemTime(), 0);
		else
			toinsert = forked->fork(Time, M + forkedcnt + 1, forked->getRemTime(), 1);
		insertToShortest(toinsert, true);
		forkedcnt++;
	}
}

void scheduler::NewToRdy()
{
	if (newlist.getLength())
	{
		while (!newlist.isEmpty() && newlist.peekFront()->getAT() == Time)//i// added as if the processes ended it gets error
		{
			process* temp = newlist.peekFront();
			newlist.dequeue();
			insertToShortest(temp, 0);
		}
	}
}





void scheduler::steal()
{
	if (Time % STL == 0)
	{
		Processor* longest = findLongest();
		Processor* shortest = findShortest(false);
		float min = shortest->getSumCT();
		float mx = longest->getSumCT();
		while ((mx - min) / mx > .4)
		{
			process* tmp = longest->stealtop();
			if (tmp && !tmp->isForked())// added after deadline
			{

				shortest->insertProcess(tmp);
				mx = longest->getSumCT();//should we still look at all the processors at one timestep to balance all??
				min = shortest->getSumCT();// added after deadline
			}
		}
	}
}

Processor* scheduler::findShortest(bool forked)
{
	int mintime;
	Processor* shortest = nullptr;
	if (NP != 0)
	{
		shortest = prolist[0];
		mintime = shortest->getSumCT();
		if (forked)
		{
			for (int i = 1; i < NF; i++)
			{
				if (prolist[i]->getSumCT() < mintime)
				{
					shortest = prolist[i];
					mintime = shortest->getSumCT();
				}
			}
		}
		else
		{
			for (int i = 1; i < NP; i++)
			{
				if (prolist[i]->getSumCT() < mintime)
				{
					shortest = prolist[i];
					mintime = shortest->getSumCT();
				}
			}
		}
	}
	return shortest;
}

Processor* scheduler::findLongest()
{
	int maxtime;
	Processor* longest = nullptr;
	if (NP != 0)
	{

		longest = prolist[0];
		maxtime = longest->getSumCT();
		for (int i = 1; i < NP; i++)
		{
			if (prolist[i]->getSumCT() > maxtime)
			{
				longest = prolist[i];
				maxtime = longest->getSumCT();
			}
		}
	}
	return longest;
}


void scheduler::readIn(const std::string& filename, int& nf, int& ns, int& nr, int& rrt, int& rtf, int& maxw, int& stl, int& fork, float& m)
{
	std::ifstream fin(filename);
	fin >> nf >> ns >> nr >> rrt >> rtf >> maxw >> stl >> fork >> m;
	NP = nf + ns + nr;
	prolist = new Processor * [NP];
	for (int i = 0; i < m; i++)
	{
		int at, pid, ct, io_n;
		fin >> at >> pid >> ct >> io_n;
		process* newProcess = new process(at, pid, ct, io_n);
		int counter = 0;
		while (counter < io_n)
		{
			int num;
			char c;
			fin >> c;
			fin >> num;
			newProcess->insertio(num);
			fin >> c;
			fin >> num;
			newProcess->insertio(num);
			fin >> c;
			if (counter + 1 == io_n);
			else
				fin >> c;
			counter++;
		}
		newlist.enqueue(newProcess);

	}
	while (fin)
	{
		int x;
		fin >> x;
		if (fin)
			killerlist.enqueue(x);
	}
	for (int i = 0; i < nf; i++)
	{
		prolist[i] = new FCFS(this);
	}
	for (int i = nf; i < ns + nf; i++)
	{
		prolist[i] = new SJF(this);
	}
	for (int i = ns + nf; i < nr + ns + nf; i++)
	{
		prolist[i] = new RR(this, rrt);
	}
}

void scheduler::outputFile(const string& filename)
{
	ofstream out(filename);
	float totWT = 0, totRT = 0, totTRT = 0, totUti = 0;
	out << "TT\t" << "PID\t" << "AT\t" << "CT\t" << "IO_D\t\t" << "WT\t" << "RT\t" << "TRT\t" << endl;
	if (NP)
	{
		for (int i = 0; i < M + forkedcnt; i++)
		{
			process* temp = termlist.peekFront();
			out << temp->getTT() << "\t" << temp->getPID() << "\t" << temp->getAT() << "\t" << temp->getCT() << "\t" << temp->getTotIO_D() << "\t\t" << temp->getWT() << "\t" << temp->getRT() << "\t" << temp->getTRT() << endl;
			totWT += temp->getWT();
			totRT += temp->getRT();
			totTRT += temp->getTRT();
			delete temp;
			termlist.dequeue();
		}
	}
	out << "Processes: " << M + forkedcnt << endl;
	out << "Avg WT = " << totWT / M << ",\t" << "Avg RT = " << totRT / M << ",\t" << "Avg TRT = " << totTRT / M << endl;
	out << "Migration%:\tRTF = " << migRTF / M * 100 << "%,\t" << "MaxW = " << migMaxW / M * 100 << "%" << endl;
	out << "Forked Process: " << forkedcnt / M * 100 << "%" << endl;
	out << "Killed Process: " << killedcnt / M * 100 << "%" << endl << endl;
	out << "Processors: " << NP << "[" << NF << " FCFS, " << NJ << " SJF, " << NR << " RR]" << endl;
	out << "Processors Load" << endl;
	for (int i = 0; i < NP; i++)
	{
		Processor* temp = prolist[i];
		out << "P" << i + 1 << " = " << temp->getBusyTime() / totTRT * 100 << "%";
		if (i < NP - 1)
			out << ",\t";
		else
			out << endl << endl;
	}
	out << "Processors Utiliz" << endl;
	for (int i = 0; i < NP; i++)
	{
		Processor* temp = prolist[i];
		float utili = temp->getBusyTime() / (float)(temp->getBusyTime() + temp->getIdleTime()) * 100;
		totUti += utili;
		out << "P" << i + 1 << " = " << utili << "%";
		if (i < NP - 1)
			out << ",\t";
		else
			out << endl;
	}
	out << "Avg Utilization = " << totUti / NP << "%" << endl;
}


void scheduler::killchild(int id)
{
	bool z = false;
	for (int i = 0; i < NF; i++)//v
	{
		prolist[i]->terminate(z, id);////////////////////////// to be checked 
		if (z)
			break;
	}
}

void scheduler::sim()
{
	UI ui;
	string filename = ui.readfilename();
	int mode = ui.getMode();
	ui.printStarted(mode);
	readIn(filename, NF, NJ, NR, RRT, RTF, MaxW, STL, Forkprob, M);
	while (M + forkedcnt != termlist.getLength() && NP)
	{
		NewToRdy();
		for (int i = 0; i < NP; i++)
		{
			prolist[i]->ScheduleAlgo();
			prolist[i]->UpdateBusyIdleTime();
			process* tmp = prolist[i]->getRunning();
			if (tmp && tmp->isFirstTime())
			{
				tmp->setRT(Time - tmp->getAT());
				tmp->setFirstTime();
			}
		}
		killSig();
		migrate();

		BlkToRdy();
		steal();
		ui.printTimeStep(Time, NF, NJ, NR, prolist, blklist, termlist, mode);
		Time++;
	}
	outputFile("output.txt");
	ui.printFinished(mode);
}

void scheduler::killSig()
{
	int timetokill = -1;
	if (killerlist.getLength())
		timetokill = killerlist.peekFront();
	if (timetokill == Time)
	{
		bool z = false;
		killerlist.dequeue();
		for (int i = 0; i < NF; i++)
		{
			//((FCFS*)prolist[i])->updateWT(); where to put this function ?? in scheduler or in sim function ?? 
			prolist[i]->terminate(z, killerlist.peekFront());
			if (z)
			{
				killedcnt++;
				break;
			}
		}
		killerlist.dequeue();
	}
}

void scheduler::terminate(process* terminated)
{
	terminated->setTT(Time);
	termlist.enqueue(terminated);
	terminated->setTRT(Time - terminated->getAT());
	terminated->setWT(terminated->getTRT() - terminated->getCT() + terminated->getRemTime());
}

scheduler:: ~scheduler()
{
	for (int i = 0; i < NP; i++)
	{
		delete prolist[i];
	}
	delete[]prolist;
	//while (!killerlist.isEmpty())
		//killerlist.dequeue();
}