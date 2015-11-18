#ifndef WINDOW_MANAGER_SDL_HPP
#define WINDOW_MANAGER_SDL_HPP

#include "image_sdl.hpp"
#include "window_manager.hpp"
#include "window_sdl.hpp"

class WindowManagerSdl : public WindowManager {
 public:
  WindowManagerSdl();
  ~WindowManagerSdl();
  virtual Window* createWindow(Image* image, const Window::PixelFormat& pixel_format, std::string title);
  virtual void sleep(long millis);
};

#endif // WINDOW_MANAGER_SDL_HPP
