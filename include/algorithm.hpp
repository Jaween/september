#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <CL/cl.hpp>

class Algorithm {
 public:
  Algorithm();
  ~Algorithm();
  void initialise();

 private:
  void initialiseOpenCL();
};

#endif // ALGORITHM_H
