#include <iostream>

using namespace std;

int main() {
  const int rows=16, cols=16;

  for(int r=15; r>=0; --r) {
      for(int c=0; c<16; ++c) 
          cout << r*cols + c << " ";
      cout << endl;
          //cout << "what? ";
  }
    
    
  return 0;
}

