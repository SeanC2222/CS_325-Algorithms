#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void printRes(std::vector<int>&, std::vector<int>&);
std::vector<int> dynProg(std::vector<int>&, int);

int main(){

   std::vector<int> testData;

   int aCoinVals [][4] = {{1,2,4,8}, {1,3,7,12}};

   std::vector< std::vector<int> > coinVals;

   for(int i = 0; i < 2; i++){
      std::vector<int> temp;
      for(int j = 0; j < 4; j++){
	 temp.push_back(aCoinVals[i][j]);
      }
      coinVals.push_back(temp);
   }

   std::vector<int> coinCount; 

   std::cout << "15\n";
   coinCount.resize(coinVals[0].size(), 0);
   std::vector<int> res = dynProg(coinVals[0], 15);
   printRes(coinVals[0], res);
   std::cout << std::endl;
   coinCount.clear();

   std::cout << "29\n";
   coinCount.resize(coinVals[1].size(), 0);
   res = dynProg(coinVals[1], 29);
   printRes(coinVals[1], res);
   std::cout << std::endl;
   coinCount.clear();

   std::cout << "31\n";
   coinCount.resize(coinVals[1].size(), 0);
   res = dynProg(coinVals[1], 31);
   printRes(coinVals[1], res);
   std::cout << std::endl;
   coinCount.clear();

   return 0;
}

void printRes(std::vector<int>& vals, std::vector<int>& res){

   std::cout << "Coin Values: " << std::endl
	     << "[";
   for(int i = 0; i < vals.size(); i++){
      std::cout << vals[i];
      if(i < vals.size()-1){
	 std::cout << ", ";
      }
   }
   std:: cout << "]" << std::endl;

   std::cout << "Number of Coins: " << std::endl
	     << "[";
   for(int i = 0; i < res.size(); i++){
      std::cout << res[i];
      if(i < res.size()-1){
	 std::cout << ", ";
      }
   }
   std:: cout << "]" << std::endl;

   return;
}

std::vector<int> dynProg(std::vector<int>& V, int A){
   std::vector< std::vector<int> > table (A+1, std::vector<int> (V.size(), 0));

   for(int i = 1; i <= A; i++){
      int currentChange = i;
      for(int j = V.size()-1; j >= 0; j--){
	 if(currentChange >= V[j]){
	    table[i] = table[i-V[j]];
	    table[i][j]++;
	    break;
	 }

      }
   }
   return table[A];
}

