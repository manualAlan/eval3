#include "ship.hpp"

#include <cstdlib>  // For strtoul
#include <sstream>

Ship::Ship(const std::string & name,
           const std::string & typeInfo,
           const std::string & source,
           const std::string & destination,
           uint64_t capacity) :
    name(name),
    typeInfo(typeInfo),
    source(source),
    destination(destination),
    capacity(capacity),
    usedCapacity(0),
    slots(0),
    usedSlots(0) {
  if (typeInfo.find("Container") == 0) {
    size_t commaPos = typeInfo.find(',', 9);
    if (commaPos != std::string::npos) {
      slots = strtoul(typeInfo.substr(9, commaPos - 9).c_str(), NULL, 10);
    }
    std::string capabilityList = typeInfo.substr(commaPos + 1);
    std::istringstream iss(capabilityList);
    std::string capability;
    while (std::getline(iss, capability, ',')) {
      hazmatCapabilities.insert(capability);
    }
  }
}

const std::string & Ship::getName() const {
  return name;
}
const std::string & Ship::getSource() const {
  return source;
}
const std::string & Ship::getDestination() const {
  return destination;
}
uint64_t Ship::getCapacity() const {
  return capacity;
}
uint64_t Ship::getUsedCapacity() const {
  return usedCapacity;
}
size_t Ship::getSlots() const {
  return slots;
}
size_t Ship::getUsedSlots() const {
  return usedSlots;
}

std::pair<std::string, std::string> Ship::getRoute() const {
  return std::make_pair(source, destination);
}

bool Ship::canCarryCargo(const std::string & cargoSource,
                         const std::string & cargoDestination,
                         uint64_t cargoWeight,
                         const std::set<std::string> & cargoProperties) const {
  if (source != cargoSource || destination != cargoDestination) {
    return false;
  }
  if (usedCapacity + cargoWeight > capacity) {
    return false;
  }
  if (usedSlots >= slots) {
    return false;
  }
  if (cargoProperties.count("container") == 0) {
    return false;
  }
  for (std::set<std::string>::const_iterator it = cargoProperties.begin();
       it != cargoProperties.end();
       ++it) {
    if (it->find("hazardous-") == 0 &&
        hazmatCapabilities.find(it->substr(10)) == hazmatCapabilities.end()) {
      return false;
    }
  }
  return true;
}

void Ship::loadCargo(uint64_t cargoWeight) {
  usedCapacity += cargoWeight;
  usedSlots += 1;
}

std::string Ship::getDescription() const {
  std::ostringstream oss;
  oss << "The Container Ship " << name << "(" << usedCapacity << "/" << capacity
      << ") is carrying:\n";
  oss << "  (" << (slots - usedSlots) << ") slots remain";
  return oss.str();
}
