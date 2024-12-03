#ifndef SHIP_HPP
#define SHIP_HPP

#include <stdint.h>

#include <map>
#include <string>
#include <vector>
//////////////////////
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
////////////////////////////
class Ship {
 protected:
  std::string name;
  std::string typeInfo;
  std::string source;
  std::string destination;
  uint64_t capacity;
  uint64_t usedCapacity;

 public:
  Ship(const std::string & name,
       const std::string & typeInfo,
       const std::string & source,
       const std::string & destination,
       uint64_t capacity);
  virtual uint64_t getCapacity() const;
  virtual ~Ship() {}
  //virtual function every subclass have canCarry for <*Ship> use
  virtual bool canCarry(const Cargo & cargo) const = 0;
  virtual void loadCargo(const Cargo & cargo) = 0;

  const std::string & getName() const;
  const std::string & getSource() const;
  const std::string & getDestination() const;

  virtual void printDetails() const = 0;
};
//////////////////////////////
////////////////////////////////////////////////
//dleet class to manage a collection of ships
class Fleet {
 private:
  std::vector<Ship *> ships;
  std::map<std::pair<std::string, std::string>, uint64_t> routeCapacities;

 public:
  ~Fleet();
  const std::vector<Ship *> & getShips() const { return ships; }
  void addShip(Ship * ship);
  void computeRouteCapacities();
  void printRouteCapacities() const;
  void loadCargo(const std::vector<Cargo> & cargoList);  //Step 2
  void printShips() const;
};

#endif
