#include "ContainerShip.hpp"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ship.hpp"
//subclass of ship
ContainerShip::ContainerShip(const std::string & name,
                             const std::string & typeInfo,
                             const std::string & source,
                             const std::string & destination,
                             uint64_t capacity,
                             unsigned int slots,
                             const std::vector<std::string> & hazmatCapabilities) :
    Ship(name, typeInfo, source, destination, capacity),
    slots(slots),
    hazmatCapabilities(hazmatCapabilities) {
}
//if ship can carry certain targo

bool ContainerShip::canCarry(const Cargo & cargo) const {
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }  //cargo must match the ship's route
  ////cargo needs the "container" property
  if (std::find(cargo.getProperties().begin(),
                cargo.getProperties().end(),
                "container") == cargo.getProperties().end()) {
    return false;
  }
  //make sure there's enough capacity left for the cargo
  if (usedCapacity + cargo.getWeight() > capacity) {
    return false;
  }
  //check if there are enough slots left for the cargo
  if (loadedCargo.size() >= slots) {
    return false;
  }

  for (std::vector<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {
    if (it->find("hazardous-") == 0) {          //validate hazmat requiremen
      std::string hazmatType = it->substr(10);  //remove "hazardous-'
      if (std::find(hazmatCapabilities.begin(), hazmatCapabilities.end(), hazmatType) ==
          hazmatCapabilities.end()) {
        return false;
      }
    }
  }
  //congrats, checks passed all
  return true;
}
//load onto ship
void ContainerShip::loadCargo(const Cargo & cargo) {
  loadedCargo.push_back(cargo);
  usedCapacity += cargo.getWeight();
}
void ContainerShip::printDetails()
    const {  //prints the ship's details, include loaded cargo
  std::cout << "The Container Ship " << name << "(" << usedCapacity << "/" << capacity
            << ") is carrying : " << std::endl;
  for (std::vector<Cargo>::const_iterator it = loadedCargo.begin();
       it != loadedCargo.end();
       ++it) {
    std::cout << "  " << it->getName() << "(" << it->getWeight() << ")" << std::endl;
  }
  std::cout << "  (" << slots - loadedCargo.size() << ") slots remain" << std::endl;
}
