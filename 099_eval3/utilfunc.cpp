#include "utilfunc.hpp"

#include <cstdlib>  // For EXIT_FAILURE and strtoull
#include <fstream>
#include <iostream>
#include <sstream>

void parseShipFile(
    const std::string & filename,
    std::map<std::pair<std::string, std::string>, uint64_t> & routeCapacity,
    std::set<std::string> & shipNames) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    std::cerr << "cannot open file" << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string name, typeInfo, source, destination, capacityStr;

    //parse line fields separated by ':'
    if (!std::getline(iss, name, ':') || !std::getline(iss, typeInfo, ':') ||
        !std::getline(iss, source, ':') || !std::getline(iss, destination, ':') ||
        !std::getline(iss, capacityStr)) {
      std::cerr << "wrong format line in input file: " << line << std::endl;
      exit(EXIT_FAILURE);
    }

    //check for duplicate ship names
    if (!shipNames.insert(name).second) {
      std::cerr << "duplicate ship name" << name << std::endl;
      exit(EXIT_FAILURE);
    }

    //vonvert capacity to unsigned int 64 bit
    uint64_t capacity;
    try {
      capacity = std::strtoull(capacityStr.c_str(), NULL, 10);
    }
    catch (const std::exception & e) {
      std::cerr << "Invalid capacity value in line:" << line << std::endl;
      exit(EXIT_FAILURE);
    }

    // Create a Ship object (typeInfo included but not used here)
    Ship ship(name, typeInfo, source, destination, capacity);

    // Add capacity to the corresponding route
    routeCapacity[ship.getRoute()] += ship.getCapacity();
  }

  file.close();
}

void printRouteCapacities(
    const std::map<std::pair<std::string, std::string>, uint64_t> & routeCapacity) {
  for (std::map<std::pair<std::string, std::string>, uint64_t>::const_iterator it =
           routeCapacity.begin();
       it != routeCapacity.end();
       it++) {
    std::cout << "(" << it->first.first << " -> " << it->first.second
              << ") has total capacity " << it->second << std::endl;
  }
}
