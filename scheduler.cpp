#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <iomanip>

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
void splitString2(string line, string name, int priority, string codeName, int arrTime){
	string temp;
	stringstream ss(line);

	ss >> temp;
	name = temp;
	ss >> temp;
	priority = stoi(temp);
	ss >> temp;
	codeName = temp;
	ss >> temp;
	arrTime = stoi(temp);

};
//compares the time for timeTable
bool operator<(const Event &a, const Event &b){
	return a.eventTime > b.eventTime;
}
//executed using the command: ./scheduler definition.txt code1.txt code2.txt code3.txt code4.txt output.txt
int main(int argc, char *argv[]) {
	//checks if the command is correct
	if (argc != 7) {
		cout << "Arguments are incorrect" << endl;
		return 1;
	}

	string line;

	vector< vector <int> > codes; //opens a vector of exectimes of codes
	vector<Process> processes;

	for (int i = 2; i < 6; i++){
		//starts with code1.txt
		ifstream infile(argv[i]);

		//reads the input
		if (infile.is_open()) {

			string name = "";
			int execTime = 0;
			bool exitLine = false;
			vector<int> execTimes;

			while(!exitLine) {
				getline(infile, line);
				splitString1(line, name, execTime);
				if(name.compare("exit") == 0){
					exitLine = true;
				}
				execTimes.push_back(execTime);
					
			}
			codes.push_back(execTimes);
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
			string codeName = "";
			int arrTime = 0;
			splitString2(line, name, priority, codeName, arrTime);
			processes.push_back(Process(name, priority, codeName, arrTime));
		}
	}

	

	return 0;

}
