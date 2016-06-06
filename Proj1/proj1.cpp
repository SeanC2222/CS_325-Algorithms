#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cstdlib>

#define MSS_TEST 0  //0 = MSS_Problems, 1 = MSS_TestProblems

void printVect(std::vector<int>&);
void printResults(std::ofstream&, std::vector<int>&);
int sumVector(std::vector<int>&);
void enumeration(std::vector<int>&, int&, int&, int&);
void enumeration2(std::vector<int>&, int&, int&, int&);
std::vector<int> linearTime(std::vector<int>&);

struct maxSubData{
   public:
      int maxSum;
      int low;
      int high;
};
struct maxSubData divAndConq(std::vector<int>&, int, int);
struct maxSubData _maxSubCross(std::vector<int>&, int, int, int);

void divideConquer(std::vector<int>&, std::vector<int>&, int&);
int _recursive(std::vector<int>&, int, int, int&, int&);

int main(){

   std::vector<int> testVals; 
   std::vector<int> subarray;
   int sum = 0;

   std::ifstream ifs;       //Input File Stream
   std::ofstream ofs;
   
   if(MSS_TEST){        //If MSS_TEST == 1, use MSS_TestProblems.txt
      ifs.open("MSS_TestProblems.txt");
      if(ifs){
         //std::cout << "MSS_TestProblems.txt opened!" << std::endl;
      } else {
         std::cout << "Failed to open MSS_TestProblems.txt!" << std::endl;
         return -1;
      }
   } else {             //Else use MSS_Problems.txt
      ifs.open("MSS_Problems.txt", std::fstream::in);
      ofs.open("MSS_Results.txt", std::fstream::out);
      if(ifs && ofs){
         //std::cout << "MSS_Problems.txt and MSS_Results.txt opened!" << std::endl;
      } else {
         std::cout << "Failed to open necessary files: MSS_Problems.txt, MSS_Results.txt" << std::endl;
         return -1;
      }
   }

   int problemCount = 1;       //Counts Test Data Sets

   //While not at and of input file
   while(!ifs.eof()){

      //Get next line of data as string
      std::string sInput;
      if(!(getline(ifs, sInput)))
		   break;


      if(MSS_TEST){
         std::cout << "\n+-----------Problem #" << problemCount << "---------------+";
         std::cout << "\n\nTest Set: " << sInput << "\n" << std::endl;
      } else {
         ofs << "\n+-----------Problem #" << problemCount << "---------------+";
         ofs << "\n\nTest Set: " << sInput << "\n" << std::endl;
      }


      //Create a stringstream for sInput
      std::stringstream ssIn;
      ssIn.str(sInput);

      //Read in all integers from sInput
      int temp;
      while(ssIn.good()){
         ssIn >> temp; 

         if(ssIn.fail()){
            ssIn.clear();
            ssIn.get();   //Remove '[', ',', and ']' characters
         } else {
            testVals.push_back(temp); //Add ints to testVals
         }
      }

      //Run enumeration algorithm
      int startInd, endInd, maxSum;
      enumeration(testVals, startInd, endInd, maxSum);
      std::vector<int> result;
      for(int i = startInd; i <= endInd; i++){
          result.push_back(testVals[i]);
      }
      if(MSS_TEST){
         printVect(result);
         std::cout << "Max Sum = " << maxSum << std::endl;
      } else {
	 ofs << "---Enumeration---" << std::endl;
         printResults(ofs, result);
         ofs << "Max Sum = " << maxSum << std::endl << std::endl;
      }
      result.clear();
      
      //Run enumeration2 algorithm
      enumeration2(testVals, startInd, endInd, maxSum);
      for(int i = startInd; i <= endInd; i++){
          result.push_back(testVals[i]);
      }
      if(MSS_TEST){
         printVect(result);
         std::cout << "Max Sum = " << maxSum << std::endl;
      } else {
	 ofs << "---Better Enumeration---" << std::endl;
         printResults(ofs, result);
         ofs << "Max Sum = " << maxSum << std::endl << std::endl;
      }
      result.clear();
       
      //Run Divide and Conquer
      struct maxSubData res = divAndConq(testVals, 0, testVals.size()-1);
      for(int i = res.low; i <= res.high; i++){
          result.push_back(testVals[i]);
      }
      if(MSS_TEST){
         printVect(result);
         std::cout << "Max Sum = " << res.maxSum << std::endl;
      } else {
	 ofs << "---Divide and Conquer---" << std::endl;
         printResults(ofs, result);
         ofs << "Max Sum = " << res.maxSum << std::endl << std::endl;
      }
      result.clear();

     
      //Run linearTime algorithm
      result = linearTime(testVals);
      if(MSS_TEST){
         printVect(result);
         std::cout << "Max Sum = " << maxSum << std::endl;
      } else {
	 ofs << "---Linear Time---" << std::endl;
         printResults(ofs, result);
         ofs << "Max Sum = " << sumVector(result) << std::endl << std::endl;
      }
      result.clear();
      
      testVals.clear();
      problemCount++;
   }
   
   ifs.close();
   return 0;
}

