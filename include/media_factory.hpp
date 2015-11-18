#ifndef MEDIA_FACTORY_HPP
#define MEDIA_FACTORY_HPP

#include <string>

#include "image.hpp"
#include "window_manager.hpp"

class MediaFactory {
 public:
  ~MediaFactory();
  virtual WindowManager* createWindowManager() = 0;
  virtual Image* createImage(unsigned int width, unsigned int height, unsigned int words_per_pixel) = 0;
  virtual void playAudio(std::string filename, bool loop) = 0;

 protected:
  std::vector<WindowManager*> window_managers;
  std::vector<Image*> images;
};

#endif // MEDIA_FACTORY_HPP
