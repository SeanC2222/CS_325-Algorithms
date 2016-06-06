#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>


/*Based on: http://stackoverflow.com/questions/26727824/how-to-parse-a-users-
input-and-store-each-individual-character-as-a-string*/

std::vector<std::vector <int> > parseInputFile(std::vector<std::string> input_string) {
	std::vector< std::vector<int> > vectorInput;
	std::string tmps;
	std::vector<int> tmpv;

	int i=0, j=0;

	for (i= 0; i < input_string.size(); i++){
		for (j = 0; j < input_string[i].length(); j++){
			if ((input_string[i][j] == '[') || (input_string[i][j] == ' ')){
			}
			else if ((isdigit(input_string[i][j])) || (input_string[i][j] == '-')){
				tmps.push_back(input_string[i][j]);
			}
			else if ((input_string[i][j] == ',') || (input_string[i][j] == ']')){
				tmpv.push_back(atoi(tmps.c_str()));
				tmps = "";
			}
			if ((j == (input_string[i].length() - 1)) && (input_string[i][0] != '[')){
				tmpv.push_back(atoi(tmps.c_str()));
				tmps = "";
			}
		}
		vectorInput.push_back(tmpv);
		tmpv.clear();
		tmps = "";
	}
	return vectorInput;
}

void printVect(std::vector<int> printVect, int count, std::ofstream * outputFile){
	*outputFile << "[";
	for (int i = 0; i < printVect.size(); i++) {
		*outputFile << printVect[i];
		if (i != (printVect.size() - 1))
			*outputFile << ",";
	}
        *outputFile << "]" << std::endl;
        *outputFile << count << std::endl;
        
	//print to screen - delete later
	/*
	std::cout << "[";
	for (int i=0; i < printVect.size(); i++){
		std::cout << printVect[i];
		if (i != (printVect.size() - 1 ))
		std::cout << ", ";
	}
	std::cout << "]" << std::endl;
	std::cout << count << std::endl;
	*/
}

int vectContSum(std::vector<int> vect){
	int count = 0;

	for (int i = 0; i < vect.size(); i++){
		count += vect[i];
	}
	return count;
}

/*********************************************************
*               changegreedy()
* Description: An approach to the coin change problem.
* This is a naive implementation since it may not be
* optimal.
* Parameters:
*   Vector with value of the coins V
*   Amount of change we are asked to make A
*********************************************************/
std::vector<int> changegreedy(std::vector<int>& V, int A){
	std::vector<int> sumCoins(V.size(), 0);
	int index = V.size() - 1;

	while (A > 0){
		while (V[index] > A){
			index--;
		}
		A = A - V[index];
		sumCoins[index]++;
	}
	return sumCoins;
}

int main(int argc, char *argv[]) {

	if (argc != 2){
		std::cout << "Usage: " << argv[0] << "[filename].txt" << std::endl;
		return 1;
	}

	std::vector< std::vector<int> > vectorInput;
	std::vector<std::string> setInFile;
	std::string input_string;
	std::ifstream problems(argv[1], std::ifstream::in);

	while (problems.good()) {
		getline(problems, input_string);
		if (input_string.length() != 0) {
			setInFile.push_back(input_string);
		}
	}

	problems.close();

	vectorInput = parseInputFile(setInFile);

	std::string fileName = argv[1];
	int index = fileName.find_last_of(".");

	std::string outputFileName = fileName.substr(0, index) + "change.txt";

	std::ofstream fileOutput;
	fileOutput.open(outputFileName.c_str(), std::ofstream::out);

	for (int i = 0; i < vectorInput.size(); i++){
		int sum = i + 1;
		std::vector<int> change(vectorInput[i].size(), 0);

		//Run and print changeGreedy
		change = changegreedy(vectorInput[i], vectorInput[sum][0]);
		int count = vectContSum(change);
		fileOutput << "changeGreedy: " << std::endl;
		printVect(change, count, &fileOutput);
		change.clear();
		
		i++; 
	}
	fileOutput.close();

	return 0;
}
