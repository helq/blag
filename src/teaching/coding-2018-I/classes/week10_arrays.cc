#include <iostream>

int main()
{
  int var[10];
  for (int i = 0; i < 10; i++) {
    var[i] = -1;
  }
  var[2] = 45;
  std::cout << var[1] << " " << var[2] << std::endl;
  return 0;
}
