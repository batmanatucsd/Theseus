#ifndef NODE_H
#define NODE_H

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

typedef unsigned char byte;

class Node {
  public:
    /********** Member Variables **********/
    int f, g, h;
    byte parent;
    byte info;
    
    /********** Member Functions **********/
    // North East West South Visited
    // info bit 001VSWEN
    // setters for the walls 
    void setNorth() { info = info | 0x01; }
    void setEast() { info = info | 0x02; }
    void setWest() { info = info | 0x04; }
    void setSouth() { info = info | 0x08; }

    // getters for the walls 
    bool getWall(byte wall) const {
      switch(wall) {
        case NORTH: return info & 0x01;
        case EAST: return info & 0x02;
        case WEST: return info & 0x04;
        case SOUTH: return info & 0x08;
        default: return true;
      }
    }
    
    // getters and setters for visited bit
    void visit() {info = info | 0x10;}
    void unVisit() {info = info & 0xef;}
    bool isVisited() const {return info & 0x10;}

    // getters and setters for visited bit
    void map() {info = info | 0x20;}
    bool isMapped() const {return info & 0x20;}
    
    // getters and setters for visited bit
    void putInOpen() {info = info | 0x40;}
    void removeFromOpen() {info = info & 0xbf;}
    bool isInOpen() const {return info & 0x40;}

    // f = g + h
    // h = distance from current to finish node
    //   Manhattan Heuristic: h = 10(|r-t|+|c-t|)
    // g = distance from previous node
    // getters for the f, g, h
    int getF() const {return f;}
    int getG() const {return g;}
    int getH() const {return h;}

    // setters for the f, g, h
    void setF() {f = g+h;}
    void setF(byte newF) {f = newF;}
    void setG(int newG) {g = newG; setF();}
    void setH(int newH) {h = newH; setF();}

    // getter and setter for parent = index for maze
    byte getParent() const {return parent;}
    void setParent(byte newParent) {parent = newParent;}
};

#endif // NODE_H
