#ifndef TANKER_HPP
#define TANKER_HPP
#include <string>
#include <vector>

#include "ship.hpp"
class Tanker : public Ship {
 private:
  int minTemp;
  int maxTemp;
  unsigned int tanks;
  std::vector<std::string> hazmatCapabilities;
  std::vector<Cargo> loadedCargo;

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
      hazmatCapabilities(hazmatCapabilities) {}

  bool canCarry(const Cargo & cargo) const;
  void loadCargo(const Cargo & cargo);
  void printDetails() const;
};
#endif
