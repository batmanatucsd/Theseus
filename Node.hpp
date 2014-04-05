#ifndef NODE_HPP
#define NODE_HPP

class Node {
  public:
    int f=0, g=0, h=0;
    char walls=0;
    
    // setters for the walls
    void setNorth() { walls = walls | 1; }
    void setSouth() { walls = walls | (1 << 2); }
    void setEast() { walls = walls | (1 << 4); }
    void setWest() { walls = walls | (1 << 6); }

    // getters for the walls
    bool getNorth() const {return walls & 1;}
    bool getSouth() const {return walls & (1 << 2);}
    bool getEast() const {return walls & (1 << 4);}
    bool getWest() const {return walls & (1 << 6);}

    // getters for the f, g, h
    int getF() const {return f;}
    int getG() const {return g;}
    int getH() const {return h;}

    // setters for the f, g, h
    void setF(int newF) {f = newF;}
    void setG(int newG) {g = newG;}
    void setH(int newH) {h = newH;}
};

#endif // NODE_HPP
