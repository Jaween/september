#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "algorithm.hpp"

Algorithm::Algorithm() {
  initialiseOpenCL();
}

Algorithm::~Algorithm() {
}

void Algorithm::initialise() {
  
}

void Algorithm::initialiseOpenCL() {
  // Retrieves the OpenCL platform to be used
  std::vector<cl::Platform> platforms;
  cl::Platform::get(&platforms);

  if (platforms.size() == 0) {
    std::cerr << "No platforms found, check OpenCL installation." << std::endl;
    exit(EXIT_FAILURE);
  }
  cl::Platform platform = platforms.at(0);
  std::cout << "Using platform: " << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;

  // Retrieves the default device of the platform
  std::vector<cl::Device> devices;
  platform.getDevices(CL_DEVICE_TYPE_DEFAULT, &devices);
  if (devices.size() == 0) {
    std::cerr << "No devices found, check OpenCL installation." << std::endl;
    exit(EXIT_FAILURE);
  }
  cl::Device device = devices.at(0);
  std::cout << "Using device: " << device.getInfo<CL_DEVICE_NAME>() << std::endl;

  context_ = cl::Context({device});

  // Loads and builds the kernel
  std::string kernel_code =  loadSource("src/kernels/september.cl");
  std::cout << "Loaded kernel" << std::endl << "Building kernel..." << std::endl;
  cl::Program::Sources sources;
  sources.push_back({kernel_code.c_str(), kernel_code.length()});
  program_ = cl::Program(context_, sources);
  if (program_.build({device}) != CL_SUCCESS) {
    std::cerr << "Error building " << program_.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
    exit(EXIT_FAILURE);
  } else {
    std::cout << "Build success!" << std::endl;
  }
  
  // Command queue
  command_queue_ = cl::CommandQueue(context_, device);
}


std::string Algorithm::loadSource(std::string filename) {
  std::ifstream stream(filename);
  std::stringstream buffer;
  buffer << stream.rdbuf();
  return buffer.str();
}