#ifndef COORDPAIR_HPP
#define COORDPAIR_HPP

class CoordPair{
    
private:
    int x;
    int y;

public:
    CoordPair();
    CoordPair(int, int);
    CoordPair operator+(const CoordPair&);
    CoordPair operator-(const CoordPair&);
    CoordPair operator=(const CoordPair&);
    int getX();
    int getY();
    int getMagnitude();
};

#endif
