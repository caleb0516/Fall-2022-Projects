#include "seam_carver.hpp"
// implement the rest of SeamCarver's functions here
const ImagePPM& SeamCarver::GetImage() const { return image_; }
int SeamCarver::GetHeight() const { return height_; }
int SeamCarver::GetWidth() const { return width_; }
int GetSquare(int x) { return x * x; }
int FLE(int x, int y) {  // find lowest energy
  if (x < y) return x;
  if (y < x) return y;
  // if equal we always return the first element use this to advantage
  return x;
}
int FLE(int x, int y, int z) {
  int lowest = FLE(y, z);
  if (x < lowest) return x;
  return lowest;
}
int SeamCarver::GetEnergy(int row, int col) const {
  Pixel row_col_minus(0, 0, 0);  // they all contain rgb values
  Pixel row_col_plus(0, 0, 0);
  Pixel row_minus_col(0, 0, 0);
  Pixel row_plus_col(0, 0, 0);
  if (col == image_.GetWidth() - 1) {
    row_col_minus = image_.GetPixel(row, col - 1);
    row_col_plus = image_.GetPixel(row, 0);
  } else if (col == 0) {
    row_col_minus = image_.GetPixel(row, image_.GetWidth() - 1);
    row_col_plus = image_.GetPixel(row, col + 1);
  } else {
    row_col_minus = image_.GetPixel(row, col - 1);
    row_col_plus = image_.GetPixel(row, col + 1);
  }
  if (row == image_.GetHeight() - 1) {
    row_minus_col = image_.GetPixel(row - 1, col);
    row_plus_col = image_.GetPixel(0, col);
  } else if (row == 0) {
    row_minus_col = image_.GetPixel(image_.GetHeight() - 1, col);
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
  int** energy_array = new int*[image_.GetHeight()];
  for (int i = 0; i < image_.GetHeight(); i++) {
    energy_array[i] = new int[image_.GetWidth()];
    for (int j = 0; j < image_.GetWidth(); j++) {
      energy_array[i][j] = GetEnergy(i, j);
    }
  }
  return energy_array;
}

// we add the vertical values and create vertical seem 2d array

int** SeamCarver::CalculatingVerticalSeamMatrix() const {
  int** energy_matrix = GetEnergyMatrix();  // points to a 2d vector that has
                                            // all the energy values
  int lowest = 0;
  for (int i = image_.GetHeight() - 2; i >= 0; i--) {
    for (int j = 0; j < image_.GetWidth(); j++) {
      if (j == 0) {
        // when j ==0 look at below and right
        lowest =
            FLE(energy_matrix[i + 1][j],
                energy_matrix[i + 1]
                             [j + 1]);  // will check to see which one is lower
        energy_matrix[i][j] += lowest;
      }

      else if (j == image_.GetWidth() - 1) {
        lowest =
            FLE(energy_matrix[i + 1][j],
                energy_matrix[i + 1]
                             [j - 1]);  // will check to see which one is lower
        energy_matrix[i][j] += lowest;
      } else {
        lowest =
            FLE(energy_matrix[i + 1][j],
                energy_matrix[i + 1]
                             [j - 1]);  // will check to see which one is lower
        lowest = FLE(lowest, energy_matrix[i + 1][j + 1]);
        energy_matrix[i][j] += lowest;
      }
    }
  }
  return energy_matrix;
}
int* SeamCarver::GetVerticalSeam() const {
  int* vertical_seam = new int[image_.GetHeight()];
  int** em = CalculatingVerticalSeamMatrix();
  int temp = em[0][0];
  int lowest = INT16_MAX;
  int pos = 0;
  for (int j = 0; j < image_.GetWidth(); j++) {
    temp = em[0][j];
    if (temp < lowest) {
      lowest = temp;
      pos = j;
    }
  }
  vertical_seam[0] = pos;
  for (int i = 1; i < image_.GetHeight(); i++) {
    if (pos == 0) {
      lowest = FLE(em[i][pos], em[i][pos + 1]);
    } else if (pos == image_.GetWidth() - 1) {
      lowest = FLE(em[i][pos], em[i][pos - 1]);
    } else
      lowest = FLE(em[i][pos], em[i][pos - 1], em[i][pos + 1]);
    if (lowest != em[i][pos]) {
      if (pos == 0) pos++;
      for (int j = pos - 1; j < image_.GetWidth(); j++) {
        if (lowest == em[i][j]) {
          pos = j;
          break;
        }
      }
    }
    vertical_seam[i] = pos;
  }
  Clear(em);
  return vertical_seam;
}

void SeamCarver::Clear(int** energy_matrix) const {
  for (int i = 0; i < height_; i++) {
    delete[] energy_matrix[i];
  }
  delete[] energy_matrix;
  energy_matrix = nullptr;
}
void SeamCarver::RemoveVerticalSeam() {
  int* vertical_seam = GetVerticalSeam();
  auto** new_pixels = new Pixel*[height_];
  for (int i = 0; i < height_; i++) {
    new_pixels[i] = new Pixel[width_ - 1];
    for (int j = 0; j < vertical_seam[i]; j++) {
      new_pixels[i][j] = image_.GetPixel(i, j);
    }
    for (int j = vertical_seam[i]; j < width_ - 1; j++) {
      new_pixels[i][j] = image_.GetPixel(i, j + 1);
    }
  }
  width_--;
  ImagePPM new_image(height_, width_, image_.GetMaxColorValue(), new_pixels);
  image_ = new_image;
  delete[] vertical_seam;
  vertical_seam = nullptr;
}
int** SeamCarver::CalculatingHorizontalSeamMatrix() const {
  int** em = GetEnergyMatrix();
  int lowest = 0;
  for (int col = image_.GetWidth() - 2; col >= 0; col--) {  // columns first
    for (int row = 0; row < image_.GetHeight(); row++) {
      if (row == 0) {
        lowest = FLE(em[row][col + 1], em[row + 1][col + 1]);
        em[row][col] += lowest;
      } else if (row == image_.GetHeight() - 1) {
        lowest = FLE(em[row][col + 1], em[row - 1][col + 1]);
        em[row][col] += lowest;
      } else {
        lowest = FLE(em[row][col + 1], em[row + 1][col + 1]);
        lowest = FLE(lowest, em[row - 1][col + 1]);
        em[row][col] += lowest;
      }
    }
  }
  return em;
}
int* SeamCarver::GetHorizontalSeam() const {
  int* horizontal_seam = new int[image_.GetWidth()];
  int** em = CalculatingHorizontalSeamMatrix();
  int temp = em[0][0];
  int lowest = em[0][0];
  int pos = 0;
  for (int row = 0; row < height_; row++) {
    temp = em[row][0];
    if (temp < lowest) {
      lowest = temp;
      pos = row;
    }
  }
  horizontal_seam[0] = pos;
  for (int col = 1; col < width_; col++) {
    if (pos == 0) {
      lowest = FLE(em[pos][col], em[pos + 1][col]);
    } else if (pos == height_ - 1) {
      lowest = FLE(em[pos][col], em[pos - 1][col]);
    } else
      lowest = FLE(em[pos][col], em[pos + 1][col], em[pos - 1][col]);
    if (lowest != em[pos][col]) {
      if (pos == 0) pos++;
      for (int row = pos - 1; row < height_; row++) {
        if (em[row][col] == lowest) {
          pos = row;
          break;
        }
      }
    }
    horizontal_seam[col] = pos;
  }
  Clear(em);
  return horizontal_seam;
}
// remove wont work vector isnt not getting created correctly
void SeamCarver::RemoveHorizontalSeam() {
  int* horizontal_seam = GetHorizontalSeam();
  auto** new_pixels = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; row++) {
    new_pixels[row] = new Pixel[width_];
  }
  for (int col = 0; col < width_; col++) {
    for (int row = 0; row < horizontal_seam[col]; row++) {
      new_pixels[row][col] = image_.GetPixel(row, col);
    }
    for (int row = horizontal_seam[col]; row < height_ - 1; row++) {
      new_pixels[row][col] = image_.GetPixel(row + 1, col);
    }
  }
  height_--;
  ImagePPM new_image(height_, width_, image_.GetMaxColorValue(), new_pixels);
  image_ = new_image;
  delete[] horizontal_seam;
  horizontal_seam = nullptr;
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