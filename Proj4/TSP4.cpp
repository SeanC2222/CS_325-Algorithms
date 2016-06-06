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

#define TIMES_AROUND 100000
#define DIST_AHEAD 10

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
 * This algorithm starts by walking the TSP path and checking
 * if the distance from the current city to the next city is
 * the shortest distance of the subsequent DIST_AHEAD cities. 
 * For example if 0->1 is the smallest distance of {0->2, 0->3,
 * 0->4, ... 0->DIST_AHEAD-1, 0->DIST_AHEAD}. The path is rearranged to put
 * the closest index next and then moves to it. 
 * 
 * The algorithm walks the path, adjusting it as it goes,
 * TIMES_AROUND times to try to find an optimal path.
 * 
 * The idea is that by continually adjusting the path as it
 * walks it that the path should eventually approach an
 * optimal. 
 * 
 * Ends up being not so optimal. Like the random it keeps
 * reshuffling things when an optimal path may already be 
 * in place. Further, because the indices are swapped in the
 * same DIST_AHEAD sized frame a lot of the solutions don't
 * end up distributed as I thought. The indices tend to stay
 * near one another since they keep getting compared to generally
 * the same set of indices.
 * 
 * The "walking" of the path seems like an interesting prospect.
 * If we can walk an optimal path and only adjust the non-optimal
 * parts somehow this traversal could be an interesting method.
 * 
 * Time: O(DIST_AHEAD * (TIMES_AROUND*n) )
 **/

int main(int argc, char* argv[]){
    std::vector< std::pair<int, CoordPair> > original;
    std::string inputFile(argv[1]);
    buildCoordPairSet(inputFile, original);

    std::vector< std::pair<int, CoordPair> > pairs = original;

    int count = 0;
    int curLoc = 0;
    int nextInd = 0;
    for(int timesAround = 0; timesAround < TIMES_AROUND;){
        int closestIndex = (curLoc + 1) % pairs.size();
        int toNext = distanceBetween(pairs[curLoc].second, pairs[closestIndex].second);
        for(int i = 2; i < 2 + DIST_AHEAD; i++){
            nextInd = (curLoc + i) % pairs.size();
            int tempToNext = distanceBetween(pairs[curLoc].second, pairs[nextInd].second); 
            if(tempToNext < toNext){
                closestIndex = nextInd;
                toNext = tempToNext;
            }
        }
        if(closestIndex != (curLoc + 1) % pairs.size()){
            swapVecInd(pairs, closestIndex, (curLoc + 1) % pairs.size());
            count = 0;
        } else {
            count++;
        }
        curLoc = ++curLoc % pairs.size();
        if(curLoc == 0){
            timesAround++;
        }
    }
    
    int dist;
    for(int i = 1; i < pairs.size(); i++){
        dist += distanceBetween(pairs[i].second, pairs[i-1].second);
    }
    dist += distanceBetween(pairs[pairs.size()-1].second, pairs[0].second);


    std::cout << "Total Distance: " << dist << std::endl;
    std::string outputFile("sol.tsp4." + inputFile.substr(0, 3)+ inputFile.at(inputFile.size()-5) + ".txt");
    std::ofstream sol(outputFile.c_str(), std::ofstream::out);
    sol << dist << std::endl;
    for(int i = 0; i < pairs.size(); i++){
        sol << pairs[i].first << std::endl;
    }
    sol.close();
    return 0;
}
