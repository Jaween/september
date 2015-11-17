#include "graphics_factory.hpp"

GraphicsFactory::~GraphicsFactory() {
  for(WindowManager* window_manager : window_managers) {
    delete window_manager;
  }

  for(Image* image : images) {
    delete image;
  }
}
