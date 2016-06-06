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
#include <cstring>

#include "coordpair.hpp"

#define BUF_SIZE 4096

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

int main(int argc, char* argv[]){
    std::vector< std::pair<int, CoordPair> > original;
    buildCoordPairSet(std::string(argv[1]), original);

    std::vector< std::pair<int, CoordPair> > pairs = original;

    std::vector< std::pair<int, CoordPair> > shortestTSP = original;
    int shortestDistance = INT_MAX;
    
    for(int start = 0; start < 10; start++){
        pairs = original;
        if(start){
            swapVecInd(pairs, 0, start);
        }
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

    std::cout << "Total Distance: " << shortestDistance << std::endl;
    std::ofstream sol("sol.txt", std::ofstream::out);
    sol << shortestDistance << std::endl;
    for(int i = 0; i < original.size(); i++){
        sol << shortestTSP[i].first << std::endl;
    }
    sol.close();
    return 0;
}
