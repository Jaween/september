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
  void execute(Image* current_frame, Image* previous_frame, Image* screen);

 private:
  void initialiseOpenCL();
  std::string loadSource(std::string filename);
  void executeImageKernel(cl::Kernel& kernel, cl::Image2D& out_buffer, Image* out_image);

  cl::Context context_;
  cl::CommandQueue command_queue_;
  cl::Program program_;
};

#endif // ALGORITHM_H
