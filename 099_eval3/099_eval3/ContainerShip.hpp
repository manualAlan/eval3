#ifndef CONTAINERSHIP_HPP
#define CONTAINERSHIP_HPP

#include <string>
#include <vector>

#include "ship.hpp"

class ContainerShip : public Ship {
 private:
  unsigned int slots;
  std::vector<std::string> hazmatCapabilities;
  std::vector<Cargo> loadedCargo;

 public:
  ContainerShip(const std::string & name,
                const std::string & typeInfo,
                const std::string & source,
                const std::string & destination,
                uint64_t capacity,
                unsigned int slots,
                const std::vector<std::string> & hazmatCapabilities);

  virtual bool canCarry(const Cargo & cargo) const;
  virtual void loadCargo(const Cargo & cargo);
  virtual void printDetails() const;
};
#endif
