#ifndef NODE_HPP
#define NODE_HPP

//#define INFINITY 999 

typedef unsigned char byte;

class Node {
  public:
    /********** Member Variables **********/
    int f=0, g=0, h=0;
    byte parent = 0;
    char walls = 0;
    
    /********** Member Functions **********/
    // setters for the walls
    // NEWS : b0000SWEN
    void setNorth() { walls = walls | 0x01; }
    void setEast() { walls = walls | 0x02; }
    void setWest() { walls = walls | 0x04; }
    void setSouth() { walls = walls | 0x08; }

    // getters for the walls
    bool getNorth() const {return walls & 0x01;}
    bool getEast() const {return walls & 0x02;}
    bool getWest() const {return walls & 0x04;}
    bool getSouth() const {return walls & 0x08;}

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
    void setG(int newG) {g = newG; setF();}
    void setH(int newH) {h = newH; setF();}

    // getter and setter for parent = index for maze
    byte getParent() const {return parent;}
    void setParent(byte newParent) {parent = newParent;}
};

#endif // NODE_HPP
