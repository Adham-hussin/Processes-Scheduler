#include "UI.h"
ostream& operator<<(ostream& cout, const process& p)
{
	cout << p.PID;
	return cout;
}

void UI::printTimeStep(int t, int fcfs, int sjf, int rr, Processor** prolist, const LinkedQueue<process*> &blklist, const LinkedQueue<process*> &termlist, int mode)
{
	if (mode == INTERACTIVE || mode == STEPBYSTEP)
	{
		int n = fcfs + sjf + rr;
		cout << "Current Timestep:" << t << endl;
		cout << "--------------     RDY processes  ----------------------" << endl;

		for (int i = 0; i < fcfs; i++)
		{
			cout << "processor " << i << "[FCFS]: " << prolist[i]->getNumOfProcesses() << " RDY: ";
			prolist[i]->print();
			cout << endl;

		}

		for (int i = fcfs; i < sjf + fcfs; i++)
		{
			cout << "processor " << i << "[SJF]: " << prolist[i]->getNumOfProcesses() << " RDY: ";
			prolist[i]->print();
			cout << endl;
		}

		for (int i = fcfs + sjf; i < rr + sjf + fcfs; i++)
		{
			cout << "processor " << i << "[RR]: " << prolist[i]->getNumOfProcesses() << " RDY: ";
			prolist[i]->print();
			cout << endl;
		}

		cout << "--------------		BLK processes  ----------------------" << endl;
		cout << blklist.getLength() << " BLK: ";
		blklist.print();
		cout << endl;

		cout << "--------------     RUN processes  ----------------------" << endl;

		int runNum = 0;
		for (int i = 0; i < n; i++)
		{
			if (prolist[i]->isbusy())
			{
				runNum++;
			}
		}
		cout << runNum << " RUN: ";
		int j = 0;
		for (int i = 0; i < n; i++)
		{
			if (prolist[i]->isbusy())
			{
				j++;
				cout << prolist[i]->getRunning()->getPID() << "(P" << i << ")";
				if (j + 1 <= runNum)
				{
					cout << ", ";
				}
			}
		}
		cout << endl;

		cout << "--------------     TRM processes  ----------------------" << endl;
		cout << termlist.getLength() << " TRM: ";
		termlist.print();
		cout << endl;
		if (mode == INTERACTIVE)
		{
			cout << endl << "PRESS ANY KEY TO MOVE TO NEXT STEP !" << endl << endl << endl;
			system("pause");
		}
		else
		{
			this_thread::sleep_for(chrono::seconds(1));
		}
	}
	
}

void UI::printFinished(int mode)
{
	if (mode == SILENT)
		cout << "Simulation ends, output file created" << endl;
}

void UI::printStarted(int mode)
{
	if (mode == SILENT)
		cout << "Silent Mode.........      Simulation starts........." << endl;
}

int UI::getMode()
{
	cout << "Please pick a mode:" << endl << "1.Interactive Mode" << endl << "2.Step by Step Mode" << endl << "3.Silent Mode" << endl;
	int mode;
	cin >> mode;
	while (mode > 3 || mode < 1)
	{
		cout << "ERROR: Please enter a valid Input" << endl << "1.Interactive Mode" << endl << "2.Step by Step Mode" << endl << "3.Silent Mode" << endl;
		cin >> mode;
	}
	return mode;
}

string  UI::readfilename()
{

	cout << "                                               PROCESS SCHEDULER PROJECT" << endl;
	cout << "Enter file name: ";
	string s;
	cin >> s;
	return s + ".txt";
	
}