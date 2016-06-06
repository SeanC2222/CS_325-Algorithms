#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <chrono>


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
}

int vectContSum(std::vector<int> vect){
	int count = 0;

	for (int i = 0; i < vect.size(); i++){
		count += vect[i];
	}
	return count;
}

/*********************************************************
*               changeSlow()
* Description: An approach to the coin change problem.
* This is a brute force implementation chekcing every combination
* through the use of a recursive function
* Parameters:
*   Vector with value of the coins V
* 	Size of input vector
*   Amount of change we are asked to make A
*********************************************************/
std::vector<int> changeSlow(std::vector<int>& input, int value, int amount)
{
	int minNum = amount + 1;
	int resultSum, interResSum;
	std::vector<int>interRes(value,0);
	std::vector<int>resultVector(value,0);
	resultVector.at(0)=minNum;
	
	//Base case if there amount is 0
	if (amount == 0)
	{
		std::vector<int>result(value,0);
		return result;
	}
	
	//Iterate through values of coin
	for (int i = 0; i < value; i++)
	{
		//Check that coin value doesn't exceed amount left
		if (input.at(i) <= amount)
		{
			//Iterate through number of each coin using recursion
			interRes = changeSlow(input, value, amount - input.at(i));
			
			//Sum up results and intermediate results
			resultSum = interResSum = 0;
			for (int j = 0; j < resultVector.size(); j++)
			{
				resultSum += resultVector.at(j);
				interResSum += interRes.at(j);
			}
			
			//Check if new minimum
			if (resultSum > (interResSum + 1))
			{
				//Increment index to add another coin of that value
				interRes.at(i) = interRes.at(i) + 1;
				//Copy new minimum to result vector
				for (int k = 0; k < interRes.size(); k++)
					resultVector.at(k) = interRes.at(k);
			}
		}
	}
	
	return resultVector;
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
	std::chrono::duration<double> timeDiff;
	
	//Initialize timing mechanism
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();

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

	fileOutput << "Algorithm changeSlow: " << std::endl;
	for (int i = 0; i < vectorInput.size(); i++){
		int sum = i + 1;
		std::vector<int> change(vectorInput[i].size(), 0);
		
		//Run and print changeSlow
		start = std::chrono::high_resolution_clock::now();  //Start time
		change = changeSlow(vectorInput[i], vectorInput[i].size(), vectorInput[sum][0]);
		end = std::chrono::high_resolution_clock::now(); //End Time
		int count = vectContSum(change);
		printVect(change, count, &fileOutput);
		timeDiff = end - start; //Calculate time
		
		//Print the following line for testing  only
		//fileOutput << "Time: " << timeDiff.count() << ", Amount: " << vectorInput[sum][0] << std::endl;
		
		change.clear();
		
		i++;
	}
	fileOutput.close();

	return 0;
}
