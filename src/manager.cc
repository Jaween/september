#include <iostream>

#include "manager.hpp"
#include "window_manager.hpp"

Manager::Manager(GraphicsFactory& graphics_factory) {
  algorithm_.initialise();

  current_frame_ = graphics_factory.createImage(640, 480, 1);

  previous_frame_ = graphics_factory.createImage(640, 480, 1);

  screen_ = graphics_factory.createImage(640, 480, 1);

  window_manager_ = graphics_factory.createWindowManager();
  window_manager_->createWindow(screen_, Window::PixelFormat::ABGR, "Earth, Wind and Fire");
}

Manager::~Manager() {
}

void Manager::start() {
  algorithm_.execute(current_frame_, previous_frame_, screen_);

  window_manager_->refresh();

  long sleep_millis = 1000;
  window_manager_->sleep(sleep_millis);
}
