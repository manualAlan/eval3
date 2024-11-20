#ifndef CARGO_HPP
#define CARGO_HPP
#include <stdint.h>

#include <cstdlib>
#include <set>
#include <string>

class Cargo {
 public:
  std::string name;
  std::string source;
  std::string destination;
  uint64_t weight;
  std::set<std::string> properties;
  Cargo(const std::string & line);
};

#endif
