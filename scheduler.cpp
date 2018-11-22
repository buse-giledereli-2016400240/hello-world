#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>
#include <cstddef>

using namespace std;

//devides code string line
void splitString1(string line, string name, int execTime){
	string temp;
	stringstream ss(line);

	ss >> temp;
	name = temp;
	ss >> temp;
	execTime = stoi(temp);
};
//devides process string line
void splitString2(string line, string name, int priority, int codeNo, int arrTime){
	string temp;
	stringstream ss(line);

	ss >> temp;
	name = temp;
	ss >> temp;
	priority = stoi(temp);
	ss >> temp;
	size_t found = temp.find_first_of("1234");
	codeNo = temp[found];
	ss >> temp;
	arrTime = stoi(temp);

};
void printQueue{
	
}
//compares with respect to arrival time for timeTable
bool operator<(const Process &a, const Process &b){
	return a.arrTime > b.arrTime;
}
//compares with respect to priority then arrival time for ready queue
struct LessThanByPriority
{
  bool operator()(const Process &a, const Process &b) const
  {
    return (a.priority > b.priority || (a.priority == b.priority && a.arrTime > b.arrTime);
  }
};
//executed using the command: ./scheduler definition.txt code1.txt code2.txt code3.txt code4.txt output.txt
int main(int argc, char *argv[]) {
	//checks if the command is correct
	if (argc != 7) {
		cout << "Arguments are incorrect" << endl;
		return 1;
	}

	string line;

	vector< vector <int> > codes; //opens a vector of exectimes of codes
	priority_queue <Process> timeTable; //a timetable based on arrival times of processes

	for (int i = 2; i < 6; i++){
		//starts with code1.txt
		ifstream infile(argv[i]);

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
			codes[i-1] = execTimes;
			execTimes.clear();
			infile.close();
		}
		else{
			cout << "Inputs cannot be opened." << endl;
			return 1;
		}
	}

	ifstream infile(argv[1]);
	bool empty = false;
	while(!empty){
		getline(infile, line);
		if(line.empty()){
			empty = true;
		}
		else{
			string name = "";
			int priority = 0;
			string codeNo = "";
			int arrTime = 0;
			splitString2(line, name, priority, codeNo, arrTime);
			timeTable.push(Process(name, priority, codeNo, arrTime));
		}
	}
	
	priority_queue<Process, vector<Process>, LessThanByPriority> readyQueue;
	int currTime = -1;
	
	while(!timeTable.empty() || !readyQueue.empty()){
		if(readyQueue.empty()){
			Process temp = timeTable.top();
			timeTable.pop();
			currTime = temp.arrTime;
			Process next = timeTable.top();
			while(currTime < next.arrTime){
				
			}
		}
	}

	return 0;

}
