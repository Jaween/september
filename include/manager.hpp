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
  Algorithm m_algorithm;
};

#endif // MANAGER_HPP
