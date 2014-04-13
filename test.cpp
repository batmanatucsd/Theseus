
#include <iostream>
#include "Board.hpp"

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
  
  Board board;

  board.setHValues();
  
  for(int i=0; i<16*16; ++i) {
    cout << " h = " << board.maze->at(i).getH() << "  ";
    if(i%16 == 15) 
      cout << endl;
  }
  return 0;
}
