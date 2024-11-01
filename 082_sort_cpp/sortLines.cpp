#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void readFromStream(std::istream & stream, std::vector<std::string> & lines) {
  std::string line;
  while (std::getline(stream, line)) {
    lines.push_back(line);
  }
}

int main(int argc, char * argv[]) {
  std::vector<std::string> lines;
  if (argc == 0) {
    return EXIT_FAILURE;
  }
  //if no arguments, read from standard input
  if (argc == 1) {
    readFromStream(std::cin, lines);
  }
  else {
    //read from each file specified in the arguments
    for (int i = 1; i < argc; ++i) {
      std::ifstream file(argv[i]);
      if (!file) {
        std::cerr << "Could not open file " << argv[i] << std::endl;
        return EXIT_FAILURE;
      }
      readFromStream(file, lines);
    }
  }

  std::sort(lines.begin(), lines.end());
  for (std::vector<std::string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    std::cout << *it << std::endl;
  }
  return EXIT_SUCCESS;
}
