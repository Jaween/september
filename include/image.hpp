#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstddef>
#include <cstdint>
#include <string>

// Abstract base class for image data tied to various graphics libaries
class Image {
 public:
  Image();
  Image(unsigned int width, unsigned int height, unsigned int words_per_pixel);
  virtual unsigned int getWidth();
  virtual unsigned int getHeight();
  virtual unsigned int getWordsPerPixel();
  virtual uint32_t* getPixels() = 0;
  virtual void load(std::string filename) = 0;
  virtual void save(std::string prefix) = 0;
  virtual void fill(unsigned int colour) = 0;
  virtual void blit(Image* other) = 0;

 protected:
  unsigned int width_ = 0;
  unsigned int height_ = 0;
  unsigned int words_per_pixel_ = 1;
};

#endif // IMAGE_HPP
