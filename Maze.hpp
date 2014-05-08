#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <vector>
#include <queue>
#include "Node.hpp"
#include "mouse.hpp"

#define ROWS 16
#define COLS 16 
#define COST 1
#define GOAL ROWS*(ROWS/2)+COLS/2

// making these variables global
extern std::vector<Node> maze;
extern const char neighbors[];
extern byte head, currentCell, nextCell;

/************************************************/
/************ Function Declarations *************/ 
/************************************************/
void setWall(byte, byte cell=currentCell);
void setMaze(std::vector<Node> &);
void setHValues(byte);
void resetGValues();
void resetParents();
void resetVisited();
void findShortestPath();
void mapMaze();

// Compare class for priority queue in shortest path finding algorithm
class CompareNodes {
  public:
  bool operator() (const byte  & lhs, const byte & rhs) const; 
};

// template class for priority_queue with find 
// used in findShortestPath()
template<class T,
         class Container=std::vector<T>, 
         class Compare=std::less<typename Container::value_type>>
class priority_queue : public std::priority_queue<T, Container, Compare> {
  public:
    typedef typename
      std::priority_queue<T, Container, 
                          Compare>::container_type::iterator iterator;

    iterator find(const T& val) {
      // return std::find(this->c.begin(), this->c.end());
      auto first = this->c.begin();
      auto last = this->c.end();
      while(first != last) {
        if(*first == val) return first; 
        ++first;
      }
      return last;
    }

    iterator end() {
      // return iterator passed the last element
      return this->c.end();
    }
};

#endif //MAZE_HPP
