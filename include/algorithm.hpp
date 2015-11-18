#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <CL/cl.hpp>
#include <string>

#include "image.hpp"

class Algorithm {
 public:
  Algorithm();
  ~Algorithm();
  void initialise();
  void compute(float shrink_factor, Image* current_frame, Image* screen);

 private:
  void initialiseOpenCL();
  std::string loadSource(std::string filename);
  void shink_image(float factor, Image* image);
  void background_removal(Image* image);
  void executeImageKernel(cl::Kernel& kernel, cl::Image2D& out_buffer, 
                          Image* out_image);

  cl::Context context_;
  cl::CommandQueue command_queue_;
  cl::Program program_;
};

#endif // ALGORITHM_H
