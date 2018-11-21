#ifndef PROCESS_H
#define PROCESS_H

#endif //PROCESS_H

#include <iostream>
#include <vector>

class Process {
public:

	vector<int> execTimes;
	
	string name;

	int priority;

	string codeName;

	int arrTime;

	int turnaroundTime;

	int waitTime;

	Process();

	Process(string name_, int priority_, string codeName_, int arrTime_);

	Process(const Process &other);

	Process &operator=(const Process &other);

	~Process();

};
