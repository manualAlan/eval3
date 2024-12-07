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

  //fleet obj
  Fleet fleet;

  /// populate the fleet
  readShips(argv[1], fleet);

  //read cargo from file
  std::vector<Cargo> cargoList = readCargo(argv[2]);

  //load cargo onto ships
  fleet.loadCargo(cargoList);

  //print ships after loading
  std::cout << "---Done Loading---Here are the ships---" << std::endl;
  fleet.printShips();

  return EXIT_SUCCESS;
}
