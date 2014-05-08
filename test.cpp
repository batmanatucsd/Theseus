#include <iostream>
#include <stack>
#include <vector>
#include <random>
#include <ctime>

#include "maze.hpp"

using namespace std;
std::vector<Node> realMaze(256);

// functions for setting up walls
void setRealNorth(byte cell) {
  realMaze[cell].setNorth(); realMaze[cell+neighbors[NORTH]].setSouth();
}
void setRealEast(byte cell) {
  realMaze[cell].setEast(); realMaze[cell+neighbors[EAST]].setWest();
}
void setRealWest(byte cell) {
  realMaze[cell].setWest(); realMaze[cell+neighbors[WEST]].setEast();
}
void setRealSouth(byte cell) {
  realMaze[cell].setSouth(); realMaze[cell+neighbors[SOUTH]].setNorth();
}
void randNumbers();
void setRealMaze();
void mazeOne();
void randMaze();
void randWalls( int i, int rand1, int rand2);
void printMaze(const std::vector<Node>&, int argc = 0);

int main(int argc, char * argv[]) {
  std::cout << "\n**************************************************************************************************\n";
  std::cout << "**************************************************************************************************\n";

  // Initial Setup for the real maze
  setRealMaze();

  /************************ DEBUG *****************************/
  /*************** Setting Up the Walls ***********************/

  //mazeOne();
  randMaze(); 
  setFakeMaze(realMaze);


  /************************************************************/
  /*********************** Setting Up  ************************/
  // Initial Setup for our maze
  std::vector<Node> newMaze(256);  
  setMaze(newMaze); // set up Maze

  setHValues(GOAL); // set H values on maze
  
  mapMaze(); // mapping maze


  /************************ DEBUG *****************************/
  /************** Printing out H values ***********************/
  // for(int i=0; i<ROWS*COLS; ++i) 
  // {
  //   cout << " h = " << maze[i].getH() << "  ";

  //   if(maze[i].getH()/10 == 0)
  //     cout << " ";
  //   if(i%ROWS == ROWS-1) 
  //     cout << endl;
  // }

  /************************ DEBUG *****************************/
  /*************** Getting Shortest Path **********************/
  std::cout << "\n**************************************************************************************************\n";
  std::cout << "**************************************************************************************************\n";

  clock_t time = clock();

  findShortestPath(); // find the shortest path when the maze is known

  time = clock() - time;

  std::cout << "\n**************************************************************************************************\n";
  std::cout << "**************************************************************************************************\n";

  std::cout << "elapsed time for a* algorithm: " << (float)time/CLOCKS_PER_SEC << std::endl;

  std::stack<byte> shortestPath;
  byte final = ROWS*(ROWS/2)+COLS/2;
  Node currentNode = maze[final];
  byte parent = currentNode.getParent();

  std::cout << "the final node: " << ROWS*(ROWS/2)+COLS/2 << std::endl;
  std::cout << "parent of the final node: " << (int) parent << std::endl;

  // get shortest path by following parent node
  shortestPath.push(final);
  while(parent != 0) {
     shortestPath.push(parent); 
     currentNode = maze[parent];
     parent = currentNode.getParent();
  }
  shortestPath.push(parent);

  /************************ DEBUG *****************************/
  /****************** Printing the Maze ***********************/
  std::cout << "\n**************************************************************************************************\n";
  std::cout << "**************************************************************************************************\n";

  std::cout << ">>>>>>>>>>>>>>>>>>>> The Real Maze: <<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
  printMaze(realMaze, argc); // printing the real maze


  std::cout << std::endl;
  std::cout << ">>>>>>>>>>>>>>>>>>>>>> Our Maze: <<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;

  // print the shortest path
  std::cout << "The shortest path is: ";
  while(!shortestPath.empty()) {
    std::cout << (int) shortestPath.top() << " ";
    shortestPath.pop();
  }
  std::cout << std::endl;

  printMaze(maze); // printing our maze


  return 0;
} // end of main

// print maze
void printMaze(const std::vector<Node>& mazeToPrint, int argc) {
  Node currentNode;

  for(int r=ROWS-1; r>=0; --r) {
    for(int c=0; c<COLS; ++c) {
       currentNode = mazeToPrint[COLS*r+c];
       if(currentNode.getWall(NORTH)) {
           std::cout << " ----- " ;
	                
       } else {
       
           std::cout << "       ";
       }
    }
    
    std::cout << std::endl;

    for(int c=0; c<COLS; ++c) {
       currentNode = mazeToPrint[COLS*r+c];

       if(currentNode.getWall(WEST)) {
         std::cout << "|"; 
       } else {
       
         std::cout << " ";
       }
       
       if(argc != 1) {
           std::cout << " ";
	   std::cout << COLS * r + c;
	   
           if((COLS*r+c)/10 == 0) {
               std::cout << "   "; 
           } else {
                if((COLS*r+c)/100 == 0 ) 
                    std::cout << "  "; 
                else {
                    std::cout << " "; 
                }
           }
       } else {
           if(COLS*r+c == 136)
               std::cout << "*    ";
           else
               std::cout << "     ";
       }
       
       if(currentNode.getWall(EAST)) {
         std::cout << "|";
       } else {
         std::cout << " ";
       }
    }
    std::cout << std::endl;

    // print out the bottom line
    if(r==0) {
      for(int c=0; c<COLS; ++c) {
          currentNode = mazeToPrint[c];
          if(currentNode.getWall(SOUTH)) 
              std::cout << " ----- ";
      }
    }
  }
  std::cout << std::endl;
}

