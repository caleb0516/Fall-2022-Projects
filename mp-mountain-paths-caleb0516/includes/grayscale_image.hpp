#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "color.hpp"
#include "elevation_dataset.hpp"
#include <cmath>

class GrayscaleImage {
public:
  // write behavior declarations here; define in grayscale_image.cc.
  //shade_of_gray = std::round((elevation_point - min_ele) / (max_ele - min_ele) * 255)
  GrayscaleImage(const ElevationDataset& dataset);
  GrayscaleImage(const std::string& filename, size_t width, size_t height);
  size_t Width() const;
  size_t Height() const;
  unsigned int MaxColorValue() const;
  const Color& ColorAt(int row, int col) const;
  const std::vector<std::vector<Color> >& GetImage() const;
  void ToPpm( const std::string& name ) const;


private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  //std::vector<Color> pass_; remove later
  static const int kMaxColorValue = 255;
};

#endif