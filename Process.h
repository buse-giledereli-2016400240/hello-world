#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <vector>


class Process {
public:
	
	std::string name;

	int priority;

	int codeNo;

	int arrTime;

    int lastInstNo;

	int turnaroundTime;

	int cpuTime;

	int nextInst;

	Process();

	Process(std::string name_, int priority_, int codeNo_, int arrTime_, int lastInstNo_);

	Process(const Process &other);

	Process &operator=(const Process &other);

	~Process();

};

#endif //PROCESS_H
