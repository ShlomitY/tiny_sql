#include "Table.h"


using namespace std;

void devider(const string& command, vector<string>& words);
int handle(vector<string>& words, int number_command, vector<Table*>& tables, std::ofstream& UnsuccessfulFile , std::ofstream& SelectOutputFile);
void printTables(const vector<Table*> &tables, std::ofstream& file, int command);


int main() {
	vector<Table*> tables;
	ifstream command_file("../Input-output/Input/input.txt");
	std::ofstream CurrentTablesFile("../Input-output/Output/CurrentTables.txt");
	std::ofstream SelectOutputFile("../Input-output/Output/SelectOutput.txt");
	std::ofstream UnsuccessfulFile("../Input-output/Output/Unsuccessful.txt");

	if (!UnsuccessfulFile) {
		cout << "failed to open the input commands file!" << endl;
		cout << "Remainder: the commands file should be located in the Input-output\\Input folder and should be named \"input.txt\" ";
		return -1;
	}

	if (!SelectOutputFile) {
		UnsuccessfulFile << "failed to open the input commands file!" << endl;
		UnsuccessfulFile << "Remainder: the commands file should be located in the Input-output\\Input folder and should be named \"input.txt\" ";
		return -1;
	}


	if (!command_file) {
		UnsuccessfulFile << "failed to open the input commands file!" << endl;
		UnsuccessfulFile << "Remainder: the commands file should be located in the Input-output\\Input folder and should be named \"input.txt\" ";
		return -1;
	}
	int number_command = 0;

	string current_command;
	while(getline(command_file, current_command)) {
		if (current_command.size() < 2) {
			continue;
		}
		number_command++;
		vector<string> words;
		devider(current_command, words);
		int ret = handle(words, number_command, tables, UnsuccessfulFile, SelectOutputFile);
		if (ret == 1) {
			continue;
		}
		if (ret == 2) {
			return 1;
		}

		if (CurrentTablesFile.is_open()) {
			printTables(tables, CurrentTablesFile, number_command);
		} else {
			UnsuccessfulFile << "Failed to open file for writing." << endl;
		}


	}
	CurrentTablesFile.close();
	command_file.close();
	return 0;
}