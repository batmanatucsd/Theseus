#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include "Node.hpp"
#include "mouse.hpp"

#define ROWS 16
#define COLS 16 
#define COST 1
#define GOAL ROWS*(ROWS/2)+COLS/2

// making these variables global
extern std::vector<Node> maze;
extern const char neighbors[];
extern byte head, currentCell, nextCell;

/************************************************/
/************ Function Declarations *************/ 
/************************************************/
void setWall(byte, byte cell=currentCell);
void setMaze(std::vector<Node> &);
void setHValues(byte);
void resetGValues();
void resetParents();
void resetVisited();
void findShortestPath();
void mapMaze();

// Compare class for priority queue in shortest path finding algorithm
class CompareNodes {
  public:
  bool operator() (const byte  & lhs, const byte & rhs) const; 
};

#endif //MAZE_HPP
