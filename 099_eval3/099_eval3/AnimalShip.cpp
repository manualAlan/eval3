#include "AnimalShip.hpp"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
//subclass of ship
#include "ship.hpp"
bool AnimalShip::canCarry(const Cargo & cargo) const {
  //check if source and destination match
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }

  //check enough capacity
  if (usedCapacity + cargo.getWeight() > capacity) {
    return false;
  }

  //check no hazardous properties allowed)
  for (std::vector<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {
    if (it->find("hazardous-") == 0) {
      return false;
    }
  }

  //check if the cargo is "animal"
  bool isAnimal =
      std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "animal") !=
      cargo.getProperties().end();

  if (isAnimal) {
    //If cargo is "roamer", ensure no other "roamer" is already loaded
    bool isRoamer =
        std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "roamer") !=
        cargo.getProperties().end();
    if (isRoamer && hasRoamer) {
      return false;
    }
    //if not a "roamer", it's okay to load
    return true;
  }
  else {
    //Check non-animal cargo rules
    // Rule 5: Ensure it does not have "liquid" or "gas" properties
    bool isLiquid =
        std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "liquid") !=
        cargo.getProperties().end();
    bool isGas =
        std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "gas") !=
        cargo.getProperties().end();
    if (isLiquid || isGas) {
      return false;
    }

    //small enough?
    if (cargo.getWeight() > smallThreshold) {
      return false;
    }

    //if all checks passed,  loaded!
    return true;
  }
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
