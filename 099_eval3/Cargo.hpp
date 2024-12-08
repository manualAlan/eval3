#ifndef CARGO_HPP
#define CARGO_HPP
#include <stdint.h>

#include <map>
#include <string>
#include <vector>

class Ship;
class Cargo {
 private:
  std::string name;
  std::string source;
  std::string destination;
  uint64_t weight;
  std::vector<std::string> properties;

 public:
  Cargo(const std::string & name,
        const std::string & source,
        const std::string & destination,
        uint64_t weight,
        const std::vector<std::string> & properties);
  void setWeight(uint64_t newWeight);
  const std::string & getName() const;
  const std::string & getSource() const;
  const std::string & getDestination() const;
  uint64_t getWeight() const;
  const std::vector<std::string> & getProperties() const;
};
#endif
