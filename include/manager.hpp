#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "algorithm.hpp"

class Manager
{
 public:
  Manager();
  ~Manager();
  void start();

 private:
  Algorithm algorithm_;
};

#endif // MANAGER_HPP
