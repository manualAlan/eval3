#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool myfunction(std::string a, std::string b) {
  return (a < b);
}
void read(std::istream & stream, std::vector<std::string> & lines) {
  std::string line;
  while (std::getline(stream, line)) {
    lines.push_back(line);
  }
}

int main(int argc, char * argv[]) {
  std::vector<std::string> lines;
  if (argc == 0) {
    std::cerr << "how?" << std::endl;
    return EXIT_FAILURE;
  }
  if (argc == 1) {
    read(std::cin, lines);
  }
  else {
    for (int i = 1; i < argc; ++i) {
      std::ifstream file(argv[i]);
      if (!file) {
        std::cerr << "Could not open file " << argv[i] << std::endl;
        return EXIT_FAILURE;
      }
      read(file, lines);
      file.close();
    }
  }

  std::sort(lines.begin(), lines.end(), myfunction);
  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    std::cout << *it << std::endl;
  }
  return EXIT_SUCCESS;
}
