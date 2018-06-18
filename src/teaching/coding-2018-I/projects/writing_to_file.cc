#include <iostream>
#include <fstream>
#include <string>

struct pos {
  int x;
  int y;
};

int main() {
  std::string file_name = "unarchivo.txt";
  std::ifstream var_f {file_name};

  int a, b;

  if( var_f.is_open() ) {
    var_f >> a >> b;
    var_f.close();

    std::cout << "The sum of the numbers in the file are: "
        << a+b << std::endl;

    std::ofstream var_f2 {file_name};
    var_f2 << b << ' ' << a+b;
    var_f2.close();
  } else {
      std::ofstream var_new_f {file_name};
      var_new_f << 0 << ' ' << 1;
      var_new_f.close();
  }


  return 0;
}
