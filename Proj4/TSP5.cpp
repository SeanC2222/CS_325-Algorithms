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
 * This algorithm is built to find the furthest distance
 * from the first city, and sets it at the "middle" of the
 * route. 
 * 
 * Array Index
 * 0...1....2....3....4....5....6....7....0
 * 1...2....3....4....5...b4...b3...b2....1
 * Route Index
 * 
 * The most efficient path that the TSP could take would be
 * a circle:
 *           5
 *        4    b4
 *      3        b3
 *        2    b2
 *           1
 * 
 * So if we put the furthest location at 5 and build 2
 * sub routes (one starting at our initial node and the other
 * at our farthest node) we'll hopefully get 2 smaller greedy
 * solutions that add to a more efficient path than the 
 * single greedy solution.
 **/
int main(int argc, char* argv[]){
    std::vector< std::pair<int, CoordPair> > original;
    std::string inputFile(argv[1]);
    buildCoordPairSet(inputFile, original);

    std::vector< std::pair<int, CoordPair> > pairs (original.size(), std::pair<int, CoordPair>(-1, CoordPair(0,0)));

    int furthest = 0;
    int furthInd = 0;
    for(int i = 1; i < original.size(); i++){
        int tempLen = distanceBetween(original[0].second, original[i].second);
        if(tempLen > furthest){
            furthest = tempLen;
            furthInd = i;
        }
    }
    
    int half = pairs.size()/2;
    pairs[0] = original[0];
    pairs[half] = original[0 + furthInd];
    
    original.erase(original.begin() + furthInd);
    original.erase(original.begin());
    
    int i = 0;
    while(original.size()){

        int fClosestDist[2] = {INT_MAX};
        int mClosestDist[2] = {INT_MAX};
        int fClosest[2] = {-1, -1};
        int mClosest[2] = {-1, -1};
        
        
        for(int j = 0; j < original.size(); j++){
            int fDist = distanceBetween(pairs[i].second, original[j].second);
            int mDist = distanceBetween(pairs[i + half].second, original[j].second);
            if(fDist < fClosestDist[0]){
                fClosestDist[1] = fClosestDist[0];
                fClosestDist[0] = fDist;
                fClosest[1] = fClosest[0];
                fClosest[0] = j;
            } else if(fDist < fClosestDist[1]){
                fClosestDist[1] = fDist;
                fClosest[1] = j;
            }
            if(mDist < mClosestDist[0]){
                mClosestDist[1] = mClosestDist[0];
                mClosestDist[0] = mDist;
                mClosest[1] = mClosest[0];
                mClosest[0] = j;
            } else if(mDist < mClosestDist[1]){
                mClosestDist[1] = mDist;
                mClosest[1] = j;
            }
        }
        
        int fNextInd = -1;
        int mNextInd = -1;
        
        if(fClosest[0] == mClosest[0]){
            int net1 = fClosestDist[0] + mClosestDist[1];
            int net2 = fClosestDist[1] + mClosestDist[0];
            if(net1 < net2){
                fNextInd = fClosest[0];
                mNextInd = mClosest[1];
            } else {
                fNextInd = fClosest[1];
                mNextInd = mClosest[0];
            }
        } else {
            fNextInd = fClosest[0];
            mNextInd = mClosest[0];
        }
        i++;
        pairs[i] = original[fNextInd];
        pairs[i+half] = original[mNextInd];
        if(fNextInd < mNextInd){
            original.erase(original.begin() + mNextInd);
            original.erase(original.begin() + fNextInd);
        } else {
            original.erase(original.begin() + fNextInd);
            original.erase(original.begin() + mNextInd);
        }
    }
    
    
    int dist;
    for(int i = 1; i < pairs.size(); i++){
        dist += distanceBetween(pairs[i].second, pairs[i-1].second);
    }
    dist += distanceBetween(pairs[pairs.size()-1].second, pairs[0].second);


    std::cout << "Total Distance: " << dist << std::endl;
    std::string outputFile("sol.tsp5." + inputFile.substr(0, 3)+ inputFile.at(inputFile.size()-5) + ".txt");
    std::ofstream sol(outputFile.c_str(), std::ofstream::out);
    sol << dist << std::endl;
    for(int i = 0; i < pairs.size(); i++){
        sol << pairs[i].first << std::endl;
    }
    sol.close();
    return 0;
}
