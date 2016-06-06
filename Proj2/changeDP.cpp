#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <algorithm>

class coinCount {
private:
    std::vector<int> count;
    unsigned int tCoins;

public:
    coinCount(){};
    
    coinCount(std::vector<int> newVals){
        this->count.resize(newVals.size(),0);
        this->tCoins = 0;
    }
    
    unsigned int getTCoins(){return this->tCoins;}
    int addCount(int i, int n){
        if(i > this->count.size()-1){return -1;} 
        else{
            this->count[i] += n; 
            this->tCoins++;
            return this->count[i];
        }
    }
    std::vector<int> getCount(){return this->count;}
    int getCount(int i){return this->count[i];}
    int getSize(){return this->count.size();}
    
    int copyCount(coinCount& C){
        if(C.getSize() != this->count.size()){return -1;}
        for(int i = 0; i < C.getSize(); i++){
            this->count[i] = C.getCount(i);
        }
        this->tCoins = C.getTCoins();
        return 0;
    }
};
/*********************************************************
*               changeDP()
* Description: This is the dynamic programming version
* that fills out a table and references previously
* calculated values of change.
* Parameters:
*   Vector with value of the coins V
*   Amount of change we are asked to make A
*********************************************************/
std::vector<int> changeDP(std::vector<int>& V, int A){
	//Create table with A+1 rows (includes sentinel change for 0)
	std::vector< coinCount > table (A+1, coinCount (V));
	//For every change amount, 1-A, find optimal solution
	for(int curChange = 1; curChange <= A; curChange++){
	    unsigned int trackMin = (unsigned int)(-1);
	    int minCoinIndex = trackMin;
	    coinCount* pMin;

	    for(int coin = V.size()-1; coin >= 0; coin--){
	       unsigned int prevMin = trackMin;
	       if(curChange >= V[coin]){
		   trackMin = std::min(trackMin, table[curChange-V[coin]].getTCoins());
		   if(trackMin != prevMin){
		       pMin = &table[curChange-V[coin]];
		       minCoinIndex = coin;
		   }
	       }
	    }
	    table[curChange].copyCount(*pMin);
	    table[curChange].addCount(minCoinIndex, 1);
	}
	return table[A].getCount();
}


std::vector<int> parseInput(std::string in){
    //Read in all integers from in
    std::vector<int> testVals;
    
    int temp;
    
    std::stringstream ssIn(in);
    while(ssIn.good()){
        ssIn >> temp; 
        
        if(ssIn.fail()){
            ssIn.clear();
            ssIn.get();   //Remove '[', ',', and ']' characters
        } else {
            testVals.push_back(temp); //Add ints to testVals
        }
    }

    return testVals;
}

void printChange(std::vector<int>& c, std::vector<int>& v, int tC, std::ofstream& ofs){
    /*ofs << "Target Change = " << tC << std::endl;
    ofs << "Coin Vals [";
    for(int i = 0; i < v.size(); i++){
        ofs << v[i];
        if(i < v.size()-1){
            ofs << ", ";
        } else {
            ofs << "]" << std::endl;
        }
    }*/
    int tCoins = 0;
    
    ofs << "Coin Amts [";
    for(int i = 0; i < c.size(); i++){
        tCoins += c[i];
        ofs << c[i];
        if(i < c.size()-1){
            ofs << ", ";
        } else {
            ofs << "]" << std::endl;
        }
    }
    ofs << "Total Coins = " << tCoins << std::endl;
    
    return;
}

int main(int argc, char *argv[]) {

	if (argc < 2){
		std::cout << "Usage: " << argv[0] << " [input_file] [outputfile]" << std::endl;
		return -1;
	}
    
    std::ifstream ifs(argv[1]);
    std::ofstream ofs;
    if(argc > 2){
        ofs.open(argv[2]);
    } else {
        ofs.open("changeDP.results.txt");
    }

    std::string input;
    int inputAmount;

    std::vector< std::vector<int> > coinValues;
    std::vector<int> targetChange;
  
    do{
        //Read Coin Values
        std::getline(ifs, input);
        //Read targetChange
        ifs >> inputAmount;
        coinValues.push_back(parseInput(input));
        targetChange.push_back(inputAmount);

        //Clear end of line characters/Set ifs.eof
        std::getline(ifs, input);

        if(coinValues.size() != targetChange.size()){
            std::cout << "Input file incorrect format." << std::endl;
            return -1;
        }
    }while(!ifs.eof());

    std::chrono::high_resolution_clock::time_point t1, t2;
    for(int i = 0; i < coinValues.size()-1; i++){
        std::vector<int> change;
        t1 = std::chrono::high_resolution_clock::now();
        change = changeDP(coinValues[i], targetChange[i]);
        t2 = std::chrono::high_resolution_clock::now();
        printChange(change, coinValues[i], targetChange[i], ofs);
        std::chrono::duration<double> runTime = std::chrono::duration_cast< std::chrono::duration<double> >(t2-t1);
        ofs << "Total Time = " << runTime.count() << std::endl << std::endl;
    }
    return 0;
}
