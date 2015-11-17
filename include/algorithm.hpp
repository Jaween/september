#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <CL/cl.hpp>

class Algorithm {
 public:
  Algorithm();
  ~Algorithm();
  void initialise();

 private:
  void initialiseOpenCL();
  std::string loadSource(std::string filename);

  cl::Context context_;
  cl::CommandQueue command_queue_;
  cl::Program program_;
};

#endif // ALGORITHM_H
