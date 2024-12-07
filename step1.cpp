#include <cstdlib>
#include <iostream>

#include "ship.hpp"
#include "utilfunc.hpp"
int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "wrong input" << std::endl;
    return EXIT_FAILURE;
  }
  Fleet fleet;

  //read ships from the file
  readShips(argv[1], fleet);
  //compute and print route capacity
  fleet.computeRouteCapacities();
  fleet.printRouteCapacities();
  return 0;
}
