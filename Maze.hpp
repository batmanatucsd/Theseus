#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include "Node.hpp"

#define rows 16
#define cols 16 

#define NORTH 0
#define EAST 1
#define WEST 2
#define SOUTH 3

/************************************************/
/*************** Global Variables ***************/ 
/************************************************/
std::vector<Node> maze;
// adjustments for adjacent nodes
// 0-3: NESW, 4-7: diagnols
char neighbors[4] = {cols, 1, -1, -cols}; // Front, Right, Left

/************************************************/
/************ Function Declarations *************/ 
/************************************************/
void setMaze(std::vector<Node> &);
void setHValues();
void findShortestPath();

// Compare class for priority queue in shortest path finding algorithm
class CompareNodes {
  public:
  bool operator() (const byte  & lhs, const byte & rhs) const {
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

// template class for priority_queue with find 
template<class T,
         class Container=std::vector<T>, 
         class Compare=std::less<typename Container::value_type>>
class priority_queue : public std::priority_queue<T, Container, Compare> {
  public:
    typedef typename
      std::priority_queue<T, Container, 
                          Compare>::container_type::const_iterator const_iterator;

    const_iterator find(const T& val) const {
      // return std::find(this->c.begin(), this->c.end());
      auto first = this->c.cbegin();
      auto last = this->c.cend();
      while(first != last) {
        if(*first == val) return first; 
        ++first;
      }
      return last;
    }

    const_iterator end() const {
      // return iterator passed the last element
      return this->c.cend();
    }
};

/************************************************/
/************* Function Definitions *************/ 
/************************************************/
// Constructor
void setMaze(std::vector<Node> & newMaze) {
  maze = newMaze; 

  //maze[0].setEast(); // set east wall of starting cell
  //maze[0+neighbors[EAST]].setWest();

  // set walls around the boarders
  for(byte r=0; r<rows; ++r) {
    maze[cols*r].setWest(); // set WEST wall
    maze[cols*r+cols-1].setEast(); // set EAST wall
  }

  for(byte c=0; c<cols; ++c) {
    maze[c].setSouth(); // set South wall
    maze[cols*(rows-1) + c].setNorth(); // set North wall
  }
}

// Fill h values
// h = current to finish node
void setHValues() {
  // h = 10 * (abs(currentRow - rows/2) + abs(currentCol - cols/2));
  for(int index=0; index<rows*cols; ++index) {
    int currentRow = index/cols, currentCol = index%cols;
    maze[index].setH(abs(currentRow-rows/2) + abs(currentCol-cols/2));
    /*
    if(currentRow >= rows/2 && currentCol >= cols/2) { // QI
      maze[index].setH(currentRow + currentCol - cols);

    } else if(currentRow >= rows/2 && currentCol < cols/2) { // QII
      maze[index].setH(currentRow - currentCol - 1);

    } else if(currentRow < rows/2 && currentCol < cols/2) { // QIII
      maze[index].setH(rows - 2 - currentRow - currentCol);

    } else if(currentRow < rows/2 && currentCol >= cols/2) { // QIV
      maze[index].setH(currentCol - currentRow - 1);
    }
    */
  }
}


// Fill g values for neighbors
// g = distance from previous node 
void setGValues(byte currentRow, byte currentCol) {
       
}

// functions for setting up walls
void setNorth(byte cell) {
  maze[cell].setNorth(); maze[cell+neighbors[NORTH]].setSouth();
}
void setEast(byte cell) {
  maze[cell].setEast(); maze[cell+neighbors[EAST]].setWest();
}
void setWest(byte cell) {
  maze[cell].setWest(); maze[cell+neighbors[WEST]].setEast();
}
void setSouth(byte cell) {
  maze[cell].setSouth(); maze[cell+neighbors[SOUTH]].setNorth();
}


void findShortestPath() {
  //std::priority_queue <byte, std::vector<byte>, CompareNodes> queue; // open list
  priority_queue<byte, std::vector<byte>, CompareNodes> queue; // open list

  queue.push(0);
  maze[0].setG(0); // set g value of the start

  byte current, neighbor;
  Node *currentNode, *neighborNode;
  int newG;


    ///////// DEBUG MESSAGE ///////////////
    //if(queue.top() == 1)
    std::cout << "this is the first one: " <<  queue.top() << std::endl;

  while(!queue.empty()) {
    current = queue.top();

    // if the current is the finish node
    //if(current == rows*rows/2+cols/2) {
      // found the destination, end search 
    //}
    queue.pop(); // remove current node from the queue

    currentNode = &maze[current];
    currentNode->visit(); // add current node to closed list

    ///////// DEBUG MESSAGE ///////////////
    std::cout << "i'm here and CURRENT: " << (int) current << std::endl;

    // loop through all its neighbor
    for(byte next=0; next<4; ++next) {
      // getting a valid neigbor
      switch(next) {
        case NORTH:
          if(currentNode->getNorth())
            continue; // if there is a wall, skip adjacent to NORTH
          break;
        case EAST:
          if(currentNode->getEast())
            continue; // if there is a wall, skip adjacent to EAST 
          break;
        case WEST:
          if(currentNode->getWest())
            continue; // if there is a wall, skip adjacent to WEST
          break;
        case SOUTH:
          if(currentNode->getSouth())
            continue; // if there is a wall, skip adjacent to WEST
          break;
      }

      neighbor = current + neighbors[next]; // else get neighbor 
      neighborNode = &maze[neighbor]; // get neighbor node

      // if the finish node is found
      if(neighbor == rows*(rows/2)+cols/2) {

        ///////// DEBUG MESSAGE ///////////////
        std::cout << "this is final node: " << (int) neighbor << " " <<  rows*(rows/2)+cols/2 << std::endl;
        // just set the parent of the neighbor
        // and then finish the algorithm
        neighborNode->setParent(current);
        std::cout << "this is the parent of final node: " << (int) neighborNode->getParent() << std::endl;
        return;
      }

      // if the neigbor is in closed list
      // don't do anything, and continue
      if(neighborNode->isVisited())
        continue;

      // evaluate new g value
      newG = currentNode->getG() + neighborNode->getG();

      // REMINDER: queue holds indices of nodes
      //           Type of neighbor is byte
      //           Type of neighborNode is Node
      bool isInOpen = queue.find(neighbor) != queue.end() ? true : false;
      
    ///////// DEBUG MESSAGE ///////////////
    std::cout << "             neighbor: " << (int) neighbor; 

      // if the neighbor is in open OR 
      // the new g value is smaller than the old g value
      if(!isInOpen || newG < currentNode->getG()) {

    ///////// DEBUG MESSAGE ///////////////
    std::cout << "  updating the neighbor"; 

        neighborNode->setParent(current); // set parent
        neighborNode->setG(newG); // set new g value

        // check if the neighbor is in open set
        // if not, add the neighbor into the open set
        if(!isInOpen) {
          queue.push(neighbor); 
        }
      }
      std::cout << std::endl;
    } // loop for all the neighbor
    
  } // end a* algorithm

}


#endif //MAZE_HPP
