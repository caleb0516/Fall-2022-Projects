#include "grayscale_image.hpp"

#include <fstream>
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset):
    width_(dataset.Width()), height_(dataset.Height()) {
  if (width_ < 0 || height_ < 0) {
    throw std::runtime_error("Width and height has to be positive");
  }
  image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
  int max = dataset.MaxEle();
  int min = dataset.MinEle();
  double difference = max - min;
  // std::cout<<max <<"   "<< min << std::endl;
  int elevation_point = 0;
  double gray_decimal = 0;
  double shade_of_gray = 0;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      elevation_point = dataset.DatumAt(i, j);
      if (difference != 0) {
        gray_decimal =
            round((elevation_point - min) / (difference)*kMaxColorValue);
        shade_of_gray = gray_decimal;
      } else {
        shade_of_gray = 0;
      }
      Color gray(shade_of_gray, shade_of_gray, shade_of_gray);
      image_.at(i).at(j) = gray;
    }
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  if (width_ < 0 || height_ < 0) {
    throw std::runtime_error("Width and height has to be positive");
  }
  ElevationDataset dataset(filename, width_, height_);
  image_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
  int max = dataset.MaxEle();
  int min = dataset.MinEle();
  double difference = max - min;
  // std::cout<<max <<"   "<< min << std::endl;
  int elevation_point = 0;
  double gray_decimal = 0;
  double shade_of_gray = 0;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      elevation_point = dataset.DatumAt(i, j);
      if (difference != 0) {
        gray_decimal =
            round((elevation_point - min) / (difference)*kMaxColorValue);
        shade_of_gray = gray_decimal;
      } else {
        shade_of_gray = 0;
      }
      Color gray(shade_of_gray, shade_of_gray, shade_of_gray);
      image_.at(i).at(j) = gray;
    }
  }
}
size_t GrayscaleImage::Width() const { return width_; }
size_t GrayscaleImage::Height() const { return height_; }
unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }
const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}
const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}
void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  if (!ofs.is_open()) {
    throw std::runtime_error("File is not open!");
  }
  ofs << "P3\n"
      << width_ << " " << height_ << std::endl
      << kMaxColorValue << std::endl;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      Color ppm_color = ColorAt(i, j);
      ofs << ppm_color.Red() << ' ' << ppm_color.Green() << ' '
          << ppm_color.Blue() << ' ';
    }
    ofs << std::endl;
  }
}
