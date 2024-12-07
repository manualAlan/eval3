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
    std::cerr << "Error: Could not open file " << filename << std::endl;
    std::exit(EXIT_FAILURE);
  }

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string name, typeInfo, source, destination;
    uint64_t capacity;

    std::getline(iss, name, ':');
    std::getline(iss, typeInfo, ':');
    std::getline(iss, source, ':');
    std::getline(iss, destination, ':');
    if (!(iss >> capacity)) {
      std::cerr << "Error: Malformed input in line: " << line << std::endl;
      std::exit(EXIT_FAILURE);
    }

    if (typeInfo.find("Container") == 0) {
      std::istringstream typeStream(typeInfo);
      std::string type, slotsStr, hazmatStr;
      std::getline(typeStream, type, ',');
      std::getline(typeStream, slotsStr, ',');
      unsigned int slots = std::strtol(slotsStr.c_str(), NULL, 10);

      std::vector<std::string> hazmatCapabilities;
      while (std::getline(typeStream, hazmatStr, ',')) {
        hazmatCapabilities.push_back(hazmatStr);
      }

      fleet.addShip(new ContainerShip(
          name, typeInfo, source, destination, capacity, slots, hazmatCapabilities));
    }
    else if (typeInfo.find("Tanker") == 0) {
      std::istringstream typeStream(typeInfo);
      std::string type;
      int minTemp, maxTemp;
      unsigned int tanks;
      std::string hazmatStr;

      std::getline(typeStream, type, ',');
      typeStream >> minTemp;
      typeStream.ignore(1, ',');
      typeStream >> maxTemp;
      typeStream.ignore(1, ',');
      typeStream >> tanks;

      std::vector<std::string> hazmatCapabilities;
      while (std::getline(typeStream, hazmatStr, ',')) {
        hazmatCapabilities.push_back(hazmatStr);
      }

      fleet.addShip(new Tanker(name,
                               typeInfo,
                               source,
                               destination,
                               capacity,
                               minTemp,
                               maxTemp,
                               tanks,
                               hazmatCapabilities));
    }
    else if (typeInfo.find("Animals") == 0) {
      std::istringstream typeStream(typeInfo);
      std::string type;
      unsigned int smallThreshold;

      std::getline(typeStream, type, ',');
      typeStream >> smallThreshold;

      fleet.addShip(
          new AnimalShip(name, typeInfo, source, destination, capacity, smallThreshold));
    }
    else {
      std::cerr << "Error: Unknown ship type in line: " << line << std::endl;
      std::exit(EXIT_FAILURE);
    }
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

    //split the line into fields and count them
    std::vector<std::string> fields;
    while (std::getline(iss, property, ',')) {
      fields.push_back(property);
    }

    if (fields.size() < 5) {
      std::cerr << "Cargo to load has to have at least 5 parts, but" << line
                << "has only " << fields.size() << std::endl;
      std::exit(EXIT_FAILURE);
    }

    //parse the mandatory fields
    name = fields[0];
    source = fields[1];
    destination = fields[2];
    weightStr = fields[3];
    uint64_t weight = std::strtoull(weightStr.c_str(), NULL, 10);

    //extract remaining fields as properties
    std::vector<std::string> properties(fields.begin() + 4, fields.end());

    //add the cargo to the list
    cargoList.push_back(Cargo(name, source, destination, weight, properties));
  }

  return cargoList;
}
