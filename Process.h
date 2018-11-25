#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>


class Process {
public:
	
	std::string name; //holds the name of the process for printing

	int priority; //holds the priority of the process to sort in ready queue

	int codeNo; //holds the actual code name(just the number) this process has

	int arrTime; //holds the arrival time of the process

    int lastInstNo; //holds the last instruction number(+1) of the process

	int turnaroundTime; //holds the turnaround time for stats

	int cpuTime; //holds the cpu time for stats

	int nextInst; //holds the next instruction to be executed

	Process();

	Process(std::string name_, int priority_, int codeNo_, int arrTime_, int lastInstNo_);

	Process(const Process &other);

	Process &operator=(const Process &other);

	~Process();

};

#endif //PROCESS_H
