#include "elevation_dataset.hpp"

#include <fstream>
ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  std::ifstream ifs(filename);  // open file
  if (width_ < 0 || height_ < 0) {
    throw std::runtime_error("Width and height has to be positive");
  }
  if (!ifs.is_open())
    throw std::runtime_error("File not open - elevation dataset");
  data_ = std::vector<std::vector<int>>(height_, std::vector<int>(width_));
  int elevation = 0;
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      ifs >> elevation;
      if (ifs.fail()) {
        throw std::runtime_error("bad file or too little data");
      }
      data_.at(i).at(j) = elevation;
    }
  }

  ifs >> elevation;
  if (ifs.good()) {
    throw std::runtime_error("too much data");
  }
  int temp_min = 0;
  int temp_max = 0;
  max_ele_ = data_.at(0).at(0);
  min_ele_ = data_.at(0).at(0);
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      temp_max = data_.at(i).at(j);
      temp_min = data_.at(i).at(j);
      if (temp_max > max_ele_) max_ele_ = temp_max;
      if (temp_min < min_ele_) min_ele_ = temp_min;
    }
  }
}

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  int i = data_.at(row).at(col);
  return (i);
}
size_t ElevationDataset::Width() const { return width_; }
size_t ElevationDataset::Height() const { return height_; }
int ElevationDataset::MaxEle() const { return max_ele_; }
int ElevationDataset::MinEle() const { return min_ele_; }
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}