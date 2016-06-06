nclude <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <cfloat>
#include <ctime>

#include "coordpair.hpp"

#define TIME_LIMIT 180   //3 minutes

int distanceBetween(CoordPair& a, CoordPair& b){
    return (a - b).getMagnitude();
}

void buildCoordPairSet(std::string filename, std::vector< std::pair<int, CoordPair> > &v){
    std::ifstream file(filename.c_str(), std::ifstream::in);
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
 * Random tester idea. The concept is to maximize work done within
 * the 3 minute time frame. The concept is that two indices, i and
 * j are randomly selected. i would be the index we're checking
 * and it is assumed that i+1 would be the next stop in the path.
 * If the distance from i to j is less than i to i+1, j and i+1
 * are swapped. 
 * 
 * The hope was that by maximizing the work done based on time,
 * we could reach the best output without going over our time
 * limit.
 * 
 * The outputs are horrible but the time frame idea is good.
 * 
 * Randomly picking indices only shuffles things over and over
 * and does not actually approach an optimal solution.
 * 
 * Time: ~180 seconds
 */

int main(int argc, char* argv[]){
    std::vector< std::pair<int, CoordPair> > original;
    std::string inputFile(argv[1]);
    buildCoordPairSet(inputFile, original);

    std::vector< std::pair<int, CoordPair> > pairs = original;

    srand(time(NULL));
    time_t curTime = time(NULL);
    time_t stop = time(NULL) + (TIME_LIMIT);
    
    int count = 0;
    while(curTime < stop && count < 100){
        curTime = time(NULL);
        int i = rand() % (pairs.size()-1); //Range: 0 - (size-2)
        int j = rand() % pairs.size();     //Range: 0 - (size-1)
        if(i == j) continue;               //If indices are equal
        if(distanceBetween(pairs[i].second, pairs[j].second) < distanceBetween(pairs[i].second, pairs[i+1].second)){
            swapVecInd(pairs, i+1, j);
            count = 0;
        } else {
            count++;
        }
    }
    
    int dist;
    for(int i = 1; i < pairs.size(); i++){
        dist += distanceBetween(pairs[i].second, pairs[i-1].second);
    }
    dist += distanceBetween(pairs[pairs.size()-1].second, pairs[0].second);


    std::cout << "Total Distance: " << dist << std::endl;
    std::string outputFile("sol.tsp3." + inputFile.substr(0, 3)+ inputFile.at(inputFile.size()-5) + ".txt");
    std::ofstream sol(outputFile.c_str(), std::ofstream::out);
    sol << dist << std::endl;
    for(int i = 0; i < pairs.size(); i++){
        sol << pairs[i].first << std::endl;
    }
    sol.close();
    return 0;
}
