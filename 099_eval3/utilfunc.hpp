#ifndef UTILFUNC_HPP
#define UTILFUNC_HPP

#include <map>
#include <set>
#include <string>
#include <vector>

#include "cargo.hpp"
#include "ship.hpp"

void parseShipFile(
    const std::string & filename,
    std::map<std::pair<std::string, std::string>, uint64_t> & routeCapacity,
    std::set<std::string> & shipNames);

std::vector<Cargo> parseCargoFile(const std::string & filename);

void printRouteCapacities(
    const std::map<std::pair<std::string, std::string>, uint64_t> & routeCapacity);

#endif
