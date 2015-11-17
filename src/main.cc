
#include <stdlib.h>

#include "graphics_factory_sdl.hpp"
#include "manager.hpp"

int main(int argc, char* argv[]) {

  GraphicsFactorySdl graphics_factory_sdl = GraphicsFactorySdl();

  Manager manager = Manager(graphics_factory_sdl);
  manager.start();

  return EXIT_SUCCESS;
}
