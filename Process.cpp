#include "Process.h"

Process::Process(){
	string name = "";
	int priority = 0;
	int codeNo = 0;
	int arrTime = 0;
	int turnaroundTime = 0;
	int waitTime = 0;
	int nextInst = 0;
}

Process::Process(string name_, int priority_, string codeName_, int arrTime_) {
	string name = "";
	int priority = 0;
	int codeNo = 0;
	int arrTime = 0;
	int turnaroundTime = 0;
	int waitTime = 0;
	int nextInst = 0;
}
Process::Process(const Process &other){
	string name = other.name;
	int priority = other.priority;
	int codeNo = other.codeNo;
	int arrTime = other.arrTime;
	int turnaroundTime = other.turnaroundTime;
	int waitTime = other.waitTime;
	int nextInst = other.nextInst;
}

Process& Process::operator=(const Process &other){
	string name = other.name;
	int priority = other.priority;
	int codeNo = other.codeNo;
	int arrTime = other.arrTime;
	int turnaroundTime = other.turnaroundTime;
	int waitTime = other.waitTime;
	int nextInst = other.nextInst;
	return *this;
}

Process::~Process() {

}
