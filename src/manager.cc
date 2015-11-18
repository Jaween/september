#include <iostream>
#include <sstream>

#include "manager.hpp"
#include "window_manager.hpp"

Manager::Manager(GraphicsFactory& graphics_factory) {
  algorithm_.initialise();

  // Creates two blank images, one for the video frame the other for display
  current_frame_ = graphics_factory.createImage(540, 300, 1);
  screen_ = graphics_factory.createImage(540, 300, 1);

  // Creates the output window
  window_manager_ = graphics_factory.createWindowManager();
  window_manager_->createWindow(screen_, Window::PixelFormat::ABGR, 
                                "Earth, Wind and Fire");
}

Manager::~Manager() {
} 

void Manager::start() {
  int frames_per_loop = 20;
  for (int frame = 0; frame < 160; frame++) {
    // Loads a new video frame
    std::cout << "Frame " << frame << std::endl;
    std::stringstream stringstream;
    stringstream << "res/frame_";
    stringstream << (frame % frames_per_loop);
    stringstream << ".png";
    current_frame_->load(stringstream.str());

    // Performs the GPU execution
    const float shrink_factor = 0.1f; 
    algorithm_.compute(shrink_factor, current_frame_, screen_);
    screen_->blit(current_frame_);
    
    // Updates the window
    window_manager_->refresh();
    window_manager_->sleep(32);
  }
}
