#include "AnimalShip.hpp"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ship.hpp"
bool AnimalShip::canCarry(const Cargo & cargo) const {
  // source and destination match
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }

  //check if there is enough capacity
  if (usedCapacity + cargo.getWeight() > capacity) {
    return false;
  }

  //check if the cargo is "small enough"
  if (cargo.getWeight() > smallThreshold &&
      std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "animal") ==
          cargo.getProperties().end()) {
    return false;
  }

  //check hazardous material rules
  for (std::vector<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {
    if (it->find("hazardous-") == 0) {
      return false;
    }
  }
  //  if the cargo is a "roamer"
  if (std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "roamer") !=
          cargo.getProperties().end() &&
      hasRoamer) {
    return false;
  }

  return true;
}

void AnimalShip::loadCargo(const Cargo & cargo) {
  usedCapacity += cargo.getWeight();
  loadedCargo.push_back(cargo);

  //mark the ship as having a roamer if the cargo has the "roamer" property
  if (std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "roamer") !=
      cargo.getProperties().end()) {
    hasRoamer = true;
  }
}
void AnimalShip::printDetails() const {
  std::cout << "The Animals Ship " << name << "(" << usedCapacity << "/" << capacity
            << ") is carrying : " << std::endl;
  for (std::vector<Cargo>::const_iterator it = loadedCargo.begin();
       it != loadedCargo.end();
       ++it) {
    std::cout << "  " << it->getName() << "(" << it->getWeight() << ")" << std::endl;
  }
  std::cout << "  " << (hasRoamer ? "has a roamer" : "does not have a roamer")
            << std::endl;
}
