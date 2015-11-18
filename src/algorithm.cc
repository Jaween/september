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

void Algorithm::compute(float shrink_factor, Image* current_frame, Image* screen) {
  shink_image(shrink_factor, screen);
  background_removal(current_frame);
}

void Algorithm::shink_image(float factor, Image* image) {
  // Allocates buffers on the compute device
  cl::Image2D cl_image_source(
      context_,
      CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
      cl::ImageFormat(CL_R, CL_UNSIGNED_INT32),
      image->getWidth(),
      image->getHeight(),
      0,
      (void*) image->getPixels()
  );

  cl::Image2D cl_image_destination(
      context_,
      CL_MEM_WRITE_ONLY,
      cl::ImageFormat(CL_R, CL_UNSIGNED_INT32),
      image->getWidth(),
      image->getHeight()
  );

  // Retrieves and sets up the compute kernel
  cl::Kernel kernel(program_, "shrink_image");
  kernel.setArg(0, factor);
  kernel.setArg(1, cl_image_source);
  kernel.setArg(2, cl_image_destination);

  executeImageKernel(kernel, cl_image_destination, image);
}

void Algorithm::background_removal(Image* image) {
  // Allocates buffers on the compute device
  cl::Image2D cl_image_source(
      context_,
      CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
      cl::ImageFormat(CL_R, CL_UNSIGNED_INT32),
      image->getWidth(),
      image->getHeight(),
      0,
      (void*) image->getPixels()
  );

  cl::Image2D cl_image_destination(
      context_,
      CL_MEM_WRITE_ONLY,
      cl::ImageFormat(CL_R, CL_UNSIGNED_INT32),
      image->getWidth(),
      image->getHeight()
  );

  // Retrieves and sets up the compute kernel  
  cl::Kernel kernel(program_, "background_removal");
  kernel.setArg(0, cl_image_source);
  kernel.setArg(1, cl_image_destination);

  executeImageKernel(kernel, cl_image_destination, image);
}

inline void Algorithm::executeImageKernel(cl::Kernel& kernel, cl::Image2D& cl_image_destination, Image* out_image) {
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

  command_queue_.enqueueReadImage(cl_image_destination, CL_TRUE, origin, region, 0, 0, pixel_data, NULL, NULL);
}