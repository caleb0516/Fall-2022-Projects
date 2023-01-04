#include "seam_carver.hpp"

// implement the rest of SeamCarver's functions here
const ImagePPM& SeamCarver::GetImage() const { return image_; }
int SeamCarver::GetHeight() const { return height_; }
int SeamCarver::GetWidth() const { return width_; }
int GetSquare(int x) { return x * x; }
int FindLowestEnergy(int x, int y) {
  if (x < y) return x;
  if (y < x) return y;
  // if equal we always return the first element use this to advantage
  return x;
}
int SeamCarver::GetEnergy(int row, int col) const {
  Pixel row_col_minus(0, 0, 0);  // they all contain rgb values
  Pixel row_col_plus(0, 0, 0);
  Pixel row_minus_col(0, 0, 0);
  Pixel row_plus_col(0, 0, 0);
  if (col == width_ - 1) {
    row_col_minus = image_.GetPixel(row, col - 1);
    row_col_plus = image_.GetPixel(row, 0);
  } else if (col == 0) {
    row_col_minus = image_.GetPixel(row, width_ - 1);
    row_col_plus = image_.GetPixel(row, col + 1);
  } else {
    row_col_minus = image_.GetPixel(row, col - 1);
    row_col_plus = image_.GetPixel(row, col + 1);
  }
  if (row == height_ - 1) {
    row_minus_col = image_.GetPixel(row - 1, col);
    row_plus_col = image_.GetPixel(0, col);
  } else if (row == 0) {
    row_minus_col = image_.GetPixel(height_ - 1, col);
    row_plus_col = image_.GetPixel(row + 1, col);
  } else {
    row_minus_col = image_.GetPixel(row - 1, col);
    row_plus_col = image_.GetPixel(row + 1, col);
  }
  int red_col = GetSquare(row_col_minus.GetRed() - row_col_plus.GetRed());
  int green_col = GetSquare(row_col_minus.GetGreen() - row_col_plus.GetGreen());
  int blue_col = GetSquare(row_col_minus.GetBlue() - row_col_plus.GetBlue());
  int red_row = GetSquare(row_minus_col.GetRed() - row_plus_col.GetRed());
  int green_row = GetSquare(row_minus_col.GetGreen() - row_plus_col.GetGreen());
  int blue_row = GetSquare(row_minus_col.GetBlue() - row_plus_col.GetBlue());
  int energy = red_col + green_col + blue_col + red_row + green_row + blue_row;
  return energy;
}
// this just gets us a 2d array with the energy values
int** SeamCarver::GetEnergyMatrix() const {
  int** energy_array = new int*[height_];
  for (int i = 0; i < height_; i++) {
    energy_array[i] = new int[width_];
    for (int j = 0; j < width_; j++) {
      energy_array[i][j] = GetEnergy(i, j);
    }
  }
  CalculatingVerticalSeamMatrix(energy_array);
  return energy_array;
}

// we add the vertical values and create vertical seem 2d array
void SeamCarver::CalculatingVerticalSeamMatrix(int** energy_matrix) const {
  // int** energy_matrix = GetEnergyMatrix();  // points to a 2d vector that has
  //  all the energy values
  int lowest = 0;
  for (int i = height_ - 2; i >= 0; i--) {
    for (int j = 0; j < width_; j++) {
      lowest = 0;
      if (j == 0) {
        // when j ==0 look at below and right
        lowest = FindLowestEnergy(
            energy_matrix[i - 1][j],
            energy_matrix[i - 1]
                         [j + 1]);  // will check to see which one is lower
        energy_matrix[i][j] += lowest;
      } else if (j == width_ - 1) {
        lowest = FindLowestEnergy(energy_matrix[i - 1][j],
                                  energy_matrix[i - 1][j - 1]);
        // will check to see which one is lower
        energy_matrix[i][j] += lowest;
      } else {
        lowest = FindLowestEnergy(energy_matrix[i - 1][j],
                                  energy_matrix[i - 1][j - 1]);
        lowest = FindLowestEnergy(lowest, energy_matrix[i - 1][j + 1]);
        energy_matrix[i][j] += lowest;
      }
    }
  }
  energy_matrix = nullptr;
}

int* SeamCarver::GetVerticalSeam() const {
  int** energy_matrix = new int*[height_];
  for (int i = 0; i < height_; i++) {
    energy_matrix[i] = new int[width_];
    for (int j = 0; j < width_; j++) {
      energy_matrix[i][j] = GetEnergy(i, j);
    }
  }
  CalculatingVerticalSeamMatrix(energy_matrix);
  int* vertical_seam = new int[height_];
  int temp = energy_matrix[0][0];
  int lowest = energy_matrix[0][0];
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      temp = energy_matrix[i][j];
      if (temp < lowest) lowest = temp;
    }
    vertical_seam[i] = lowest;
  }
  Clear(energy_matrix);
  return vertical_seam;
}
void SeamCarver::RemoveVerticalSeam() {
  int* vertical_seam = GetVerticalSeam();
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      if (image_[i][j] == vertical_seam[i]) {
      }
    }
  }
  // vertical_seam is an array of the energy values

  int** height_;
  width_;
  delete[] vertical_seam;
  vertical_seam = nullptr;
}

int* SeamCarver::GetHorizontalSeam() const {
  int temp = height_;
  int* temper = &temp;
  return temper;
  // pointer will point to an array. with the vertical seems
}
void SeamCarver::RemoveHorizontalSeam() {
  height_;
  width_;
}
void SeamCarver::Clear(int** energy_matrix) const {
  for (int i = 0; i < height_; i++) {
    delete[] energy_matrix[i];
  }
  delete[] energy_matrix;
  energy_matrix = nullptr;
}

// given functions below, DO NOT MODIFY
SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}