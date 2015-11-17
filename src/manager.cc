#include <iostream>

#include "manager.hpp"
#include "window_manager.hpp"

Manager::Manager(GraphicsFactory& graphics_factory) {
  algorithm_.initialise();
  std::cout << "Success!" << std::endl;

  image_ = graphics_factory.createImage(640, 480, 1);
  image_->fill(0x00);

  window_manager_ = graphics_factory.createWindowManager();
  window_manager_->createWindow(image_, Window::PixelFormat::RGB, "Earth, Wind and Fire");
}

Manager::~Manager() {
}

void Manager::start() {
  window_manager_->refresh();
  
  long sleep_millis = 1000;
  window_manager_->sleep(sleep_millis);
}
