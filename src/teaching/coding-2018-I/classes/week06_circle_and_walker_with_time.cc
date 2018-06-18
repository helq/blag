#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>

bool is_inside_circle(int a, int b, double rad) {
  double y = a - 8.5;
  double x = (b - 35)/2;
  bool circle = x*x + y*y < rad*rad;
  return circle;
}

bool caminador(int i, int j, int t) {
  if((t/70)%18 == i) {
    if (i%2==0) {
      return j==t%70;
    } else {
      return j==69-t%70;
    }
  } else {
    return false;
  }
}

int main() {
  for(int t=300; t<=1000000; t++) {
    double rad = 3*(sin(t/5)+1.5);
    for(int i=0; i<18; i++) {
      for(int j=0; j<70; j++) {
        if( caminador(i,j,t) ^ is_inside_circle(i,j,rad) ) {
          std::cout << '#';
        } else {
          std::cout << ' ';
        }
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::this_thread::sleep_for( std::chrono::milliseconds(50) );
  }
  return 0;
}
