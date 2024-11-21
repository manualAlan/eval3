#include <algorithm>
#include <iostream>
#include <vector>

#include "cargo.hpp"
#include "ship.hpp"
#include "utilfunc.hpp"

int main(int argc, char * argv[]) {
  if (argc != 3) {
    std::cerr << "wrong number of arguments\n";
    exit(EXIT_FAILURE);
  }

  std::map<std::pair<std::string, std::string>, uint64_t> routeCapacity;
  std::set<std::string> shipNames;
  std::vector<Ship> ships;

  parseShipFile(argv[1], routeCapacity, shipNames);

  for (std::map<std::pair<std::string, std::string>, uint64_t>::const_iterator it =
           routeCapacity.begin();
       it != routeCapacity.end();
       ++it) {
    ships.push_back(Ship(
        it->first.first, "Container", it->first.second, it->first.second, it->second));
  }

  std::vector<Cargo> cargoList = parseCargoFile(argv[2]);

  for (size_t i = 0; i < cargoList.size(); ++i) {
    Cargo & cargo = cargoList[i];
    std::vector<std::string> eligibleShips;

    for (size_t j = 0; j < ships.size(); ++j) {
      if (ships[j].canCarryCargo(
              cargo.source, cargo.destination, cargo.weight, cargo.properties)) {
        eligibleShips.push_back(ships[j].getName());
      }
    }

    if (eligibleShips.empty()) {
      std::cout << "no ships can carry " << cargo.name << " from " << cargo.source
                << " to " << cargo.destination << std::endl;
    }
    else {
      std::sort(eligibleShips.begin(), eligibleShips.end());
      std::cout << eligibleShips.size() << " ships can carry the " << cargo.name
                << " from " << cargo.source << " to " << cargo.destination << std::endl;

      for (size_t j = 0; j < eligibleShips.size(); ++j) {
        std::cout << "  " << eligibleShips[j] << std::endl;
      }

      std::cout << "**Loading the cargo onto " << eligibleShips[0] << "**" << std::endl;
    }
  }

  return 0;
}
