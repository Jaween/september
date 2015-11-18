#include <ctime>
#include <fstream>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "image_sdl.hpp"

ImageSdl::ImageSdl(unsigned int width, unsigned int height, unsigned int words_per_pixel) {
  unsigned int flag = 0;
  unsigned int depth = 32;
  unsigned int r_mask = 0x000000FF;
  unsigned int g_mask = 0x0000FF00;
  unsigned int b_mask = 0x00FF0000;
  unsigned int a_mask = 0xFF000000;
  surface_ = SDL_CreateRGBSurface(flag, width, height, depth, r_mask, g_mask, b_mask, a_mask);

  width_ = surface_->w;
  height_ = surface_->h;
  words_per_pixel_ = 1;
}

ImageSdl::ImageSdl(std::string filename) {
  load(filename);
}

ImageSdl::~ImageSdl() {
  SDL_FreeSurface(surface_);
}

uint32_t* ImageSdl::getPixels() {
  return (uint32_t*) surface_->pixels;
}

SDL_Surface* ImageSdl::getSurface() {
  return surface_;
}

void ImageSdl::load(std::string filename) {
  // Frees any existing image
  if (surface_ != NULL) {
    SDL_FreeSurface(surface_);
  }

  // Loads in the image
  surface_ = IMG_Load(filename.c_str());
  if (surface_ == NULL) {
    std::cerr << "Failed to load image" << std::endl;
  }

  // Saves the dimensions of the image
  width_ = surface_->w;
  height_ = surface_->h;
  words_per_pixel_ = 1;
}

void ImageSdl::save(std::string prefix) {
  std::string date_time = getDateTime();
  std::string directory = "out/";
  std::string extension = ".bmp";

  std::string filename = directory + prefix + " " + date_time + extension;
  std::cout << filename << std::endl;
  SDL_SaveBMP(surface_, filename.c_str());
}

void ImageSdl::fill(unsigned int colour) {
  for (unsigned int y = 0; y < height_; y++) {
    for (unsigned int x = 0; x < width_; x++) {
        unsigned int index = y * width_ + x;
        ((unsigned int*) surface_->pixels)[index] = colour;
    }
  }
}

void ImageSdl::blit(Image* other) {
  SDL_BlitSurface(
      (dynamic_cast<ImageSdl*>(other))->getSurface(),
      NULL,
      surface_,
      NULL
  );
}

void ImageSdl::grayscale() {
  unsigned int* pixels = (unsigned int*) surface_->pixels;

  for (unsigned int y = 0; y < height_; y++) {
    for (unsigned int x = 0; x < width_; x++) {
      unsigned int index = y * width_ + x;
      unsigned int pixel = pixels[index];

      unsigned int r = pixel >> 16 & 0xFF;
      unsigned int g = pixel >> 8 & 0xFF;
      unsigned int b = pixel & 0xFF;
      unsigned int v = 0.212671f * r + 0.715160f * g + 0.072169f * b;
      unsigned int gray_pixel = (0xFF << 24) | (v << 16) | (v << 8) | v;

      pixels[index] = gray_pixel;
    }
  }
}

std::string ImageSdl::getDateTime() {
  time_t rawtime;
  struct tm * timeinfo;
  int size = 80;
  char buffer[size];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, size, "%y-%m-%d %T", timeinfo);
  return std::string(buffer);
}
