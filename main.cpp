#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>
#include "Process.h"

using namespace std;

//devides code string line
void splitString1(string line, string &name, int &execTime){
	string temp;
	stringstream ss(line);

	ss >> temp;
	name = temp;
	ss >> temp;
	execTime = stoi(temp);
};
//devides process string line
void splitString2(string line, string &name, int &priority, int &codeNo, int &arrTime){
	string temp;
	stringstream ss(line);

	ss >> temp;
	name = temp;
	ss >> temp;
	priority = stoi(temp);
	ss >> temp;
	size_t found = temp.find_first_of("1234");
	codeNo = temp[found] - '0';
	ss >> temp;
	arrTime = stoi(temp);

};
//prints out the ready queue
template<class T>
void printQueue(int currTime, T readyQueue){
	cout << currTime << ":HEAD-";
    if(readyQueue.empty())
        cout << "-";
    while(!readyQueue.empty()){
        Process temp = readyQueue.top();
        cout << temp.name << "[" << temp.nextInst << "]-";
        readyQueue.pop();
    }
    cout << "TAIL" << endl;

};
//prints the turnaround and waiting times for the processes
void printStats(priority_queue <Process> lastVersion){
    cout << endl;
    while(!lastVersion.empty()){
        cout << "Turnaround time for ";
        Process temp = lastVersion.top();
        cout << temp.name << " = " << temp.turnaroundTime << " ms" << endl;
        cout << "Waiting time for ";
        cout << temp.name << " = " << temp.turnaroundTime-temp.cpuTime << endl;
        lastVersion.pop();
    }
};
//compares with respect to arrival time for timeTable
bool operator<(const Process &a, const Process &b){
	return a.arrTime > b.arrTime;
}
//compares with respect to priority then arrival time for ready queue
struct LessThanByPriority
{
  bool operator()(const Process &a, const Process &b) const
  {
    return (a.priority > b.priority || (a.priority == b.priority && a.arrTime > b.arrTime));
  }
};
//executed using the command: ./scheduler
int main(int argc, char *argv[]) {

    //redirects stdout to output.txt so cout woill write to the output file
    freopen("output.txt","w",stdout);

	string line;

	vector <int> codes[5]; //opens an array of exectimes of codes

    string codePaths[5]; //a string array to hold the name of files
    codePaths[1] = "code1.txt";
    codePaths[2] = "code2.txt";
    codePaths[3] = "code3.txt";
    codePaths[4] = "code4.txt";

    ifstream infile;

    for (int i = 1; i < 5; i++){
		//opens the code file
		infile.open(codePaths[i]);

		//reads the input
		if (infile.is_open()) {

			string name = "";
			int execTime = 0;
			bool exitLine = false; //controls if it is the end of file
			vector<int> execTimes; //holds execution times for the given code
			execTimes.push_back(0); //just for making the code more readable, inst1 will be in execTimes[1] etc

            //reads the instructions
			while(!exitLine) {
				getline(infile, line);
				splitString1(line, name, execTime);
				if(name.compare("exit") == 0){
					exitLine = true;
				}
				execTimes.push_back(execTime);
					
			}
			codes[i] = execTimes;
			execTimes.clear();
			infile.close();
            infile.clear();
		}
		else{
			cout << "Inputs cannot be opened." << endl;
			return 1;
		}
	}

    priority_queue <Process> timeTable; //a timetable based on arrival times of processes

    //opes the definition file
	infile.open("definition.txt");
	while(getline(infile, line)){

		string name = "";
		int priority = 0;
		int codeNo = 0;
		int arrTime = 0;
		splitString2(line, name, priority, codeNo, arrTime);
        timeTable.push(Process(name, priority, codeNo, arrTime, (int)codes[codeNo].size())); //pushes the read process into the timetable
	}
    infile.close();
	
	priority_queue<Process, vector<Process>, LessThanByPriority> readyQueue; // a ready queue for the CPU sorted with respect to priority then arrival time
	int currTime = 0; //starts with current time = 0
    priority_queue<Process> lastVersion; //this queue will be needed to print out the statistics

    //loop will continue until both the time table and the ready queue is empty
	while(!timeTable.empty() || !readyQueue.empty()){
        printQueue(currTime, readyQueue); //queue will be printed every time there is a change
        //this is the case where ready queue is empty but there will be new arrivals
		if(readyQueue.empty()){
			Process curr = timeTable.top();
			timeTable.pop();
            readyQueue.push(curr); //pushes the new arrival into the ready queue
			currTime = curr.arrTime; //updates the time according to arrival time
            if(!timeTable.empty()) {
                Process next = timeTable.top();
                //a loop to get all the processes that arrive at the same time
                while (currTime == next.arrTime) {
                    readyQueue.push(next); //pushes the new arrival into the ready queue
                    timeTable.pop();
                    if(timeTable.empty())
                        break;
                    next = timeTable.top();
                }
            }
		}else if(!timeTable.empty()){ //this is the case where there are arrivals and the ready queue is not empty
            bool emptyReadyQueue = false;
            Process temp = readyQueue.top();
            readyQueue.pop();
            Process nextArr = timeTable.top();
            timeTable.pop();
            //the processes from the ready queue will go on until there is an arrival
            while(currTime < nextArr.arrTime){
                int instTime = codes[temp.codeNo][temp.nextInst]; //gets the execution time for next instruction
                currTime += instTime; //updates the currTime according to instTime
                temp.cpuTime += instTime; //updates the cpu time for the process
                temp.nextInst++; //updates the nextInst
                //if the process is finished
                if(temp.lastInstNo == temp.nextInst){
                    temp.turnaroundTime = currTime - temp.arrTime; //calculates turnaroundTime
                    lastVersion.push(temp); //pushes the process into the queue for statistics
                    if(readyQueue.empty()){
                        emptyReadyQueue = true;
                        break;
                    }
                    if(currTime != nextArr.arrTime)
                        printQueue(currTime, readyQueue); //prints since a process has left the ready queue
                    temp = readyQueue.top(); //the next process comes from the ready queue
                    readyQueue.pop();
                }
            }
            if(!emptyReadyQueue) {
                readyQueue.push(temp); //the last process which is not completed yet is pushed back into the ready queue
                readyQueue.push(nextArr); //the next arrival is pushed into the ready queue
                if(!timeTable.empty()) {
                    Process next = timeTable.top();
                    //a loop to get all the processes that arrive at the same time
                    while (currTime >= next.arrTime) {
                        readyQueue.push(next); //pushes the new arrival into the ready queue
                        timeTable.pop();
                        if(timeTable.empty())
                            break;
                        next = timeTable.top();
                    }
                }
            }else{
                timeTable.push(nextArr);
            }

        }else{ //this is the case where there are no arrivals left, just the ready queue
            while(!readyQueue.empty()){
                Process temp = readyQueue.top();
                readyQueue.pop();
                while(true) {
                    int instTime = codes[temp.codeNo][temp.nextInst]; //gets the execution time for next instruction
                    currTime += instTime; //updates the currTime according to instTime
                    temp.cpuTime += instTime; //updates the cpu time for the process
                    temp.nextInst++; //updates the nextInst
                    //if the process is finished
                    if (temp.lastInstNo == temp.nextInst) {
                        temp.turnaroundTime = currTime - temp.arrTime; //calculates turnaroundTime
                        lastVersion.push(temp); //pushes the process into the queue for statistics
                        break;
                    }
                }
                printQueue(currTime, readyQueue); //prints since a process has left the ready queue
            }
        }
	}

    printStats(lastVersion);

	return 0;

}
