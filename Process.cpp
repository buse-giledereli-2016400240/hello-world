#include "Process.h"

Process::Process(){
	string name = "";
	int priority = 0;
	string codeName = "";
	int arrTime = 0;
	int turnaroundTime = 0;
	int waitTime = 0;
}

Process::Process(string name_, int priority_, string codeName_, int arrTime_) {
	string name = "";
	int priority = 0;
	string codeName = "";
	int arrTime = 0;
	int turnaroundTime = 0;
	int waitTime = 0;
}
Process::Process(const Process &other){
	string name = other.name;
	int priority = other.priority;
	string codeName = other.codeName;
	int arrTime = other.arrTime;
	int turnaroundTime = other.turnaroundTime;
	int waitTime = other.waitTime;
}

Process& Process::operator=(const Process &other){
	string name = other.name;
	int priority = other.priority;
	string codeName = other.codeName;
	int arrTime = other.arrTime;
	int turnaroundTime = other.turnaroundTime;
	int waitTime = other.waitTime;
	return *this;
}

Process::~Process() {

}
