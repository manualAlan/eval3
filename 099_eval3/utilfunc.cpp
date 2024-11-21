#include "utilfunc.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

void parseShipFile(
    const std::string & filename,
    std::map<std::pair<std::string, std::string>, uint64_t> & routeCapacity,
    std::set<std::string> & shipNames) {
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    std::cerr << "cannot open " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string name, typeInfo, source, destination, capacityStr;

    if (!std::getline(iss, name, ':') || !std::getline(iss, typeInfo, ':') ||
        !std::getline(iss, source, ':') || !std::getline(iss, destination, ':') ||
        !std::getline(iss, capacityStr)) {
      std::cerr << "malformed line in input file: " << line << '\n';
      exit(EXIT_FAILURE);
    }

    if (!shipNames.insert(name).second) {
      std::cerr << "Duplicate ship name " << name << std::endl;
      exit(EXIT_FAILURE);
    }

    uint64_t capacity = strtoull(capacityStr.c_str(), NULL, 10);
    routeCapacity[std::make_pair(source, destination)] += capacity;
  }
}

std::vector<Cargo> parseCargoFile(const std::string & filename) {
  std::vector<Cargo> cargoList;
  std::ifstream file(filename.c_str());
  if (!file.is_open()) {
    std::cerr << "error: cannot open " << filename << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string line;
  while (std::getline(file, line)) {
    cargoList.push_back(Cargo(line));
  }
  return cargoList;
}

void printRouteCapacities(
    const std::map<std::pair<std::string, std::string>, uint64_t> & routeCapacity) {
  for (std::map<std::pair<std::string, std::string>, uint64_t>::const_iterator it =
           routeCapacity.begin();
       it != routeCapacity.end();
       ++it) {
    std::cout << "(" << it->first.first << " -> " << it->first.second
              << ") has total capacity " << it->second << std::endl;
  }
}