void printVect(std::vector<int>& input){

   if(input.empty()){
      return;
   }

   std::cout << "[";

   for(int i = 0; i < input.size()-1; i++){
      std::cout << input[i] << ", ";
   }

   std::cout << input[input.size()-1] << "]" << std::endl;
   return;
}

int sumVector(std::vector<int>& input){
   int sum = 0;
   for(int i = 0; i < input.size(); i++){
     sum += input[i];
   }
   return sum;
}

void printResults(std::ofstream& ofs, std::vector<int>& input){

   if(input.empty()){
      return;
   }

   ofs << "[";

   for(int i = 0; i < input.size()-1; i++){
      ofs << input[i] << ", ";
   }

   ofs << input[input.size()-1] << "]" << std::endl;
   return;
}

/**************************************************************************************
*            						enumeration
* Description: Finds the maximum subarray using an enumeration algorithm. Changes
* the start index, end index, and max sum parameters based on algorithm.
* Parameters:
*	vector<int> array: Provided array of values
*	int startInd: The starting index variable to set, changed in function
*	int endInd: The ending index variable to set, changed in function
*	int maxSum: Maximum sum variable to set, changed in function
**************************************************************************************/
void enumeration(std::vector<int>& array, int &startInd, int &endInd, int &maxSum)
{
	int sum, first, last;
	int max = 0;
	int n = array.size();
	
	//Loop through all subarrays and find sum
	//Starting index control
	for(int i = 0; i < n; i++)
	{
		
		if (i != (n-1))
		{
			//Ending index control
			for(int j = i; j < n; j++)
			{
				sum = 0;
				//Sum all values within specified index
				for (int k = i; k <= j; k++)
					sum += array.at(k);
				
				//Compare sum to see if it's max and set indices
				if (max < sum)
				{
					max = sum;
					first = i;
					last = j;
				}
			}
		}
		else
		{
			//If last element in array, sum is that element value
			sum = array.at(i);
			//Compare sum to see if it's max and set indices 
			if (max < sum)
			{
				max = sum;
				first = i;
				last = i;
			}
		}
	}
	
	//Set maximum sum, the start index, and end index of the maximum subarray
	maxSum = max;
	startInd = first;
	endInd = last;
}

/**************************************************************************************
*            						enumeration2
* Description: Finds the maximum subarray using an improved enumeration algorithm. Changes
* the start index, end index, and max sum parameters based on algorithm.
* Parameters:
*	vector<int> array: Provided array of values
*	int startInd: The starting index variable to set, changed in function
*	int endInd: The ending index variable to set, changed in function
*	int maxSum: Maximum sum variable to set, changed in function
**************************************************************************************/
void enumeration2(std::vector<int>& array, int &startInd, int &endInd, int &maxSum)
{
	int sum, first, last;
	int max = 0;
	int n = array.size();
	
	//Loop through all subarrays and find sum
	//Starting index control
	for(int i = 0; i < n; i++)
	{
		sum = 0;
		if (i != (n-1))
		{
			//Loop through remaining elements of array based on starting point
			for(int j = i; j < n; j++)
			{
				sum += array.at(j);
				//Compare sum to see if it's max and set indices
				if (max < sum)
				{
					max = sum;
					first = i;
					last = j;
				}
			}
		}
		else
		{
			//If last element in array, sum is that element value. Compare for max and set indices
			if (max < array.at(i))
			{
				max = array.at(i);
				first = i;
				last = i;
			}
		}
	}
	
	//Set maximum sum, the start index, and end index of the maximum subarray
	maxSum = max;
	startInd = first;
	endInd = last;
}

