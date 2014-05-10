#include "maze.hpp"

/************************************************/
/*************** Global Variables ***************/ 
/************************************************/
std::vector<Node> maze;

// adjustments for adjacent nodes
// 0-3: NEWS, 4-7: diagnols
const char neighbors[] = {COLS, 1, -COLS, -1}; // NORTH, EAST, SOUTH, WEST

/************************************************/
/************ CompareNodes Function  ************/ 
/************************************************/
bool CompareNodes::operator() (const byte & lhs, const byte & rhs) const {

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

/************************************************/
/************* Function Definitions *************/ 
/************************************************/
void setMaze(std::vector<Node> & newMaze) {

  maze = newMaze; 
  setWall(EAST);

  // set walls around the boarders
  for(byte r=0; r<ROWS; ++r) {
    maze[COLS*r].setWest(); // set WEST wall
    maze[COLS*r+COLS-1].setEast(); // set EAST wall
  }

  for(byte c=0; c<COLS; ++c) {
    maze[c].setSouth(); // set South wall
    maze[COLS*(ROWS-1) + c].setNorth(); // set North wall
  }
}

// Fill h values
// h = current to finish node
// h = 10 * (abs(currentRow - ROWS/2) + abs(currentCol - COLS/2));
void setHValues(byte finish) {

  int row = finish/COLS, col = finish%COLS;

  // if H values are going to be these, get rid off local variables
  for(int index=0; index<ROWS*COLS; ++index) {
    int currentRow = index/COLS, currentCol = index%COLS;
    //maze[index].setH(abs(currentRow-row) + abs(currentCol-col));

    if(currentRow >= ROWS/2 && currentCol >= COLS/2) { // QI
      maze[index].setH(currentRow + currentCol - COLS);

    } else if(currentRow >= ROWS/2 && currentCol < COLS/2) { // QII
      maze[index].setH(currentRow - currentCol - 1);

    } else if(currentRow < ROWS/2 && currentCol < COLS/2) { // QIII
      maze[index].setH(ROWS - 2 - currentRow - currentCol);

    } else if(currentRow < ROWS/2 && currentCol >= COLS/2) { // QIV
      maze[index].setH(currentCol - currentRow - 1);
    }
  }
}



void setWall(byte wall, byte cell) {

  switch(wall) {

    case NORTH:
      maze[cell].setNorth(); maze[cell+neighbors[NORTH]].setSouth();
      return;
      
    case EAST:
      maze[cell].setEast(); maze[cell+neighbors[EAST]].setWest();
      return;

    case WEST:
      maze[cell].setWest(); maze[cell+neighbors[WEST]].setEast();
      return;

    case SOUTH:
      maze[cell].setSouth(); maze[cell+neighbors[SOUTH]].setNorth();
      return;
  }
}

void findShortestPath() {

  // reset values
  resetGValues();
  resetParents();
  resetVisited();

  //std::priority_queue <byte, std::vector<byte>, CompareNodes> queue; // open list
  std::priority_queue<byte, std::vector<byte>, CompareNodes> queue; // open list

  queue.push(0);
  maze[0].setG(0); // set g value of the start

  Node *currentNode, *neighborNode;
  int newG;

    ///////// DEBUG MESSAGE ///////////////
    //if(queue.top() == 1)
    std::cout << "this is the first one: " <<  queue.top() << std::endl;

  while(!queue.empty()) {

    currentCell = queue.top();

    // if the currentCell is the finish node
    //if(currentCell == ROWS*ROWS/2+COLS/2) {
      // found the destination, end search 
    //}
    queue.pop(); // remove current node from the queue

    currentNode = &maze[currentCell];
    currentNode->visit(); // add current node to closed list
    currentNode->removeFromOpen(); // mark the current node out of open list

    ///////// DEBUG MESSAGE ///////////////
    std::cout << "i'm here and CURRENT: " << (int) currentCell 
              << " g: " << currentNode->getG()
              << " h: " << currentNode->getH()
              << " f: " << currentNode->getF()
              << std::endl;

    // loop through all its neighbor
    for(byte next=0; next<4; ++next) {
      // getting a valid neigbor by checking to see if there's wall
      if(currentNode->getWall(next)) continue;

      nextCell = currentCell + neighbors[next]; // else get neighbor 
      neighborNode = &maze[nextCell]; // get neighbor node

      // if the finish node is found
      if(nextCell == GOAL) {

        ///////// DEBUG MESSAGE ///////////////
        std::cout << "this is final node: " << (int) nextCell << " " << GOAL << std::endl;
        // just set the parent of the nextCell 
        // and then finish the algorithm
        neighborNode->setParent(currentCell);
        std::cout << "this is the parent of final node: " << (int) neighborNode->getParent() << std::endl;
        return;
      }

      // if the neigbor is in closed list
      // don't do anything, and continue
      if(neighborNode->isVisited())
        continue;

      // evaluate new g value
      newG = currentNode->getG() + COST; 

      // REMINDER: queue holds indices of nodes
      //           Type of nextCell is byte
      //           Type of neighborNode is Node
      //bool isInOpen = queue.find(nextCell) != queue.end() ? true : false;
      bool isInOpen = neighborNode->isInOpen();
      
    ///////// DEBUG MESSAGE ///////////////
    std::cout << "             nextCell: " << (int) nextCell; 

      // if the nextCell is in open OR 
      // the new g value is smaller than the old g value
      if(!isInOpen || newG < neighborNode->getG()) {

    ///////// DEBUG MESSAGE ///////////////
    std::cout << "  updating the nextCell" 
              << " G: " << (int)newG 
              << " H: " << neighborNode->getH() 
              << " F: " << neighborNode->getF(); 

        neighborNode->setParent(currentCell); // set parent
        neighborNode->setG(newG); // set new g value

        // check if the nextCell is in open set
        // if not, add the nextCell into the open set
        if(!isInOpen) {
          queue.push(nextCell); 
          neighborNode->putInOpen(); // mark the node as in open
        }
      }
      std::cout << std::endl;
    } // loop for all the nextCell 
  } // end a* algorithm

} // end of findShortestPath

void mapMaze() {

  bool keepMapping = true, reachedGoal = false;
  Node* currentNode;

  int counter = 0;

  // for each cells visited
  while(keepMapping) {

    std::priority_queue<byte, std::vector<byte>, CompareNodes> queue; // available cells list 
    currentNode = &maze[currentCell]; // get currentNode
  
    std::cout << counter << "th current cell: " << (int) currentCell << std::endl;

    // if the current node is not visited
    if(!currentNode->isMapped()) {

      currentNode->map(); // mark the cell that it has been mapped 
      counter++; // when visiting new cell, increment counter

      // check sensors using checkForWalls function
      // set walls
      checkForWalls();
    }

    // update neighboring nodes by changing the g values,
    // keep track of the smallest g value 
    // and choose the best option
    for(byte side=0; side<4; ++side) {

      if(currentNode->getWall(side)) continue; // if theres wall, do nothing

      nextCell = currentCell + neighbors[side]; // get next cell index

      if(!maze[nextCell].isMapped()) { // if the new cell is not visited
        // if changing the g value each time doesn't work,
        // try comparing the g value, and if lower g value can be stored, store the lower.
        maze[nextCell].setG(0);
        if(!maze[nextCell].getParent()) // if there is no parent
          maze[nextCell].setParent(currentCell); // set parent of nextCell to currentCell
        // only add cells that are haven't been visited
        queue.push(nextCell);
      }
    } // end of for() loop

    // if there are three walls and or no new cells to visit, move to parent
    // this is when the queue is empty
    nextCell = queue.empty() ? currentNode->getParent() : queue.top();

    // TODO:
    // check for corner cases
    // such as when the mouse has reached the goal
    // needs to go back to the start cell
    if(currentCell == GOAL) {
      reachedGoal = true;
      //setHValues(0);
    }

    // TODO:
    // move to next node
    // change orientation, move the mouse
    currentCell = nextCell;

    // when the mouse comes back to the start cell
    if(currentCell == 0 && reachedGoal)
    //if(currentCell == GOAL) // for now end algorithm when the center is reached
      keepMapping = false;

  } // end of while() loop
}

void mapMaze() {

  bool keepMapping = true, reachedGoal = false;
  Node* currentNode;

  int counter = 0;

  // for each cells visited
  while(keepMapping) {

    std::priority_queue<byte, std::vector<byte>, CompareNodes> queue; // available cells list 
    currentNode = &maze[currentCell]; // get currentNode
  
    std::cout << counter << "th current cell: " << (int) currentCell << std::endl;

    // if the current node is not visited
    if(!currentNode->isMapped()) {

      currentNode->map(); // mark the cell that it has been mapped 
      counter++; // when visiting new cell, increment counter

      // check sensors using checkForWalls function
      // set walls
      checkForWalls();
    }

    // update neighboring nodes by changing the g values,
    // keep track of the smallest g value 
    // and choose the best option
    for(byte side=0; side<4; ++side) {

      if(currentNode->getWall(side)) continue; // if theres wall, do nothing

      nextCell = currentCell + neighbors[side]; // get next cell index

      if(!maze[nextCell].isMapped()) { // if the new cell is not visited
        // if changing the g value each time doesn't work,
        // try comparing the g value, and if lower g value can be stored, store the lower.
        maze[nextCell].setG(0);
        if(!maze[nextCell].getParent()) // if there is no parent
          maze[nextCell].setParent(currentCell); // set parent of nextCell to currentCell
        // only add cells that are haven't been visited
        queue.push(nextCell);
      }
    } // end of for() loop

    // if there are three walls and or no new cells to visit, move to parent
    // this is when the queue is empty
    nextCell = queue.empty() ? currentNode->getParent() : queue.top();

    // TODO:
    // check for corner cases
    // such as when the mouse has reached the goal
    // needs to go back to the start cell
    if(currentCell == GOAL) {
      reachedGoal = true;
      //setHValues(0);
    }

    // TODO:
    // move to next node
    // change orientation, move the mouse
    currentCell = nextCell;

    // when the mouse comes back to the start cell
    if(currentCell == 0 && reachedGoal)
    //if(currentCell == GOAL) // for now end algorithm when the center is reached
      keepMapping = false;

  } // end of while() loop
}

void resetGValues() {
  for(int index=0; index<ROWS*COLS; ++index) {
    // reset g to 0
    maze[index].setG(0);
  }
}

void resetParents() {
  for(int index=0; index<ROWS*COLS; ++index) {
    // reset parents 
    maze[index].setParent(0);
  }
}

void resetVisited() {
  for(int index=0; index<ROWS*COLS; ++index) {
    // reset visited 
    maze[index].unVisit();
  }
}
