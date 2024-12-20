#ifndef SHIP_HPP
#define SHIP_HPP
#include <stdint.h>
//#include <cstdint>
#include <string>
#include <utility>

class Ship {
 private:
  std::string name;
  std::string typeInfo;
  std::string source;
  std::string destination;
  uint64_t capacity;

 public:
  Ship(const std::string & name,
       const std::string & typeInfo,
       const std::string & source,
       const std::string & destination,
       uint64_t capacity);

  const std::string & getName() const;
  const std::string & getTypeInfo() const;
  const std::string & getSource() const;
  const std::string & getDestination() const;
  uint64_t getCapacity() const;

  std::pair<std::string, std::string> getRoute() const;
};

#endif
