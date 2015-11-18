
#include <stdlib.h>

#include "media_factory_sdl.hpp"
#include "manager.hpp"

int main(int argc, char* argv[]) {

  MediaFactorySdl media_factory_sdl = MediaFactorySdl();

  Manager manager = Manager(media_factory_sdl);
  manager.start();

  return EXIT_SUCCESS;
}
