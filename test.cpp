
#include <iostream>
#include <stack>
#include <vector>
#include "Maze.hpp"

#include <ctime>

using namespace std;

int main(int argc, char * argv[]) {
  
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
  for(int i=0; i<rows*cols; ++i) 
  {
    cout << " h = " << maze[i].getH() << "  ";

    if(maze[i].getH()/10 == 0)
      cout << " ";
    if(i%rows == rows-1) 
      cout << endl;
  }

  /************************ DEBUG *****************************/
  /*************** Setting Up the Walls ***********************/

  //row 0 0-15
  setEast(0);
  for( int i = 2; i < 16; i++ )
  {
    if( i != 8 )
      setNorth(i);
  }

  //row 1 16-31
  setEast(16);
  setEast(17);
  for( int i = 19; i < 30; i++ )
  {
    setNorth(i);
  }
  setEast(30);

  //row 2 32-47
  setEast(32);
  setEast(33);
  for( int i = 35; i < 45; i++ )
  {
    if( i != 40 )
      setNorth(i);
  }

  //row 3 48-63
  setEast(49);
  setNorth(51);
  setNorth(54);
  setNorth(55);
  setNorth(56);
  setNorth(57);
  setNorth(59);
  setNorth(60);
  setEast(61);
  setEast(62);

  //row 4 64-79
  setEast(64);
  setEast(65);
  setEast(66);
  setEast(67);
  setEast(68);
  for( int i = 70; i < 78; i++)
  {
    setNorth(i);
  }
  setEast(77);
  
  setEast(78);

  //row 5 80-95
  setEast(80);
  setEast(81);
  setEast(82);
  setEast(83);
  setEast(84);
  setEast(85);
  setNorth(87);
  setNorth(88);
  setNorth(89);
  setEast(92);
  setEast(93);
  setEast(94);

  //row 6 96-111
  setEast(96);
  setEast(97);
  setEast(99);
  setEast(100);
  setEast(101);
  setNorth(103);
  setNorth(104);
  setNorth(105);
  setEast(106);
  setEast(107);
  setNorth(107);
  setEast(108);
  setEast(109);
  setEast(110);
  setNorth(110);
  //row 7 112 - 127
  for( int i = 113; i < 123; i++)
  {
    if( i!=119 )
      setEast(i);
  }
  setNorth(123);
  setEast(124);
  setEast(126);
  setNorth(126);

  //row 8 128 - 143
  for( int i = 128; i < 135; i++ )
  {
    setEast(i);
  }
  setNorth(135);
  setNorth(136);
  setEast(137);
  setEast(138);
  
  //row 9 144-159
  for( int i = 144; i < 150; i++ )
  {
    if( i != 147 )
      setEast(i);
  }
  setNorth(151);
  setNorth(152);
  
  for( int i = 153; i < 159; i++ )
  {
    setEast(i);
  }
  

  // row 10 160-175
  for( int i = 160; i < 167; i++ )
  {
    setEast(i);
  }
  setNorth(167);
  setEast(168);
  setNorth(169);
  setEast(169);
  for( int i = 170; i < 175; i++ )
  {
    setEast(i);
  }

  //row 11 176 - 191
  for(int i = 177; i < 182; i++)
  {
    setEast(i);
  }
  for(int i = 183; i < 187; i++)
  {
    setNorth(i);
  }
  setEast(186);
  for(int i = 187; i < 191; i++)
  {
    setEast(i);
  }

  //row 12 192 - 207
  for(int i = 192; i < 198; i++ )
  {
    setEast(i);
  }
  
  for(int i = 198; i < 202; i++ )
  {
    setNorth(i);
  }

  for(int i = 202; i < 207; i++ )
  {
    setEast(i);
  }

  //row 13 208 - 223
  for( int i = 208; i < 213; i++ )
  {
    setEast(i);
  }

  for( int i = 214; i < 221; i++ )
  {
    setNorth(i);
  }

  for( int i = 218; i < 223; i++ )
  {
    setEast(i);
  }
  
  //row 14 224 - 239 
  for( int i = 224; i < 239; i++ )
  {
    if ( i < 230 && i != 228 || i == 238)
    {
      setEast(i);
    }
    if( i > 229 )
    {
      setNorth(i);
    }
  } 

  //row 15 240 -255
  setEast(240);
  
  /*setNorth(12);
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
  setEast(28);*/



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

  // get shortest path by following parent node
  shortestPath.push(final);
  while(parent != 0) {
     shortestPath.push(parent); 
     currentNode = maze[parent];
     parent = currentNode.getParent();
  }
  shortestPath.push(parent);

  // print the shortest path
  std::cout << "The shortest path is: \n";
  while(!shortestPath.empty()) {
    std::cout << (int) shortestPath.top() << " ";
    shortestPath.pop();
  }

  std::cout << std::endl;

  // print maze
  for(int r=rows-1; r>=0; --r) {
    for(int c=0; c<cols; ++c) {
       currentNode = maze[cols*r+c];
       if(currentNode.getNorth()) {
           std::cout << " ----- " ;
	                
       } else {
       
           std::cout << "       ";
       }
    }
    
    std::cout << std::endl;

    for(int c=0; c<cols; ++c) {
       currentNode = maze[cols*r+c];

       if(currentNode.getWest()) {
         std::cout << "|"; 
       } else {
       
         std::cout << " ";
       }
       
       if(argc != 1) {
           std::cout << " ";
	   std::cout << cols * r + c;
	   
           if((cols*r+c)/10 == 0) {
               std::cout << "   "; 
           } else {
                if((cols*r+c)/100 == 0 ) 
                    std::cout << "  "; 
                else {
                    std::cout << " "; 
                }
           }
       } else {
           std::cout << "     ";
       }
       
        

       if(currentNode.getEast()) {
         std::cout << "|";
       } else {
         std::cout << " ";
       }
    }
    std::cout << std::endl;

    // print out the bottom line
    if(r==0) {
      for(int c=0; c<cols; ++c) {
          currentNode = maze[c];
          if(currentNode.getSouth()) 
              std::cout << " ----- ";
      }
    }
  }
  std::cout << std::endl;
  return 0;
}
