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
void Cargo::setWeight(uint64_t newWeight) {
  weight = newWeight;  // Update the cargo weight
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
  // std::cout << "1" << std::endl;
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
///////////////////////////////////////////
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
