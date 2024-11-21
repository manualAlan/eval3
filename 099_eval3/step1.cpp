#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>

#include "utilfunc.hpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "incorrect number of arguments" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string filename = argv[1];
  std::map<std::pair<std::string, std::string>, uint64_t> routeCapacity;
  std::set<std::string> shipNames;

  parseShipFile(filename, routeCapacity, shipNames);
  printRouteCapacities(routeCapacity);

  return 0;
}