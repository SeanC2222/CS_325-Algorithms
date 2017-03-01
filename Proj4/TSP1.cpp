#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cfloat>

#include <cmath>
#include <cstdlib>

#include "coordpair.hpp"

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
/**
 * Simple greedy algorithm. Starts at the first index read
 * into the program, and selects and visits the next city
 * based on which unvisited city is closest. The "visited"
 * quality isn't explicitly tracked, visited cities are 
 * removed from the system by ordering.
 * 
 */
int main(int argc, char* argv[]){
    
    std::vector< std::pair<int, CoordPair> > pairs;
    std::string inputFile(argv[1]);
    buildCoordPairSet(inputFile, pairs);

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
            std::pair <int, CoordPair> temp = pairs[closestIndex];
            pairs[closestIndex] = pairs[i+1];
            pairs[i+1] = temp;
        }
    }
    int dist = 0;
    for(int i = 1; i < pairs.size(); i++){
        dist += distanceBetween(pairs[i].second, pairs[i-1].second);
    }
    dist += distanceBetween(pairs[pairs.size()-1].second, pairs[0].second);
    
    std::cout << "Total Distance: " << dist << std::endl;
    std::string outputFile("sol.tsp." + inputFile.substr(0, 3)+ inputFile.at(inputFile.size()-5) + ".txt");
    std::ofstream sol(outputFile.c_str(), std::ofstream::out);
    sol << dist << std::endl;
    for(int i = 0; i < pairs.size(); i++){
        sol << pairs[i].first << std::endl;
    }
    sol.close();
    return 0;
}
