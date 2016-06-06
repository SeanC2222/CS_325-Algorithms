#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <chrono>

void enumeration(std::vector<int>&);
void enumeration2(std::vector<int>&);
void linearTime(std::vector<int>&);

struct maxSubData{
   public:
      int maxSum;
      int low;
      int high;
};
struct maxSubData divAndConq(std::vector<int>&, int, int);
struct maxSubData _maxSubCross(std::vector<int>&, int, int, int);


int main()
{
	std::ofstream outputFile;
	std::vector<int>input;
	std::chrono::duration<double> timeDiff;
	int userN, userAlg;
	unsigned seed;
	int loop = 10;  //number of data points for analysis at each input size
	
	//Set seed for random function
	seed=time(0);
	srand(seed);
	
	//Initialize timing mechanism
	auto start = std::chrono::high_resolution_clock::now();
	auto end = std::chrono::high_resolution_clock::now();
	
	//Open output file
	outputFile.open("Time_Results.txt");
	if(outputFile){
         std::cout << "Output file opened!" << std::endl;
     } 
	 else {
         std::cout << "Failed to open output file!" << std::endl;
         return -1;
     }
	
	do
	{
		//Get user input
		std::cout << "How many elements are in your array? ";
		std::cin >> userN;
		std::cout << "Select an algorithm to use:" <<  std::endl;
		std::cout << "1) Enumeration   2) Better Enumeration   3) Divide and Conquer   4) Linear   5) Quit" << std::endl;
		std::cin >> userAlg;
		if (userAlg != 5)
		{
			//Print algorithm name and n to output file
			switch(userAlg)
			{
				case 1: outputFile << "1) Enumeration\t" << userN << "\t";
						break;
				case 2: outputFile << "2) Better Enumeration\t" << userN << "\t";
						break;
				case 3: outputFile << "3) Divide and Conquer\t" << userN << "\t";
						break;
				case 4: outputFile << "4) Linear\t" << userN << "\t";
						break;
			}
			
			//Set range for random numbers
			int high = userN;
			int low = -1 * userN;
			
			//Loop through create new random array and running algorithm, write time to output file
			for (int i = 0; i < 10; i++)
			{
				//Populate random array
				for (int j = 0; j < userN; j++)
					input.push_back(rand() % (high - low + 1) + low);
				
				//Start time
				start = std::chrono::high_resolution_clock::now();
				//Run algorithm
				switch(userAlg)
				{
					case 1: enumeration(input);
							break;
					case 2: enumeration2(input);
							break;
					case 3: divAndConq(input,0, input.size()-1);
							break;
					case 4: linearTime(input);
							break;
					default: std::cout << "Not a valid algorithm selection" << std::endl;
				}
				//End Time
				end = std::chrono::high_resolution_clock::now();
				timeDiff = end - start;
				outputFile << timeDiff.count() << "\t";
				
				//Clear array
				input.clear();
			}
			
			outputFile << "\n";
		}
	}while(userAlg != 5);
	
	//Close output file
	outputFile.close();
	
	return 0;
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
void enumeration(std::vector<int>& array)
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
	
/*	//Set maximum sum, the start index, and end index of the maximum subarray
	maxSum = max;
	startInd = first;
	endInd = last;*/
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
void enumeration2(std::vector<int>& array)
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
	
/*	//Set maximum sum, the start index, and end index of the maximum subarray
	maxSum = max;
	startInd = first;
	endInd = last;*/
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
void linearTime(std::vector<int>& input){

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
   /*std::vector<int> retVect;
   for(int i = 0; i <= highBound - lowBound; i++){
      retVect.push_back(input[lowBound + i]);
   }

   return retVect;*/
}


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
         
      } else if (t1.maxSum > t2.maxSum){
         return t1;
      } else if (t1.maxSum < t2.maxSum){
         return t2;
      } else {
         return t1;
      }
   }
}