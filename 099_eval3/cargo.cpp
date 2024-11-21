#include "cargo.hpp"

#include <cstdlib>  // For strtoull
#include <sstream>

Cargo::Cargo(const std::string & line) {
  std::istringstream iss(line);
  std::getline(iss, name, ',');
  std::getline(iss, source, ',');
  std::getline(iss, destination, ',');
  std::string weightStr;
  std::getline(iss, weightStr, ',');
  weight = strtoull(weightStr.c_str(), NULL, 10);

  std::string property;
  while (std::getline(iss, property, ',')) {
    properties.insert(property);
  }
}
