#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <chrono>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <ctime>

#include "coordpair.hpp"

#define TIME_LIMIT 177   //3 minutes - 2 seconds to finish run

int distanceBetween(CoordPair& a, CoordPair& b){
    return (a - b).getMagnitude();
}

void buildCoordPairSet(std::string filename, std::vector< std::pair<int, CoordPair> > &v){
    std::ifstream file(filename.c_str(), std::ifstream::in);
   if(!file.is_open()){
      std::cout << "Can't open file " << filename << std::endl;
      exit(-1);
   }
    int i, x, y;
    while(file >> i >> x >> y){
        v.push_back(std::pair<int, CoordPair>(i, CoordPair((double)x, (double)y)));
    }
}

void swapVecInd(std::vector< std::pair<int, CoordPair> > &v, int a, int b){
    std::pair <int, CoordPair> temp = v[a];
    v[a] = v[b];
    v[b] = temp;
    return;
}



/**
 * This algorithm combines the computational time of TSP3.cpp
 * with algorithm 2's best outcomes. This limits the computation
 * to ~TIME_LIMIT seconds. Once TIME_LIMIT is exceeded for
 * large n, computation stops and the best outcome is saved.
 * 
 * Starting locations for large enough n are selected randomly from
 * the range of possible starting indices. The greedy algorithm
 * is then run from that start location. This is repeated for
 * as many start locations as can complete in TIME_LIMIT.
 * 
 * This might be a winner, I'm not sure. I haven't tried any 
 * of the other creative solutions that have been researched.
 * 
 * It does come up with the best numbers of anything posted
 * */
int main(int argc, char* argv[]){
    std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();
    std::vector< std::pair<int, CoordPair> > original;
    std::string inputFile(argv[1]);
    buildCoordPairSet(inputFile, original);
    
    std::vector< std::pair<int, CoordPair> > shortestTSP = original;
    int shortestDistance = INT_MAX;
    
    std::vector< std::pair<int, CoordPair> > pairs = original;

    
    std::vector<int> triedAlready;
    for(int i = 0; i < original.size(); i++){
        triedAlready.push_back(i);
    }
    
    srand(time(NULL));

    time_t stop = time(NULL) + (TIME_LIMIT);
    time_t curTime = time(NULL);
    while(curTime < stop && triedAlready.size()){
        curTime = time(NULL);
        pairs = original;
        int randStart = rand() % triedAlready.size();
        swapVecInd(pairs, 0, triedAlready[randStart]);
        triedAlready.erase(triedAlready.begin() + randStart);
        for(int i = 0; i < pairs.size()-1; i++){
            int closestIndex = i+1;
            int closest = INT_MAX;
            for(int j = i+1; j < pairs.size(); j++){
                int temp = distanceBetween(pairs[j].second, pairs[i].second);
                if(temp < closest){
                    closest = temp;
                    closestIndex = j;
                }
            }
            if(closestIndex != i+1){
                swapVecInd(pairs, closestIndex, i+1);
            }
        }
        int dist = 0;
        for(int i = 1; i < pairs.size(); i++){
            dist += distanceBetween(pairs[i].second, pairs[i-1].second);
        }
        dist += distanceBetween(pairs[pairs.size()-1].second, pairs[0].second);

        if(dist < shortestDistance){
            shortestDistance = dist;
            shortestTSP = pairs;
        }
        
    }
    //std::cout << "Size left: " << triedAlready.size() << std::endl;
    std::cout << "Total Distance: " << shortestDistance << std::endl;
    std::string outputFile("sol.tsp6." + inputFile.substr(0, 3)+ inputFile.at(inputFile.size()-5) + ".txt");
    std::ofstream sol(outputFile.c_str(), std::ofstream::out);
    sol << shortestDistance << std::endl;
    for(int i = 0; i < shortestTSP.size(); i++){
        sol << shortestTSP[i].first << std::endl;
    }
    sol.close();
    std::chrono::high_resolution_clock::time_point stopTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> totalTime = std::chrono::duration_cast<std::chrono::duration<double>>(stopTime - startTime);
    std::cout << totalTime.count() << std::endl;
    return 0;
}
