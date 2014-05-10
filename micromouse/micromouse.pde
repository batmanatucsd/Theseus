#define MAIN

#include <stack>
#include "header.h"

//std::vector<byte> finalPath;
std::stack<byte> shortestPath;
Node currentNode; 
byte parent;
  
void setup() {

  // NORTH, EAST, SOUTH, WEST
  neighbors[0] = COLS;
  neighbors[1] = 1;
  neighbors[2] = -COLS;
  neighbors[3] = -1;
  
  // Initial Setup
  std::vector<Node> newMaze(256);  
  setMaze(newMaze); // set up Maze
  setHValues(GOAL); // set H values on maze

//  findShortestPath();
  mapMaze(); // mapping maze

  findShortestPath();
//  mapMaze();

 
 currentNode = maze[GOAL];
 parent = currentNode.getParent();

// get shortest path by following parent node
  shortestPath.push(GOAL);
  while(parent != 0) {
     shortestPath.push(parent); 
     currentNode = maze[parent];
     parent = currentNode.getParent();
  }
  shortestPath.push(parent);

attachInterrupts();
readSensors();

}

void loop() {
//  
//  delay(1000);
//  
//  
//    // get final path
//    while(!shortestPath.empty()) {
//     finalPath.push_back(shortestPath.top());
//      shortestPath.pop();
//
//    }
//  
//  
//
//
//  for(int i=0; i<finalPath.size(); ++i) {
//  }

//PID();
printEncoderTicks();
testPID();

}


