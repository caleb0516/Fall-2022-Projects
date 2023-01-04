#include "path_image.hpp"
/*
  private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;

  std::vector<std::vector<Color>> path_image_;
  //path_image == grayscale image
  static const int kMaxColorValue = 255;

  so create paths which is a vector of all the paths
  within paths find the path with the lowest ele_change and get the index of
  that meaning iterate through paths and find index with lowest ele_change after
  that set all path_image red (252,25,63) then go to the lowest path and set all
  those pixels to green (31,253,13)
*/
static const Color kRed(252, 25, 63);
static const Color kGreen(31, 253, 13);
PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    width_(image.Width()), height_(dataset.Height()) {
  size_t lowest_ele_change = SIZE_MAX;
  size_t lowest_row = 0;
  for (size_t row = 0; row < height_; row++) {
    paths_.push_back(Path(dataset, width_, row));
    if (paths_.at(row).EleChange() < lowest_ele_change) {
      lowest_ele_change = paths_.at(row).EleChange();
      lowest_row = row;
    }
  }
  path_image_ = image.GetImage();
  for (size_t row = 0; row < height_; row++) {
    std::vector<size_t> path = paths_.at(row).GetPath();
    for (size_t col = 0; col < width_; col++) {
      path_image_[path.at(col)][col] = kRed;
    }
  }
  std::vector<size_t> lowest_path = paths_.at(lowest_row).GetPath();
  for (size_t i = 0; i < width_; i++) {
    path_image_[lowest_path[i]][i] = kGreen;
  }
}
size_t PathImage::Width() const { return width_; }
size_t PathImage::Height() const { return height_; }
unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }
const std::vector<Path>& PathImage::Paths() const { return paths_; }
const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}
const Color& PathImage::ColorAt(size_t row, size_t col) const {
  return path_image_.at(row).at(col);
}
void PathImage::ToPpm(const std::string& name) const {
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
