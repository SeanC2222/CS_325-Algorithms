#include <cmath>
#include <iostream>
#include <chrono>

unsigned long long int fibIter(int n);
unsigned long long int fibRecur(int n);


int main(){

   int testValues [] = {10, 100, 1000, 10000, 50000, 100000, 200000, 500000, 1000000, 2000000, 5000000};
   int testValuesRecur [] = {5, 10, 15, 20, 30, 40, 45, 50, 51, 52, 53};
   unsigned long long int fib_num;
   
   for(int i = 0; i < 11; i++){
      std::cout << "+-------------------------+" << std::endl;
      std::cout << "     N = " << testValues[i] << std::endl;
      std::cout << "+-------------------------+" << std::endl;

      std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
      std::cout << "___Iteration___" << std::endl;
      fib_num = fibIter(testValues[i]);
      std::cout << fib_num << std::endl << std::endl;
      std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> runTime = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
      std::cout << runTime.count() << std::endl << std::endl;
   }

    for(int i = 0; i < 11; i++){
      std::cout << "+-------------------------+" << std::endl;
      std::cout << "     N = " << testValuesRecur[i] << std::endl;
      std::cout << "+-------------------------+" << std::endl;
  
      std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
      std::cout << "___Recursion___" << std::endl;
      fib_num = fibRecur(testValuesRecur[i]);
      std::cout << fib_num << std::endl << std::endl;
      std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> runTime = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
      std::cout << runTime.count() << std::endl << std::endl;
   }

   return 0;

}

unsigned long long int fibIter(int n){

   unsigned long long int fib_m = 0;
   unsigned long long int fib_n = 1;
   unsigned long long int fib_cur = 0; 

   for(int i = 1; i < n; i++){
      fib_cur = fib_n + fib_m;
      fib_m = fib_n;
      fib_n = fib_cur;
   }
   return fib_cur;
}

unsigned long long int fibRecur(int n){

   if(n == 0){
      return 0;
   } else if (n == 1){
      return 1;
   } else {
      return fibRecur(n-1) + fibRecur(n-2);
   }
}
