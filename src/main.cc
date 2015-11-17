#include <stdlib.h>

#include "manager.hpp"

int main(int argc, char* argv[]) {
  Manager manager = Manager();
  manager.start();

  return EXIT_SUCCESS;
}
