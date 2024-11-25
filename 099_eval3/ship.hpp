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

  virtual bool canCarry(const Cargo & cargo) const = 0;
  virtual void loadCargo(const Cargo & cargo) = 0;

  const std::string & getName() const;
  const std::string & getSource() const;
  const std::string & getDestination() const;

  virtual void printDetails() const = 0;
};
//////////////////////////////
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
//////////////////////////////////////////
class Tanker : public Ship {
 private:
  int minTemp;
  int maxTemp;
  unsigned int tanks;
  std::vector<std::string> hazmatCapabilities;
  std::vector<Cargo> loadedCargo;

 public:
  Tanker(const std::string & name,
         const std::string & typeInfo,
         const std::string & source,
         const std::string & destination,
         uint64_t capacity,
         int minTemp,
         int maxTemp,
         unsigned int tanks,
         const std::vector<std::string> & hazmatCapabilities) :
      Ship(name, typeInfo, source, destination, capacity),
      minTemp(minTemp),
      maxTemp(maxTemp),
      tanks(tanks),
      hazmatCapabilities(hazmatCapabilities) {}

  bool canCarry(const Cargo & cargo) const;
  void loadCargo(const Cargo & cargo);
  void printDetails() const;
};
////////////////////////////////////////////////
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
