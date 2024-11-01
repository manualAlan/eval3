#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// This function compares two strings for use with std::sort
bool stringOrder(const std::string & a, const std::string & b) {
  return a < b;
}

// This function sorts the data in the vector
void sortData(std::vector<std::string> & data) {
  std::sort(data.begin(), data.end(), stringOrder);
}

void processInput(std::istream & input) {
  std::vector<std::string> lines;
  std::string line;

  // Read lines from the input stream
  while (std::getline(input, line)) {
    lines.push_back(line);
  }

  // Sort the lines
  sortData(lines);

  // Output the sorted lines
  for (const auto & line : lines) {
    std::cout << line << std::endl;
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    // No command-line arguments: read from standard input
    processInput(std::cin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      std::ifstream file(argv[i]);
      if (!file) {
        std::cerr << "Could not open file: " << argv[i] << std::endl;
        return EXIT_FAILURE;
      }
      processInput(file);
      file.close();
    }
  }
  return EXIT_SUCCESS;
}
