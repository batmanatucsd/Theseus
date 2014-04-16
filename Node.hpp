#ifndef NODE_HPP
#define NODE_HPP

//#define INFINITY 999 

typedef unsigned char byte;

class Node {
  public:
    /********** Member Variables **********/
    int f=0, g=0, h=0;
    byte parent = 0;
    byte info = 0;
    
    /********** Member Functions **********/
    // North East West South Visited
    // info bit 000VSWEN
    // setters for the walls 
    void setNorth() { info = info | 0x01; }
    void setEast() { info = info | 0x02; }
    void setWest() { info = info | 0x04; }
    void setSouth() { info = info | 0x08; }

    // getters for the walls 
    bool getNorth() const {return info & 0x01;}
    bool getEast() const {return info & 0x02;}
    bool getWest() const {return info & 0x04;}
    bool getSouth() const {return info & 0x08;}
    
    // getters and setters for visited bit
    void visit() {info = info | 0x10;}
    bool isVisited() const {return info & 0x10;}

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
