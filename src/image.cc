#include "image.hpp"

Image::Image() {
  // Default empty constructor
}

Image::Image(unsigned int width, unsigned int height, unsigned int words_per_pixel) {
  // No implementation (exists for external interface purposes)
}

unsigned int Image::getWidth() {
  return width_;
}

unsigned int Image::getHeight() {
  return height_;
}

unsigned int Image::getWordsPerPixel() {
  return words_per_pixel_;
}
