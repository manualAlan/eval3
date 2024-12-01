#include "ship.hpp"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
///////////////////////cargo
Cargo::Cargo(const std::string & name,
             const std::string & source,
             const std::string & destination,
             uint64_t weight,
             const std::vector<std::string> & properties) :
    name(name),
    source(source),
    destination(destination),
    weight(weight),
    properties(properties) {
}

const std::string & Cargo::getName() const {
  return name;
}

const std::string & Cargo::getSource() const {
  return source;
}

const std::string & Cargo::getDestination() const {
  return destination;
}

uint64_t Cargo::getWeight() const {
  return weight;
}

const std::vector<std::string> & Cargo::getProperties() const {
  return properties;
}

/////////////////////Ship/////////
Ship::Ship(const std::string & name,
           const std::string & typeInfo,
           const std::string & source,
           const std::string & destination,
           uint64_t capacity) :
    name(name),
    typeInfo(typeInfo),
    source(source),
    destination(destination),
    capacity(capacity),
    usedCapacity(0) {
}
uint64_t Ship::getCapacity() const {
  std::cout << "1" << std::endl;
  return capacity;
}
const std::string & Ship::getName() const {
  return name;
}

const std::string & Ship::getSource() const {
  return source;
}

const std::string & Ship::getDestination() const {
  return destination;
}
//////////////////containership/////////////////
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

bool ContainerShip::canCarry(const Cargo & cargo) const {
  if (cargo.getSource() != source || cargo.getDestination() != destination) {
    return false;
  }

  if (std::find(cargo.getProperties().begin(),
                cargo.getProperties().end(),
                "container") == cargo.getProperties().end()) {
    return false;
  }

  if (usedCapacity + cargo.getWeight() > capacity) {
    return false;
  }

  if (loadedCargo.size() >= slots) {
    return false;
  }

  for (std::vector<std::string>::const_iterator it = cargo.getProperties().begin();
       it != cargo.getProperties().end();
       ++it) {
    if (it->find("hazardous-") == 0) {
      std::string hazmatType = it->substr(10);  // Remove "hazardous-"
      if (std::find(hazmatCapabilities.begin(), hazmatCapabilities.end(), hazmatType) ==
          hazmatCapabilities.end()) {
        return false;
      }
    }
  }

  return true;
}

void ContainerShip::loadCargo(const Cargo & cargo) {
  loadedCargo.push_back(cargo);
  usedCapacity += cargo.getWeight();
}
void ContainerShip::printDetails() const {
  std::cout << "The Container Ship " << name << "(" << usedCapacity << "/" << capacity
            << ") is carrying : " << std::endl;
  for (std::vector<Cargo>::const_iterator it = loadedCargo.begin();
       it != loadedCargo.end();
       ++it) {
    std::cout << "  " << it->getName() << "(" << it->getWeight() << ")" << std::endl;
  }
  std::cout << "  (" << slots - loadedCargo.size() << ") slots remain" << std::endl;
}
/////////////////////////////////fleet/////////////
Fleet::~Fleet() {
  for (std::vector<Ship *>::iterator it = ships.begin(); it != ships.end(); ++it) {
    delete *it;
  }
}

void Fleet::addShip(Ship * ship) {
  ships.push_back(ship);
}

void Fleet::computeRouteCapacities() {
  // routeCapacities.clear();
  for (std::vector<Ship *>::const_iterator it = ships.begin(); it != ships.end(); it++) {
    std::pair<std::string, std::string> route((*it)->getSource(),
                                              (*it)->getDestination());
    routeCapacities[route] += (*it)->getCapacity();
  }
}

void Fleet::printRouteCapacities() const {
  for (std::map<std::pair<std::string, std::string>, uint64_t>::const_iterator it =
           routeCapacities.begin();
       it != routeCapacities.end();
       ++it) {
    std::cout << "(" << it->first.first << " -> " << it->first.second
              << ") has total capacity " << it->second << std::endl;
  }
}
///////////////////////Tanker/////////////////////////
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

//////////////// AnimalShip methods//////////////////
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

void Fleet::loadCargo(const std::vector<Cargo> & cargoList) {
  for (std::vector<Cargo>::const_iterator cargoIt = cargoList.begin();
       cargoIt != cargoList.end();
       ++cargoIt) {
    bool loaded = false;
    for (std::vector<Ship *>::iterator shipIt = ships.begin(); shipIt != ships.end();
         ++shipIt) {
      if ((*shipIt)->canCarry(*cargoIt)) {
        std::cout << "**Loading the cargo onto " << (*shipIt)->getName() << "**\n";
        (*shipIt)->loadCargo(*cargoIt);
        loaded = true;
        break;
      }
    }
    if (!loaded) {
      std::cout << "No ships can carry the " << cargoIt->getName() << " from "
                << cargoIt->getSource() << " to " << cargoIt->getDestination() << "\n";
    }
  }
}

void Fleet::printShips() const {
  for (std::vector<Ship *>::const_iterator it = ships.begin(); it != ships.end(); ++it) {
    (*it)->printDetails();
  }
}
