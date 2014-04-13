#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include "Node.hpp"

#define rows 16 
#define cols 16 


class Board {
  public:
    std::vector<Node>* maze;

    // Constructor
    Board() {
      maze = new std::vector<Node>(rows*cols);
    }

    // Destructor
    ~Board() {
      delete maze;
    }

    // Fill h values
    // h = current to finish node
    void setHValues() {
      // h = 10 * (abs(currentRow - rows/2) + abs(currentCol - cols/2));
      for(int index=0; index<rows*cols; ++index) {
        int currentRow = index/cols, currentCol = index%cols;

        if(currentRow >= rows/2 && currentCol >= cols/2) { // QI
          maze->at(index).setH(currentRow + currentCol - cols);

        } else if(currentRow >= rows/2 && currentCol < cols/2) { // QII
          maze->at(index).setH(currentRow - currentCol - 1);

        } else if(currentRow < rows/2 && currentCol < cols/2) { // QIII
          maze->at(index).setH(rows - 2 - currentRow - currentCol);

        } else if(currentRow < rows/2 && currentCol >= cols/2) { // QIV
          maze->at(index).setH(currentCol - currentRow - 1);
        }
      }
    }


    // Fill g values for neighbors
    // g = distance from previous node 
    void setGValues(int currentRow, int currentCol) {
       
    }
};

#endif //BOARD_HPP
