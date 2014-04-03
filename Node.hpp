#ifndef NODE_HPP
#define NODE_HPP

#define SETNORTH(walls) walls | 1
#define SETSOUTH(walls) walls | (1 << 2)
#define SETEAST(walls) walls | (1 << 4)
#define SETWEST(walls) walls | (1 << 6)
#define GETNORTH(walls) 
#define GETSOUTH(walls)
#define GETEAST(walls)
#define GETWEST(walls)

#define
#define
#define
class Node {
  public:
    int f, g, h;
    char walls;
};

#endif // NODE_HPP
