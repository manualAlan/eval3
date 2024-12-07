#ifndef UTILFUNC_HPP
#define UTILFUNC_HPP

#include <string>
#include <vector>

#include "AnimalShip.hpp"
#include "ContainerShip.hpp"
#include "Tanker.hpp"
#include "ship.hpp"
//to read ships from an input file
void readShips(const std::string & filename, Fleet & fleet);

//read cargo from an input file
std::vector<Cargo> readCargo(const std::string & filename);

//compare ships by name
bool shipCompare(Ship * a, Ship * b);

//find eligible ships for a given cargo
std::vector<Ship *> findEligibleShips(const Cargo & cargo, const Fleet & fleet);

//process and load cargo onto ships
void processCargo(const std::vector<Cargo> & cargoList, Fleet & fleet);
#endif
