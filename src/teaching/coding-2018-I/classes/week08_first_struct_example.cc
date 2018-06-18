#include <iostream>

struct pareja {
  int p1;
  int q2;
};

pareja g(int x, int y) {
  pareja ret;
  ret.p1 = x+y;
  ret.q2 = x-y;
  return ret;
}

int main() {
  pareja rr;
  rr.p1 = 5;
  rr.q2 = 34;
  std::cout << rr.p1 << " " << rr.q2 << std::endl;
  rr = g(10, 4);
  std::cout << rr.p1 << " " << rr.q2 << std::endl;
}
