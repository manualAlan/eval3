#include "Tanker.hpp"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ship.hpp"
bool Tanker::canCarry(const Cargo & cargo) const {
  //  std::cout << "Checking if ship '" << name << "' can carry cargo '" << cargo.getName()
  //        << "'" << std::endl;

  //Source and destination match
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }

  // Hazardous material rules
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
  for (std::vector<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       it++) {
    size_t equalsCount = std::count(it->begin(), it->end(), '=');
    if (equalsCount > 1) {  //reject properties with more than one=
      std::cerr << "wrong num of =" << std::endl;
      std::exit(EXIT_FAILURE);
    }
  }
  //"liquid" or "gas" property
  bool isLiquid =
      std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "liquid") !=
      cargo.getProperties().end();
  bool isGas =
      std::find(cargo.getProperties().begin(), cargo.getProperties().end(), "gas") !=
      cargo.getProperties().end();

  if (!isLiquid && !isGas) {
    return false;
  }

  // Ensure capacity is divisible by the number of tanks
  uint64_t capacityPerTank = capacity / tanks;
  if (capacity % tanks != 0) {
    std::cerr << "Error: Tanker capacity not divisible by the number of tanks."
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  // Simulate tank allocation
  uint64_t remainingWeight = cargo.getWeight();
  bool cargoTypeMatches = false;

  // Check if the cargo can fit into partially filled tanks of the same type
  for (std::vector<Tank>::const_iterator it = tankStatus.begin(); it != tankStatus.end();
       ++it) {
    if (it->cargoType == cargo.getName() && it->used < capacityPerTank) {
      uint64_t availableSpace = capacityPerTank - it->used;
      if (remainingWeight <= availableSpace) {
        cargoTypeMatches = true;  // It can fit into an existing tank
        remainingWeight = 0;
        break;
      }
      remainingWeight -= availableSpace;
    }
  }

  // Check if remaining weight can fit into new tanks
  if (remainingWeight > 0) {
    for (std::vector<Tank>::const_iterator it = tankStatus.begin();
         it != tankStatus.end();
         ++it) {
      if (it->used == 0) {  // Empty tank
        uint64_t loadAmount = std::min(capacityPerTank, remainingWeight);
        remainingWeight -= loadAmount;
        if (remainingWeight == 0) {
          cargoTypeMatches = true;
          break;
        }
      }
    }
  }

  // If there's still remaining weight or type doesn't match, it can't be carried
  if (remainingWeight > 0 || !cargoTypeMatches) {
    return false;
  }

  // Temperature requirements
  int cargoMinTemp = -273, cargoMaxTemp = 1000;
  for (std::vector<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {  //check min/max or default if no value
    if (it->find("mintemp=") == 0) {
      std::string valueStr = it->substr(8);
      if (valueStr.empty()) {
        cargoMinTemp = 0;
      }
      else {
        cargoMinTemp = std::strtol(valueStr.c_str(), NULL, 10);
      }
    }
    else if (it->find("maxtemp=") == 0) {
      std::string valueStr = it->substr(8);
      if (valueStr.empty()) {
        cargoMaxTemp = 0;
      }
      else {
        cargoMaxTemp = std::strtol(valueStr.c_str(), NULL, 10);
      }
    }
  }

  if (cargoMinTemp > maxTemp || cargoMaxTemp < minTemp) {
    return false;
  }

  return true;
}

void Tanker::loadCargo(const Cargo & cargo) {
  // Calculate per tank capacity
  uint64_t capacityPerTank = capacity / tanks;

  // Ensure that capacity is divisible by the number of tanks (this should be checked during initialization)
  if (capacity % tanks != 0) {
    std::cerr << "Error: Tanker capacity not divisible by the number of tanks."
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  uint64_t remainingWeight = cargo.getWeight();

  // First, fill partially filled tanks of the same cargo type
  for (std::vector<Tank>::iterator it = tankStatus.begin(); it != tankStatus.end();
       ++it) {
    if (it->cargoType == cargo.getName() && it->used < capacityPerTank) {
      uint64_t availableSpace = capacityPerTank - it->used;
      uint64_t loadAmount = std::min(availableSpace, remainingWeight);
      it->used += loadAmount;
      remainingWeight -= loadAmount;
      if (remainingWeight == 0) {
        break;  // Fully loaded
      }
    }
  }

  // Use empty tanks if there’s remaining weight
  for (std::vector<Tank>::iterator it = tankStatus.begin(); it != tankStatus.end();
       ++it) {
    if (it->used == 0) {  // Empty tank
      uint64_t loadAmount = std::min(capacityPerTank, remainingWeight);
      it->cargoType = cargo.getName();
      it->used = loadAmount;
      remainingWeight -= loadAmount;
      if (remainingWeight == 0) {
        break;  // Fully loaded
      }
    }
  }

  //If there’s still remaining weight, this is an internal logic error, as canCarry should have caught it
  if (remainingWeight > 0) {
    std::cerr << "atempting to load cargo that cannot fit: " << cargo.getName()
              << std::endl;
    std::exit(EXIT_FAILURE);
  }

  //Add the cargo to the loadedCargo list for tracking
  loadedCargo.push_back(cargo);

  // Update the used capacity of the ship
  usedCapacity += cargo.getWeight();

  //  std::cout << "Successfully loaded " << cargo.getWeight() << " of '" << cargo.getName()
  //        << "' onto ship '" << name << "'" << std::endl;
}

//void Tanker::loadCargo(const Cargo & cargo) {
// usedCapacity += cargo.getWeight();
// loadedCargo.push_back(cargo);
//}
void Tanker::printDetails() const {
  std::cout << "The Tanker Ship " << name << "(" << usedCapacity << "/" << capacity
            << ") is carrying : " << std::endl;
  for (std::vector<Cargo>::const_iterator it = loadedCargo.begin();
       it != loadedCargo.end();
       ++it) {
    std::cout << "  " << it->getName() << "(" << it->getWeight() << ")" << std::endl;
  }
  unsigned int tanksUsed = 0;
  for (std::vector<Tank>::const_iterator it = tankStatus.begin(); it != tankStatus.end();
       ++it) {
    if (it->used > 0) {
      ++tanksUsed;  // Count tanks that have been used
    }
  }
  std::cout << "  " << tanksUsed << " / " << tanks << " tanks used" << std::endl;
}