void setRealMaze() {
  // set walls around the boarders
  for(byte r=0; r<ROWS; ++r) {
    realMaze[COLS*r].setWest(); // set WEST wall
    realMaze[COLS*r+COLS-1].setEast(); // set EAST wall
  }

  for(byte c=0; c<COLS; ++c) {
    realMaze[c].setSouth(); // set South wall
    realMaze[COLS*(ROWS-1) + c].setNorth(); // set North wall
  }
}

void mazeOne()
{
 //row 0 0-15
  setRealEast(0);
  for( int i = 2; i < 16; i++ )
  {
    if( i != 8 )
      setRealNorth(i);
  }

  //row 1 16-31
  setRealEast(16);
  setRealEast(17);
  for( int i = 19; i < 30; i++ )
  {
    setRealNorth(i);
  }
  setRealEast(30);

  //row 2 32-47
  setRealEast(32);
  setRealEast(33);
  for( int i = 35; i < 45; i++ )
  {
    if( i != 40 )
      setRealNorth(i);
  }

  //row 3 48-63
  setRealEast(49);
  setRealNorth(51);
  setRealNorth(54);
  setRealNorth(55);
  setRealNorth(56);
  setRealNorth(57);
  setRealNorth(59);
  setRealNorth(60);
  setRealEast(61);
  setRealEast(62);

  //row 4 64-79
  setRealEast(64);
  setRealEast(65);
  setRealEast(66);
  setRealEast(67);
  setRealEast(68);
  for( int i = 70; i < 78; i++)
  {
    setRealNorth(i);
  }
  setRealEast(77);
  
  setRealEast(78);

  //row 5 80-95
  setRealEast(80);
  setRealEast(81);
  setRealEast(82);
  setRealEast(83);
  setRealEast(84);
  setRealEast(85);
  setRealNorth(87);
  setRealNorth(88);
  setRealNorth(89);
  setRealEast(92);
  setRealEast(93);
  setRealEast(94);

  //row 6 96-111
  setRealEast(96);
  setRealEast(97);
  setRealEast(99);
  setRealEast(100);
  setRealEast(101);
  setRealNorth(103);
  //setRealNorth(104);
  setRealNorth(105);
  setRealEast(106);
  setRealEast(107);
  setRealNorth(107);
  setRealEast(108);
  setRealEast(109);
  setRealEast(110);
  setRealNorth(110);
  //row 7 112 - 127
  for( int i = 113; i < 123; i++)
  {
    if( i!=119)
      setRealEast(i);
  }
  setRealNorth(123);
  setRealEast(124);
  setRealEast(126);
  setRealNorth(126);

  //row 8 128 - 143
  for( int i = 128; i < 137; i++ )
  {
    setRealEast(i);
  }
  setRealNorth(135);
  setRealNorth(136);
  setRealEast(137);
  setRealEast(138);
  
  //row 9 144-159
  for( int i = 144; i < 150; i++ )
  {
    if( i != 147 )
      setRealEast(i);
  }
  setRealNorth(151);
  setRealNorth(152);
  
  for( int i = 153; i < 159; i++ )
  {
    setRealEast(i);
  }
  

  // row 10 160-175
  for( int i = 160; i < 167; i++ )
  {
    setRealEast(i);
  }
  setRealNorth(167);
  setRealEast(168);
  setRealNorth(169);
  setRealEast(169);
  for( int i = 170; i < 175; i++ )
  {
    setRealEast(i);
  }

  //row 11 176 - 191
  for(int i = 177; i < 182; i++)
  {
    setRealEast(i);
  }
  for(int i = 183; i < 187; i++)
  {
    setRealNorth(i);
  }
  setRealEast(186);
  for(int i = 187; i < 191; i++)
  {
    setRealEast(i);
  }

  //row 12 192 - 207
  for(int i = 192; i < 198; i++ )
  {
    setRealEast(i);
  }
  
  for(int i = 198; i < 202; i++ )
  {
    setRealNorth(i);
  }

  for(int i = 202; i < 207; i++ )
  {
    setRealEast(i);
  }

  //row 13 208 - 223
  for( int i = 208; i < 213; i++ )
  {
    setRealEast(i);
  }

  for( int i = 214; i < 221; i++ )
  {
    setRealNorth(i);
  }

  for( int i = 218; i < 223; i++ )
  {
    setRealEast(i);
  }
  
  //row 14 224 - 239 
  for( int i = 224; i < 239; i++ )
  {
    if ( i < 230 && i != 228 || i == 238)
    {
      setRealEast(i);
    }
    if( i > 229 )
    {
      setRealNorth(i);
    }
  } 

  //row 15 240 -255
  setRealEast(240);
}

void randNumbers()
{
  srand(time(NULL));
  for( int i = 0; i < 256; i++)
  {
    
  }
}

void randMaze()
{

  setRealEast(0);
  setRealEast(16);
  setRealEast(32);
  setRealNorth( 136 );
  setRealNorth( 135 );
  setRealWest( 135 );
  setRealWest( 119 );
  setRealSouth( 119 );
  setRealSouth( 120 );
  setRealEast( 120 );
  srand( time(NULL) );
  
  for( int i = 0; i < 300; i++ )
  {
    int num = rand()%256;
    if( num != 16 && num != 0 && num != 32 && num != 136 
	&& num != 135 && num != 119 && num != 120 && num != 137 &&
	num !=48 && num != 49 )
    {
      randWalls( num, rand()%4, rand()%8 );
    }
  }
}

void randWalls( int i, int rand1, int rand2 )
{
  //cout << i << " " << rand1 << " " << rand2 << endl;

  if( rand1 % 2 == 0 && rand1 > 1 )
  {
    setRealWest(i);
  }
  
  if( rand2 % 2 == 0 )
  {
    setRealNorth( i );
  }
}

