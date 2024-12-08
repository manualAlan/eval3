#include "ship.hpp"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
///////////////////////cargo

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
  shipMap.add(ship->getCapacity() - ship->getUsedCapacity(), ship);  //  new for step4
}

void Fleet::computeRouteCapacities() {
  routeCapacities.clear();
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
bool compareWeight(const Cargo & a, const Cargo & b) {
  return a.getWeight() > b.getWeight();
}
void Fleet::loadCargo(const std::vector<Cargo> & cargoList) {
  // Sort cargo list from largest to smallest weight
  std::vector<Cargo> sortedCargoList = cargoList;
  std::stable_sort(sortedCargoList.begin(), sortedCargoList.end(), compareWeight);

  // Iterate over each cargo
  for (std::vector<Cargo>::const_iterator cargoIt = sortedCargoList.begin();
       cargoIt != sortedCargoList.end();
       ++cargoIt) {
    const Cargo & cargo = *cargoIt;

    // Get all entries in the AVL tree
    std::vector<std::pair<std::pair<uint64_t, std::set<Ship *> >, int> > treeContents =
        shipMap.preOrderDump();

    Ship * bestFit = NULL;
    uint64_t minWaste = UINT64_MAX;

    // Iterate over the AVL tree contents to find the best fit
    for (std::vector<
             std::pair<std::pair<uint64_t, std::set<Ship *> >, int> >::const_iterator it =
             treeContents.begin();
         it != treeContents.end();
         ++it) {
      uint64_t remainingCapacity = it->first.first;
      const std::set<Ship *> & ships = it->first.second;

      if (remainingCapacity >= cargo.getWeight()) {
        for (std::set<Ship *>::const_iterator shipIt = ships.begin();
             shipIt != ships.end();
             ++shipIt) {
          if ((*shipIt)->canCarry(cargo)) {
            uint64_t waste = remainingCapacity - cargo.getWeight();
            if (waste < minWaste ||
                (waste == minWaste && (*shipIt)->getName() < bestFit->getName())) {
              bestFit = *shipIt;
              minWaste = waste;
            }
          }
        }
      }
    }

    if (bestFit != NULL) {
      // Remove ship from AVL tree
      shipMap.remove(bestFit->getCapacity() - bestFit->getUsedCapacity(), bestFit);

      // Load the cargo onto the best-fit ship
      bestFit->loadCargo(cargo);

      // Calculate remaining capacity after loading
      uint64_t remainingCapacity = bestFit->getCapacity() - bestFit->getUsedCapacity();

      // Reinsert ship into AVL tree
      shipMap.add(remainingCapacity, bestFit);

      // Print detailed loading message
      std::cout << "Loading " << cargo.getName() << " onto " << bestFit->getName()
                << " from " << cargo.getSource() << " to " << cargo.getDestination()
                << " " << remainingCapacity << " capacity remains" << std::endl;
    }
    else {
      std::cout << "No ships can carry the " << cargo.getName() << " from "
                << cargo.getSource() << " to " << cargo.getDestination() << std::endl;
    }
  }
}

void Fleet::printShips() const {
  for (std::vector<Ship *>::const_iterator it = ships.begin(); it != ships.end(); ++it) {
    (*it)->printDetails();
  }
}
