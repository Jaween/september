#include "window_manager_sdl.hpp"

WindowManagerSdl::WindowManagerSdl() {

}

WindowManagerSdl::~WindowManagerSdl() {
  SDL_Quit();
}

Window* WindowManagerSdl::createWindow(Image* image, const Window::PixelFormat& pixel_format, std::string title) {
  Window* window = new WindowSdl(image, pixel_format, title);
  windows_.push_back(window);
  return window;
}

void WindowManagerSdl::sleep(long millis) {
  SDL_Delay(millis);
}