#ifndef UTILFUNC_HPP
#define UTILFUNC_HPP

#include <string>
#include <vector>

#include "AnimalShip.hpp"
#include "ContainerShip.hpp"
#include "Tanker.hpp"
#include "ship.hpp"
// Function to read ships from an input file
void readShips(const std::string & filename, Fleet & fleet);

// Function to read cargo from an input file
std::vector<Cargo> readCargo(const std::string & filename);

// Function to compare ships by name
bool shipCompare(Ship * a, Ship * b);

// Find eligible ships for a given cargo
std::vector<Ship *> findEligibleShips(const Cargo & cargo, const Fleet & fleet);

// Process and load cargo onto ships
void processCargo(const std::vector<Cargo> & cargoList, Fleet & fleet);
#endif
