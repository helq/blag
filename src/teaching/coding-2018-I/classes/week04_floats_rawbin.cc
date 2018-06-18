#include <bitset>
#include <iostream>

// You can optionally separate the binary numbers with ', but you need a C++14 compilant compiler,
// add --std=c++14 to use it

typedef union {
  unsigned int i;
  float f;
  struct {
    unsigned char a, b, c, d;
  } s;
} u;

int main()
{
  u u1;
  u1.s.d = 0b00111110;
  u1.s.c = 0b00100000;
  u1.s.b = 0b00000000;
  u1.s.a = 0b00000000;
  //u1.i = 0b00111110001000000000000000000000;

  std::cout << u1.f << std::endl;
  //std::cout << (int) u1.s.a
  //   << " " << (int) u1.s.b
  //   << " " << (int) u1.s.c
  //   << " " << (int) u1.s.d << std::endl;

  std::bitset<32> u1bin = u1.i;
  std::cout << u1bin << std::endl;

  std::bitset<8> u1dbin = u1.s.d;
  std::bitset<8> u1cbin = u1.s.c;
  std::bitset<8> u1bbin = u1.s.b;
  std::bitset<8> u1abin = u1.s.a;
  std::cout << u1dbin
     << " " << u1cbin
     << " " << u1bbin
     << " " << u1abin
     << " " << std::endl;
  return 0;
}
