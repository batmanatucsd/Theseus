#ifndef HEADER_H
#define HEADER_H

#ifdef MAIN
#define EXTERN 
#else
#define EXTERN extern 
#endif

#include <vector>
#include <queue>
#include "Node.h"

#define ROWS 16
#define COLS 16
#define COST 1
#define GOAL ROWS*(ROWS/2)+COLS/2

#define FS 0 // front sensor index
#define LS 1 // left sensor index
#define RS 2 // right sensor index 

//#define _INPUT_ANALOG INPUT_ANALOG

/************************************************/
/*************** Global Variables ***************/ 
/************************************************/
// making these variables global
EXTERN std::vector<Node> maze;

// adjustments for adjacent nodes
// 0-3: NEWS, 4-7: diagnols
EXTERN char neighbors[4]; // NORTH, EAST, SOUTH, WEST
EXTERN byte head, currentCell, nextCell;



void setWall(byte, byte cell=currentCell);
void setMaze(std::vector<Node> &);
void setHValues(byte);
void resetGValues();
void resetParents();
void resetVisited();
void findShortestPath();
void mapMaze();

// Function to check for the walls
// In the real machine, check the sensors for the walls
// This function will call setWall() in Maze.hpp 
// to update the maze with the correct wall information
void checkForWalls();

class CompareNodes {

  public:
  //  bool operator() (const byte  & lhs, const byte & rhs) const; 
    bool operator() (const byte & lhs, const byte & rhs) const {
    // lowest f value gets the highest priority
    // > means smaller values get higher priority
    // < means higher values get higher priority
    if(maze[lhs].getF() > maze[rhs].getF()) 
        return true;
    else if(maze[lhs].getF() < maze[rhs].getF()) 
        return false;
    else // if the f values are equal use h values to break the tie
        return maze[lhs].getH() > maze[rhs].getH();
    }
};

#endif // HEADER_H
