#include "Process.h"

Process::Process(){
	std::string name = "";
	priority = 0;
	codeNo = 0;
	arrTime = 0;
	lastInstNo = 0;
	turnaroundTime = 0;
	cpuTime = 0;
	nextInst = 1;
}

Process::Process(std::string name_, int priority_, int codeNo_, int arrTime_, int lastInstNo_) {
	name = name_;
	priority = priority_;
	codeNo = codeNo_;
	arrTime = arrTime_;
	lastInstNo = lastInstNo_;
	turnaroundTime = 0;
	cpuTime = 0;
	nextInst = 1;
}
Process::Process(const Process &other){
	name = other.name;
	priority = other.priority;
	codeNo = other.codeNo;
	arrTime = other.arrTime;
	lastInstNo = other.lastInstNo;
	turnaroundTime = other.turnaroundTime;
	cpuTime = other.cpuTime;
	nextInst = other.nextInst;
}

Process& Process::operator=(const Process &other){
	name = other.name;
	priority = other.priority;
	codeNo = other.codeNo;
	arrTime = other.arrTime;
	lastInstNo = other.lastInstNo;
	turnaroundTime = other.turnaroundTime;
	cpuTime = other.cpuTime;
	nextInst = other.nextInst;
	return *this;
}

Process::~Process() {

}
