#include "utilfunc.hpp"

#include <stdint.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
//function to read ships from the file and populates the fleet
void readShips(const std::string & filename, Fleet & fleet) {
  std::ifstream file(filename.c_str());
  if (!file) {
    std::cerr << "could not open file " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string name, typeInfo, source, destination;
    uint64_t capacity;

    //parse the ship details from the line
    std::getline(iss, name, ':');
    std::getline(iss, typeInfo, ':');
    std::getline(iss, source, ':');
    std::getline(iss, destination, ':');
    if (!(iss >> capacity)) {
      std::cerr << "Error: Malformed input in line: " << line << std::endl;
      std::exit(EXIT_FAILURE);
    }

    if (typeInfo.find("Container") ==
        0) {  //if the ship is a ContainerShip, parse additional details
      std::istringstream typeStream(typeInfo);
      std::string type;
      std::string slotsStr;

      std::string hazmatStr;
      std::getline(typeStream, type, ',');  //parse container detail
      std::getline(typeStream, slotsStr, ',');
      unsigned int slots = std::strtol(slotsStr.c_str(), NULL, 10);

      std::vector<std::string> hazmatCapabilities;
      while (std::getline(typeStream, hazmatStr, ',')) {
        hazmatCapabilities.push_back(hazmatStr);
      }

      fleet.addShip(new ContainerShip(
          name, typeInfo, source, destination, capacity, slots, hazmatCapabilities));
    }  //create a new ContainerShip and add it to the fleet
  }
}

//compare function for sorting ships by name
bool shipCompare(Ship * a, Ship * b) {
  return a->getName() < b->getName();
}

//find eligible ships for a given cargo
std::vector<Ship *> findEligibleShips(const Cargo & cargo, const Fleet & fleet) {
  std::vector<Ship *> eligibleShips;
  //find eligible one iteratively
  for (std::vector<Ship *>::const_iterator shipIt = fleet.getShips().begin();
       shipIt != fleet.getShips().end();
       ++shipIt) {
    if ((*shipIt)->canCarry(cargo)) {
      eligibleShips.push_back(*shipIt);
    }
  }

  //sort eligible ships alphabeticaly
  std::sort(eligibleShips.begin(), eligibleShips.end(), shipCompare);

  return eligibleShips;
}

//process cargo loading
void processCargo(const std::vector<Cargo> & cargoList, Fleet & fleet) {
  for (std::vector<Cargo>::const_iterator cargoIt = cargoList.begin();
       cargoIt != cargoList.end();
       ++cargoIt) {
    const Cargo & cargo = *cargoIt;

    //find eligible ships
    std::vector<Ship *> eligibleShips = findEligibleShips(cargo, fleet);

    //print eligible ships and load the first one if possible
    if (!eligibleShips.empty()) {
      std::cout << eligibleShips.size() << " ships can carry the " << cargo.getName()
                << " from " << cargo.getSource() << " to " << cargo.getDestination()
                << std::endl;

      for (std::vector<Ship *>::const_iterator shipIt = eligibleShips.begin();
           shipIt != eligibleShips.end();
           ++shipIt) {
        std::cout << "  " << (*shipIt)->getName() << std::endl;
      }

      //;oad the cargo onto the first eligible ship
      eligibleShips[0]->loadCargo(cargo);
      std::cout << "  **Loading the cargo onto " << eligibleShips[0]->getName() << "**"
                << std::endl;
    }
    else {
      //if no eligible ships, print a message
      std::cout << "No ships can carry the " << cargo.getName() << " from "
                << cargo.getSource() << " to " << cargo.getDestination() << std::endl;
    }
  }
}

//  read cargo details from the file
std::vector<Cargo> readCargo(const std::string & filename) {
  std::ifstream file(filename.c_str());
  if (!file) {
    std::cerr << "Could not open file " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::vector<Cargo> cargoList;
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string name, source, destination, weightStr, property;
    uint64_t weight;
    //Parse the cargo details from the line
    std::getline(iss, name, ',');
    std::getline(iss, source, ',');
    std::getline(iss, destination, ',');
    std::getline(iss, weightStr, ',');
    weight = std::strtoull(weightStr.c_str(), NULL, 10);
    //parse the cargo properties
    std::vector<std::string> properties;
    while (std::getline(iss, property, ',')) {
      properties.push_back(property);
    }
    //add to the cargo list
    cargoList.push_back(Cargo(name, source, destination, weight, properties));
  }

  return cargoList;
}
