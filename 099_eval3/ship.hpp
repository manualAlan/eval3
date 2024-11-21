#ifndef SHIP_HPP
#define SHIP_HPP

#include <stdint.h>  // For uint64_t

#include <set>
#include <string>

class Ship {
 private:
  std::string name;
  std::string typeInfo;
  std::string source;
  std::string destination;
  uint64_t capacity;
  uint64_t usedCapacity;
  size_t slots;
  size_t usedSlots;
  std::set<std::string> hazmatCapabilities;

 public:
  Ship(const std::string & name,
       const std::string & typeInfo,
       const std::string & source,
       const std::string & destination,
       uint64_t capacity);

  const std::string & getName() const;
  const std::string & getSource() const;
  const std::string & getDestination() const;
  uint64_t getCapacity() const;
  uint64_t getUsedCapacity() const;
  size_t getSlots() const;
  size_t getUsedSlots() const;
  std::pair<std::string, std::string> getRoute() const;
  bool canCarryCargo(const std::string & cargoSource,
                     const std::string & cargoDestination,
                     uint64_t cargoWeight,
                     const std::set<std::string> & cargoProperties) const;
  void loadCargo(uint64_t cargoWeight);
  std::string getDescription() const;
};

#endif