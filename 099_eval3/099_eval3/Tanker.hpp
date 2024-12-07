#ifndef TANKER_HPP
#define TANKER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "ship.hpp"
struct Tank {
  std::string cargoType;  // Type of cargo in the tank (e.g., "liquid hydrogen")
  uint64_t used;
  // Amount of capacity used in this tank
  Tank() : cargoType(""), used(0) {}
};
class Tanker : public Ship {
 private:
  int minTemp;
  int maxTemp;
  unsigned int tanks;
  std::vector<std::string> hazmatCapabilities;
  std::vector<Cargo> loadedCargo;
  std::string cargoType;
  std::vector<Tank> tankStatus;

 public:
  Tanker(const std::string & name,
         const std::string & typeInfo,
         const std::string & source,
         const std::string & destination,
         uint64_t capacity,
         int minTemp,
         int maxTemp,
         unsigned int tanks,
         const std::vector<std::string> & hazmatCapabilities) :
      Ship(name, typeInfo, source, destination, capacity),
      minTemp(minTemp),
      maxTemp(maxTemp),
      tanks(tanks),
      hazmatCapabilities(hazmatCapabilities) {
    if (capacity % tanks != 0) {
      std::cerr << "Error: Tanker capacity is not divisible by the number of tanks."
                << std::endl;
      std::exit(EXIT_FAILURE);
    }

    // Initialize the tankStatus vector with empty tanks
    for (unsigned int i = 0; i < tanks; ++i) {
      Tank emptyTank;
      tankStatus.push_back(emptyTank);
    }
  }

  bool canCarry(const Cargo & cargo) const;
  void loadCargo(const Cargo & cargo);
  void printDetails() const;
};
#endif
