#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "media_factory_sdl.hpp"
#include "image_sdl.hpp"
#include "window_manager_sdl.hpp"

MediaFactorySdl::MediaFactorySdl() {
  initialiseSdl();
}

MediaFactorySdl::~MediaFactorySdl() {
  Mix_FreeMusic(music_);
  music_ = NULL;

  Mix_Quit();
  IMG_Quit();
  SDL_Quit();
}

WindowManager* MediaFactorySdl::createWindowManager() {
  WindowManager* window_manager = new WindowManagerSdl();
  window_managers.push_back(window_manager);
  return window_manager;
}

Image* MediaFactorySdl::createImage(unsigned int width, unsigned int height, unsigned int words_per_pixel) {
  Image* image = new ImageSdl(width, height, words_per_pixel);
  images.push_back(image);
  return image;
}

bool MediaFactorySdl::initialiseSdl() {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
    std::cerr << "Failed to initialise SDL" << std::endl;
    return false;
  }

  int flags = IMG_INIT_PNG;
  if ((IMG_Init(flags) & flags) == -1) {
    std::cerr << "Failed to initialise SDL_image" << std::endl;
    return false;
  }

  if ((Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)) {
    std::cerr << "Failed to initialise SDL_mixer" << std::endl;
    return false;
  }

  return true;
}

void MediaFactorySdl::playAudio(std::string filename, bool loop) {
  music_ = Mix_LoadMUS(filename.c_str());
  if (music_ == NULL) {
    std::cerr << "Could not open " << filename << std::endl;
  }

  if (loop) {
    Mix_PlayMusic(music_, -1);
  } else {
    Mix_PlayMusic(music_, 1);
  }
}