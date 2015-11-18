#include <iostream>
#include <string>

#include "window_sdl.hpp"

WindowSdl::WindowSdl(Image* image, const PixelFormat& pixel_format, std::string title) : Window(image, pixel_format, title) {
  createWindow(image->getWidth(), image->getHeight(), pixel_format, title);
}

WindowSdl::~WindowSdl() {
  SDL_DestroyTexture(texture_);

  SDL_RenderClear(renderer_);
  SDL_DestroyRenderer(renderer_);

  SDL_DestroyWindow(window_);
}

void WindowSdl::createWindow(unsigned int width, unsigned int height, const PixelFormat& pixel_format, std::string title) {
  window_ = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
  if (window_ != NULL) {
    unsigned int options = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    renderer_ = SDL_CreateRenderer(window_, -1, options);
    if (renderer_ == NULL) {
      std::cerr << "Failed to create renderer, SDL error " << SDL_GetError() << std::endl;
      window_ = NULL;
    } else {
      SDL_SetRenderDrawColor(renderer_, 0xFF, 0xFF, 0xFF, 0xFF);

      unsigned int sdl_pixel_format;
      switch (pixel_format) {
        case RGB:
          sdl_pixel_format = SDL_PIXELFORMAT_RGB24;
          break;
        case ABGR:
          sdl_pixel_format = SDL_PIXELFORMAT_ABGR8888;
          break;
        case GREY:
        default:
          std::cout << "Window: Setting pixel format to ABGR8888" << std::endl;
          sdl_pixel_format = SDL_PIXELFORMAT_ABGR8888;
      }
      texture_ = SDL_CreateTexture(renderer_, sdl_pixel_format, SDL_TEXTUREACCESS_STREAMING, width, height);
    }
  } else {
    std::cerr << "Window could not be created, SDL Error " << SDL_GetError() << std::endl;
  }
}

void WindowSdl::refresh() {
  // ?? TODO(jaween): Is this the way concrete classes created from a factory access extended functionality?
  SDL_Surface* surface = static_cast<ImageSdl*>(image_)->getSurface();
  if (surface != NULL)
  {
    SDL_UpdateTexture(texture_, NULL, surface->pixels, surface->pitch);
  }

  // Renders using the GPU
  SDL_RenderClear(renderer_);
  SDL_RenderCopy(renderer_, texture_, NULL, NULL);
  SDL_RenderPresent(renderer_);
}
