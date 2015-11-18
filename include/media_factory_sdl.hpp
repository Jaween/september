#ifndef MEDIA_FACTORY_SDL_HPP
#define MEDIA_FACTORY_SDL_HPP

#include <SDL2/SDL_mixer.h>

#include "media_factory.hpp"

class MediaFactorySdl : public MediaFactory {
 public:
  MediaFactorySdl();
  ~MediaFactorySdl();
  virtual WindowManager* createWindowManager();
  virtual Image* createImage(unsigned int width, unsigned int height, unsigned int words_per_pixel);
  virtual void playAudio(std::string filename, bool loop);

 private:
  bool initialiseSdl();
  Mix_Music* music_;
};

#endif // MEDIA_FACTORY_SDL_HPP
