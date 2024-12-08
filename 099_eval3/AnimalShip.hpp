#ifndef ANIMALSHIP_HPP
#define ANIMALSHIP_HPP
#include <string>
#include <vector>
//extend from superclass Ship
#include "ship.hpp"
class AnimalShip : public Ship {
 private:
  unsigned int smallThreshold;
  bool hasRoamer;
  std::vector<Cargo> loadedCargo;

 public:
  AnimalShip(const std::string & name,
             const std::string & typeInfo,
             const std::string & source,
             const std::string & destination,
             uint64_t capacity,
             unsigned int smallThreshold) :
      Ship(name, typeInfo, source, destination, capacity),
      smallThreshold(smallThreshold),
      hasRoamer(false) {}

  bool canCarry(const Cargo & cargo) const;
  void loadCargo(const Cargo & cargo);
  void printDetails() const;
};

#endif
