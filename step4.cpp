#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "avlmultimap03.hpp"
#include "ship.hpp"
#include "utilfunc.hpp"
int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <ships file> <cargo file>" << std::endl;
    return EXIT_FAILURE;
  }

  // Create a Fleet object
  Fleet fleet;

  // Read ships from file and populate the fleet
  readShips(argv[1], fleet);

  // Read cargo from file
  std::vector<Cargo> cargoList = readCargo(argv[2]);

  // Load cargo onto ships
  fleet.loadCargo(cargoList);

  // Print ships after loading
  std::cout << "---Done Loading---Here are the ships---" << std::endl;
  fleet.printShips();

  return EXIT_SUCCESS;
}