/******************************************************************
 *                        linearTime
 * Description: This function finds the max subarray in a vector in
 *     linear time. It returns a vector of the max subarray.
 * Pre-Conditions: Initialized vector<int> is passed to function
 * Post-Conditions: Returns max subarray as new vector
 * Parameters: 
 *     std::vector<int>& input - The input vector to find max subarray
 ******************************************************************/
std::vector<int> linearTime(std::vector<int>& input){

   int maxSum = 0;                  //Max subarray sum
   int curSum = 0;                  //Current subarray sum

   int lowBound = 0;                //Lower index of max subarray
   int tLB = lowBound;              //Temporary low bound marker
   int highBound = input.size()-1;  //High index of max subarray
   int tHB = highBound;             //Temporary high bound marker

   //For each element:
   for(int i = 0; i < input.size(); i++){
      //Save previous current sum for state information
      int prevCurSum = curSum;
      
      //Current sum at index must be increasing for max subarray
      curSum = std::max(0, curSum + input[i]);
      //If curSum is greater than maxSum, set maxSum to curSum
      maxSum = std::max(maxSum, curSum);

      //If previous curSum was 0, partition a new temp subarray
      if(prevCurSum == 0){
         tLB = i;
      }

      //If curSum of subarray is maxSum, set tHB
      if(i < input.size() && curSum == maxSum){
         tHB = i;
      }

      //If tLB gets set and tHB hasn't been set, set tHB
      if(tHB < tLB){
         tHB = tLB;
      }

      //If sum of current subarray is maxSum, store indices
      if(curSum == maxSum){
         lowBound = tLB;
         highBound = tHB;
      }

   }

   //Build return vector from indices
   std::vector<int> retVect;
   for(int i = 0; i <= highBound - lowBound; i++){
      retVect.push_back(input[lowBound + i]);
   }

   return retVect;
}

/***********************************************
 *          divideConquer()
 * Description: this function calculates the 
 * maximum sum of a subarray using divide and
 * conquer algorithm.
 * Parameters:
 * vector<int> input: array of numbers provided
 * vector<int> subarray: part of the input array
 * sum: maximum sum of the subarray
************************************************/
struct maxSubData _maxSubCross(std::vector<int>& in, int l, int m, int h){

   int curSum = 0;

   int leftSum =0;
   int maxLeft = m+1;

   for(int i = m; i >= l; i--){
      curSum += in[i];
      if(curSum > leftSum){
         leftSum = curSum;
         maxLeft = i;
      }
   }

   curSum = 0;

   int rightSum = 0;
   int maxRight = m;

   for(int i = m+1; i <= h; i++){
      curSum += in[i];
      if(curSum > rightSum){
         rightSum = curSum;
         maxRight = i;
      }
   }

   struct maxSubData ret;
   ret.maxSum = leftSum + rightSum;
   ret.low = maxLeft;
   ret.high = maxRight;

   return ret;
}

struct maxSubData divAndConq(std::vector<int>& in, int l, int h){

   if(l == h){
      struct maxSubData t;
      t.maxSum = in[l];
      t.low = l;
      t.high = l;
      return t;
   } else {

      struct maxSubData t1, t2;

      t1 = divAndConq(in, l, (h + l)/2);
      t2 = divAndConq(in, (h + l)/2+1, h);

      if(t1.maxSum >= 0 && t2.maxSum >= 0){
         struct maxSubData t3 = _maxSubCross(in, l, (h + l)/2, h);

         if(t3.maxSum > t1.maxSum && t3.maxSum > t2.maxSum){
            return t3;
         }
         
         return (t1.maxSum > t2.maxSum) ? t1 : t2;
      } else {
	 return (t2.maxSum > t1.maxSum) ? t2 : t1;
      }
   }
}
