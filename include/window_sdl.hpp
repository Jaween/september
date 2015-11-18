#ifndef WINDOW_SDL_HPP
#define WINDOW_SDL_HPP

#include <string>

#include "image_sdl.hpp"
#include "window.hpp"

class WindowSdl : public Window {
 public:
  WindowSdl(Image* image, const PixelFormat& pixel_format, std::string title);
  ~WindowSdl();
  virtual void refresh();

 private:
  void createWindow(unsigned int width, unsigned int height, const PixelFormat& pixel_format, std::string title);
  SDL_Window* window_ = NULL;
  SDL_Texture* texture_ = NULL;
  SDL_Renderer* renderer_ = NULL;
};

#endif // WINDOW_SDL_HPP
