#ifndef UTILS_HPP
#define UTILS_HPP

#include <map>
#include <set>
#include <string>

#include "ship.hpp"

//parse the ship file and updates the route capacities and ship name
void parseShipFile(
    const std::string & filename,
    std::map<std::pair<std::string, std::string>, uint64_t> & routeCapacity,
    std::set<std::string> & shipNames);

//Prints the total capacities of all routes
void printRouteCapacities(
    const std::map<std::pair<std::string, std::string>, uint64_t> & routeCapacity);

#endif
