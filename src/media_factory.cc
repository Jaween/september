#include "media_factory.hpp"

MediaFactory::~MediaFactory() {
  for(WindowManager* window_manager : window_managers) {
    delete window_manager;
  }

  for(Image* image : images) {
    delete image;
  }
}
