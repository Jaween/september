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

 private:
  Algorithm algorithm_;
  Image* image_;
  WindowManager* window_manager_;
};

#endif // MANAGER_HPP
