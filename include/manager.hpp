#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "algorithm.hpp"
#include "graphics_factory.hpp"
#include "image.hpp"
#include "window_manager.hpp"

class Manager {
 public:
  Manager(GraphicsFactory& graphics_factory);
  ~Manager();
  void start();
  void loadImage(int frame);

 private:
  Algorithm algorithm_;
  Image* current_frame_;
  Image* screen_;
  WindowManager* window_manager_;
};

#endif // MANAGER_HPP
