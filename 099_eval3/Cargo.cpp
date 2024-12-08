#include "Cargo.hpp"

#include <stdint.h>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ship.hpp"
///////////////////////cargo
Cargo::Cargo(const std::string & name,
             const std::string & source,
             const std::string & destination,
             uint64_t weight,
             const std::vector<std::string> & properties) :
    name(name),
    source(source),
    destination(destination),
    weight(weight),
    properties(properties) {
}

const std::string & Cargo::getName() const {
  return name;
}

const std::string & Cargo::getSource() const {
  return source;
}

const std::string & Cargo::getDestination() const {
  return destination;
}

uint64_t Cargo::getWeight() const {
  return weight;
}
void Cargo::setWeight(uint64_t newWeight) {
  weight = newWeight;  // Update the cargo weight
}
const std::vector<std::string> & Cargo::getProperties() const {
  return properties;
}
