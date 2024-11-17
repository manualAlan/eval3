#include "ship.hpp"

Ship::Ship(const std::string & name,
           const std::string & typeInfo,
           const std::string & source,
           const std::string & destination,
           uint64_t capacity) :
    name(name),
    typeInfo(typeInfo),
    source(source),
    destination(destination),
    capacity(capacity) {
}

const std::string & Ship::getName() const {
  return name;
}

//const std::string & Ship::getTypeInfo() const {
//  return typeInfo;
//}

const std::string & Ship::getSource() const {
  return source;
}

const std::string & Ship::getDestination() const {
  return destination;
}

uint64_t Ship::getCapacity() const {
  return capacity;
}

std::pair<std::string, std::string> Ship::getRoute() const {
  return std::make_pair(source, destination);
}
