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

  // If no arguments, read from standard input
  if (argc == 1) {
    readFromStream(std::cin, lines);
  }
  else {
    // Read from each file specified in the arguments
    for (int i = 1; i < argc; ++i) {
      std::ifstream file(argv[i]);
      if (!file) {
        std::cerr << "Could not open file " << argv[i] << std::endl;
        return EXIT_FAILURE;
      }
      readFromStream(file, lines);
    }
  }

  // Sort the lines using std::sort
  std::sort(lines.begin(), lines.end());

  // Print the sorted lines
  for (const auto & line : lines) {
    std::cout << line << std::endl;
  }

  return EXIT_SUCCESS;
}
