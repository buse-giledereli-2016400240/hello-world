#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cstddef>
#include <cstdio>
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
//executed using the command: ./scheduler output.txt
int main(int argc, char *argv[]) {

    freopen("output.txt","w",stdout);
	//checks if the command is correct
	if (argc != 2) {
		cout << "Arguments are incorrect" << endl;
		return 1;
	}

	string line;

	vector <int> codes[5]; //opens an array of exectimes of codes
	priority_queue <Process> timeTable; //a timetable based on arrival times of processes
    vector<Process> processTable; //for keeping data

    string codePaths[5];
    codePaths[1] = "code1.txt";
    codePaths[2] = "code2.txt";
    codePaths[3] = "code3.txt";
    codePaths[4] = "code4.txt";

    ifstream infile;

    for (int i = 1; i < 5; i++){
		//starts with code1.txt
		infile.open(codePaths[i]);

		//reads the input
		if (infile.is_open()) {

			string name = "";
			int execTime = 0;
			bool exitLine = false;
			vector<int> execTimes;
			execTimes.push_back(0); //just for making the code more readable, inst1 will be in execTimes[1] etc

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

	infile.open("definition.txt");
	while(getline(infile, line)){

		string name = "";
		int priority = 0;
		int codeNo = 0;
		int arrTime = 0;
		splitString2(line, name, priority, codeNo, arrTime);
        timeTable.push(Process(name, priority, codeNo, arrTime, codes[codeNo].size()));
	}
    infile.close();
	
	priority_queue<Process, vector<Process>, LessThanByPriority> readyQueue;
	int currTime = 0;
    priority_queue<Process> lastVersion;
	
	while(!timeTable.empty() || !readyQueue.empty()){
        printQueue(currTime, readyQueue);
		if(readyQueue.empty()){
			Process curr = timeTable.top();
			timeTable.pop();
            readyQueue.push(curr);
			currTime = curr.arrTime;
			Process next = timeTable.top();
			while(currTime == next.arrTime){
                cout<< "I'M HERE" << endl;
				readyQueue.push(next);
                timeTable.pop();
                next = timeTable.top();
			}
		}else if(!timeTable.empty()){
            Process temp = readyQueue.top();
            readyQueue.pop();
            Process nextArr = timeTable.top();
            timeTable.pop();
            while(currTime < nextArr.arrTime){
                int instTime = codes[temp.codeNo][temp.nextInst];
                currTime += instTime;
                temp.cpuTime += instTime;
                temp.nextInst++;
                if(temp.lastInstNo == temp.nextInst){
                    temp.turnaroundTime = currTime - temp.arrTime;
                    lastVersion.push(temp);
                    printQueue(currTime, readyQueue);
                    temp = readyQueue.top();
                    readyQueue.pop();
                }
            }
            readyQueue.push(temp);
            readyQueue.push(nextArr);
        }else{
            while(!readyQueue.empty()){
                Process temp = readyQueue.top();
                readyQueue.pop();
                while(true) {
                    int instTime = codes[temp.codeNo][temp.nextInst];
                    currTime += instTime;
                    temp.cpuTime += instTime;
                    temp.nextInst++;
                    if (temp.lastInstNo == temp.nextInst) {
                        temp.turnaroundTime = currTime - temp.arrTime;
                        lastVersion.push(temp);
                        break;
                    }
                }
                printQueue(currTime, readyQueue);
            }
        }
	}

    printStats(lastVersion);

	return 0;

}
