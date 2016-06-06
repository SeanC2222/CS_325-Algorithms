#include <cmath>
#include "coordpair.hpp"


CoordPair::CoordPair(){
    this->x = 0;
    this->y = 0;
}

CoordPair::CoordPair(int a, int b){
    this->x = a;
    this->y = b;
}

CoordPair CoordPair::operator+(const CoordPair &cP){
    CoordPair retVal(this->x + cP.x, this->y + cP.y);
    return retVal;
}

CoordPair CoordPair::operator-(const CoordPair &cP){
    CoordPair retVal(this->x - cP.x, this->y - cP.y);
    return retVal;
}

CoordPair CoordPair::operator=(const CoordPair &cP){
    this->x = cP.x;
    this->y = cP.y;
    return *this;
}

int CoordPair::getX(){return this->x;}
int CoordPair::getY(){return this->y;}

int CoordPair::getMagnitude(){
    return (int)(sqrt(pow(this->x,2.0) + pow(this->y, 2.0)) + 0.5);
}
