
#include <iostream>
#include <stack>
#include <vector>
#include "Maze.hpp"

using namespace std;

int main() {
  
 /*
  Node node;
  Node node2;

  node.setNorth();
  node.setNorth();

  if(node.getNorth())
    std::cout << "for node: north wall is set" << std::endl;

  if(node2.getNorth())
    std::cout << "for node2: north wall is set" << std::endl;
  else
    std::cout << "for node2: north wall is NOT set" << std::endl;


    Node maze[rows][cols];

    for(int i=0; i<rows; ++i) {
      for(int j=0; j<cols; ++j) {
        maze[i][j] = Node(); 
      }
    }

    maze[2][1].setEast();

    std::cout << maze[2][1].getEast() << std::endl;
    std::cout << maze[2][1].getNorth() << std::endl;

  */
  std::vector<Node> newMaze(256);  
  setMaze(newMaze); // set up Maze
  setHValues(); // set H values on maze
  
  findShortestPath(); // find the shortest path when the maze is known

  for(int i=0; i<rows*cols; ++i) {
    cout << " h = " << maze[i].getH() << "  ";
    if(maze[i].getH()/10 == 0)
      cout << " ";
    if(i%rows == rows-1) 
      cout << endl;
  }

  std::stack<byte> shortestPath;
  Node currentNode = maze[rows*(rows/2)+cols/2];
  byte parent = currentNode.getParent();


  std::cout << "the final node: " << rows*(rows/2)+cols/2 << std::endl;
  std::cout << "parent of the final node: " << (int) parent << std::endl;
  // get shortest path by following parent node
  while(parent != 0) {
    std::cout << "i'm here | finding shortest path" << std::endl;
     shortestPath.push(parent); 
     currentNode = maze[parent];
     parent = currentNode.getParent();
  }
  shortestPath.push(parent);

  std::cout << "The shortest path is: \n";
  while(!shortestPath.empty()) {
    std::cout << (int) shortestPath.top() << " ";
    shortestPath.pop();
  }

  std::cout << std::endl;
  return 0;
}
