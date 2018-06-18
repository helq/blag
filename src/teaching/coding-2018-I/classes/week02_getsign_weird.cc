#include <iostream>

int main()
{
  int a = 0;
  int sign = a > 0 ? 1 : a >> 31;
  std::cout << sign << std::endl;
  return 0;
}
