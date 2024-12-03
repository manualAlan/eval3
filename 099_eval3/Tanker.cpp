#include "Tanker.hpp"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ship.hpp"
bool Tanker::canCarry(const Cargo & cargo) const {
  //source and destination match
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }

  // hazardous material rules
  for (std::vector<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {
    if (it->find("hazardous-") == 0) {
      std::string hazmat = it->substr(10);
      if (std::find(hazmatCapabilities.begin(), hazmatCapabilities.end(), hazmat) ==
          hazmatCapabilities.end()) {
        return false;
      }
    }
  }
  //  "liquid" or "gas" property
  if (std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "liquid") ==
          cargo.getProperties().end() &&
      std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "gas") ==
          cargo.getProperties().end()) {
    return false;
  }

  //check if there is enough total capacity
  if (usedCapacity + cargo.getWeight() > capacity) {
    return false;
  }

  //check if there are enough tanks available
  unsigned int availableTanks = tanks - loadedCargo.size();
  if (availableTanks == 0) {
    return false;
  }

  //remperature requirements
  int cargoMinTemp = 0, cargoMaxTemp = 0;
  for (std::vector<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {
    if (it->find("mintemp=") == 0) {
      cargoMinTemp = std::strtol(it->substr(8).c_str(), NULL, 10);
    }
    else if (it->find("maxtemp=") == 0) {
      cargoMaxTemp = std::strtol(it->substr(8).c_str(), NULL, 10);
    }
  }

  if (cargoMinTemp > maxTemp || cargoMaxTemp < minTemp) {
    return false;
  }

  return true;
}

void Tanker::loadCargo(const Cargo & cargo) {
  usedCapacity += cargo.getWeight();
  loadedCargo.push_back(cargo);
}
void Tanker::printDetails() const {
  std::cout << "The Tanker Ship " << name << "(" << usedCapacity << "/" << capacity
            << ") is carrying : " << std::endl;
  for (std::vector<Cargo>::const_iterator it = loadedCargo.begin();
       it != loadedCargo.end();
       ++it) {
    std::cout << "  " << it->getName() << "(" << it->getWeight() << ")" << std::endl;
  }
  std::cout << "  " << loadedCargo.size() << " / " << tanks << " tanks used" << std::endl;
}
