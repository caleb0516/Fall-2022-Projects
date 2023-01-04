#include "path.hpp"

#include <iostream>
Path::Path(const ElevationDataset& dataset, size_t length, size_t starting_row):
    length_(length), starting_row_(starting_row) {
  path_ = std::vector<size_t>(length);
  int above = 0;
  int same = 0;
  int below = 0;
  for (size_t i = 0; i < length_; i++) {  // start at first column
    path_[i] = starting_row_;
    if (i == length_ - 1) break;
    if (starting_row_ == 0) {
      same = abs(dataset.DatumAt(starting_row_, i) -
                 dataset.DatumAt(starting_row_, i + 1));
      below = abs(dataset.DatumAt(starting_row_, i) -
                  dataset.DatumAt(starting_row_ + 1, i + 1));
      above = same;
    } else if (starting_row_ == (dataset.Height() - 1)) {
      above = abs(dataset.DatumAt(starting_row_, i) -
                  dataset.DatumAt(starting_row_ - 1, i + 1));
      same = abs(dataset.DatumAt(starting_row_, i) -
                 dataset.DatumAt(starting_row_, i + 1));
      below = same;
    } else {
      above = abs(dataset.DatumAt(starting_row_, i) -
                  dataset.DatumAt(starting_row_ - 1, i + 1));
      same = abs(dataset.DatumAt(starting_row_, i) -
                 dataset.DatumAt(starting_row_, i + 1));
      below = abs(dataset.DatumAt(starting_row_, i) -
                  dataset.DatumAt(starting_row_ + 1, i + 1));
    }
    if (above < same && above < below) {
      starting_row_ -= 1;
      ele_change_ += above;
    } else if ((below < same)) {
      starting_row_ += 1;
      // IncEleChange(below);
      ele_change_ += below;
    } else
      ele_change_ += same;
  }
}
// std::cout << "path: ";
// for (int i = 0; i < path_.size(); i++) {
//   std::cout << path_[i] << " ";
// }
size_t Path::Length() const { return length_; }
size_t Path::StartingRow() const { return starting_row_; }
unsigned int Path::EleChange() const { return ele_change_; }

void Path::IncEleChange(unsigned int value) { ele_change_ += value; }

const std::vector<size_t>& Path::GetPath() const { return path_; }

void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }