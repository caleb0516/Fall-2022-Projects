#include "image_ppm.hpp"

// implement the rest of ImagePPM's functions here
Pixel ImagePPM::GetPixel(int row, int col) const { return pixels_[row][col]; }

int ImagePPM::GetMaxColorValue() const { return max_color_value_; }

// given functions below, DO NOT MODIFY
ImagePPM::ImagePPM(int height, int width, int max_color_value, Pixel** pixels):
    height_(height),
    width_(width),
    max_color_value_(max_color_value),
    pixels_(pixels) {}

ImagePPM::ImagePPM(const std::string& path) {
  std::ifstream input_file(path);
  input_file >> *this;
  input_file.close();
}
// std::ostream& operator<<(std::ostream& os, const ImagePPM& image);
std::ostream& operator<<(std::ostream& os, const ImagePPM& image) {
  os << "P3"
     << "\n"
     << image.GetWidth() << " " << image.GetHeight() << "\n"
     << image.GetMaxColorValue() << "\n";
  for (int row = 0; row < image.GetHeight(); ++row) {
    for (int col = 0; col < image.GetWidth(); ++col) {
      os << image.GetPixel(row, col).GetRed() << "\n"
         << image.GetPixel(row, col).GetGreen() << "\n"
         << image.GetPixel(row, col).GetBlue() << "\n";
    }
  }
  return os;
}
ImagePPM::ImagePPM(const ImagePPM& source) { *this = source; }

ImagePPM& ImagePPM::operator=(const ImagePPM& source) {
  if (this == &source) {
    return *this;
  }

  Clear();

  height_ = source.height_;
  width_ = source.width_;
  max_color_value_ = source.max_color_value_;

  pixels_ = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    pixels_[row] = new Pixel[width_];

    for (int col = 0; col < width_; col++) {
      pixels_[row][col] = source.pixels_[row][col];
    }
  }

  return *this;
}

ImagePPM::~ImagePPM() { Clear(); }

void ImagePPM::Clear() {
  for (int i = 0; i < height_; i++) {
    delete[] pixels_[i];
  }

  delete[] pixels_;

  height_ = 0;
  width_ = 0;
  pixels_ = nullptr;
}

std::istream& operator>>(std::istream& is, ImagePPM& image) {
  image.Clear();
  std::string line;
  // ignore magic number line
  getline(is, line);
  // check to see if there's a comment line
  getline(is, line);
  if (line[0] == '#') {
    getline(is, line);
  }
  // parse width and height
  int space = line.find_first_of(' ');
  image.width_ = std::stoi(line.substr(0, space));
  image.height_ = std::stoi(line.substr(space + 1));
  // get max color value
  getline(is, line);
  image.max_color_value_ = std::stoi(line);
  // init and fill in Pixels array
  image.pixels_ = new Pixel*[image.height_];
  for (int i = 0; i < image.height_; i++) {
    image.pixels_[i] = new Pixel[image.width_];
  }
  for (int row = 0; row < image.height_; row++) {
    for (int col = 0; col < image.width_; col++) {
      getline(is, line);
      int red = std::stoi(line);
      getline(is, line);
      int green = std::stoi(line);
      getline(is, line);
      int blue = std::stoi(line);

      Pixel p(red, green, blue);
      image.pixels_[row][col] = p;
    }
  }
  return is;
}