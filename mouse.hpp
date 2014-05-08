#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "maze.hpp"

#define FS 0 // front sensor index
#define LS 1 // left sensor index
#define RS 2 // right sensor index 

#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

void goStraight();

// Turns
void turnRight();
void turnLeft();
void turn180();

// Function to check for the walls
// In the real machine, check the sensors for the walls
// This function will call setWall() in Maze.hpp 
// to update the maze with the correct wall information
void checkForWalls();


// simulation methods:
void setFakeMaze(std::vector<Node>&);
void readFakeSensor();



#endif // MOUSE_HPP
