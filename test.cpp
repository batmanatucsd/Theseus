
#include <iostream>
#include <stack>
#include <vector>
#include "Maze.hpp"

#include <ctime>

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

  // Initial Setup
  std::vector<Node> newMaze(256);  
  setMaze(newMaze); // set up Maze
  setHValues(); // set H values on maze
  

  /************************ DEBUG *****************************/
  /************** Printing out H values ***********************/
  for(int i=0; i<rows*cols; ++i) {
    cout << " h = " << maze[i].getH() << "  ";
    if(maze[i].getH()/10 == 0)
      cout << " ";
    if(i%rows == rows-1) 
      cout << endl;
  }

  /************************ DEBUG *****************************/
  /*************** Setting Up the Walls ***********************/

  setNorth(12);
  setEast(1);
  setNorth(7);
  setNorth(8);
  setNorth(9);
  setWest(9);
  setSouth(10);
  setEast(10);
  setWest(17);
  setEast(13);
  setEast(19);
  setNorth(20);
  setNorth(21);
  setEast(21);
  setNorth(25);
  setNorth(26);
  setEast(26);
  setEast(28);



  /************************ DEBUG *****************************/
  /*************** Getting Shortest Path **********************/

  clock_t time = clock();

  findShortestPath(); // find the shortest path when the maze is known

  time = clock() - time;
  std::cout << "elapsed time for a* algorithm: " << (float)time/CLOCKS_PER_SEC << std::endl;

  std::stack<byte> shortestPath;
  byte final = rows*(rows/2)+cols/2;
  Node currentNode = maze[final];
  byte parent = currentNode.getParent();


  std::cout << "the final node: " << rows*(rows/2)+cols/2 << std::endl;
  std::cout << "parent of the final node: " << (int) parent << std::endl;

  shortestPath.push(final);
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
