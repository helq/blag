#include <iostream>

void fun(int &a) {
  a = 2;
}

int main(int argc, char const* argv[])
{
  int b = 23;
  std::cout << b << std::endl;
  fun(b);
  std::cout << b << std::endl;

  return 0;
}
