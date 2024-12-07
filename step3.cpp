#include <algorithm>
#include <cstdlib>
#include <iostream>

#include "utilfunc.hpp"

int main(int argc, char ** argv) {
  if (argc != 3) {
    std::cerr << "input " << argv[0] << " ships_file cargo_file" << std::endl;
    return EXIT_FAILURE;
  }
  Fleet fleet;

  //Read ships from the file
  readShips(argv[1], fleet);

  //read cargo from the file
  std::vector<Cargo> cargoList = readCargo(argv[2]);

  //Process cargo loading
  processCargo(cargoList, fleet);

  //print all ships and their details
  std::cout << "---Done Loading---Here are the ships---" << std::endl;
  fleet.printShips();

  return 0;
}
