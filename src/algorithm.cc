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

void Algorithm::execute(Image* current_frame, Image* previous_frame, Image* screen) {
  // Allocates buffer on the compute device
  cl::Image2D clImage_current(
      context_,
      CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
      cl::ImageFormat(CL_RGBA, CL_UNSIGNED_INT8),
      current_frame->getWidth(),
      current_frame->getHeight(),
      0,
      (void*) current_frame->getPixels()
  );

  cl::Image2D clImage_previous(
      context_,
      CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
      cl::ImageFormat(CL_RGBA, CL_UNSIGNED_INT8),
      previous_frame->getWidth(),
      previous_frame->getHeight(),
      0,
      (void*) previous_frame->getPixels()
  );

  cl::Image2D clImage_screen(
      context_,
      CL_MEM_WRITE_ONLY,
      cl::ImageFormat(CL_R, CL_UNSIGNED_INT32),
      screen->getWidth(),
      screen->getHeight()
  );

  cl::Kernel kernel(program_, "execute");
  kernel.setArg(0, clImage_current);
  kernel.setArg(1, clImage_previous);
  kernel.setArg(2, clImage_screen);

  executeImageKernel(kernel, clImage_screen, screen);
}

inline void Algorithm::executeImageKernel(cl::Kernel& kernel, cl::Image2D& out_buffer, Image* out_image) {
  cl_int result = command_queue_.enqueueNDRangeKernel(
      kernel,
      cl::NullRange,
      cl::NDRange(out_image->getWidth(), out_image->getHeight()),
      cl::NullRange
  );

  if (result != CL_SUCCESS) {
    std::cerr << "Kernel execution error" << std::endl;
  }

  cl::size_t<3> origin;
  origin[0] = 0;
  origin[1] = 0;
  origin[2] = 0;

  cl::size_t<3> region;
  region[0] = out_image->getWidth();
  region[1] = out_image->getHeight();
  region[2] = 1;

  uint32_t* pixel_data = out_image->getPixels();

  command_queue_.enqueueReadImage(out_buffer, CL_TRUE, origin, region, 0, 0, pixel_data, NULL, NULL);
}