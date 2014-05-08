#include "mouse.hpp"

#include <iostream>

/************************************************/
/*************** Global Variables ***************/ 
/************************************************/
byte head = 0; // orientation
byte currentCell = 0; // the current cell that the mouse is in
byte nextCell; // the next cell the mouse is suppose to go
std::vector<Node> fakeMaze;

/************************************************/
/************* Function Definitions *************/ 
/************************************************/
void checkForWalls() {
  // TODO:
  std::cout << "check for walls" << std::endl;
  // check sensors using checkForWalls function
  // readSensor() // this is the real readSensor function
  readFakeSensor();
 
  //setWall(EAST);
  // set walls
}

void setFakeMaze(std::vector<Node>& realMaze) {
  fakeMaze = realMaze;
}
void readFakeSensor() {
  for(byte side=0; side<4; ++side) {
    if(fakeMaze[currentCell].getWall(side)) {
      std::cout << "i'm here" << std::endl;
      setWall(side); 
    }
  }
}

