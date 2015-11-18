#include "window_manager.hpp"

WindowManager::~WindowManager() {
  for (Window* window : windows_) {
    delete window;
  }
}

void WindowManager::refresh() {
  for (int i = 0; i < windows_.size(); i++) {
    windows_.at(i)->refresh();
  }
}
