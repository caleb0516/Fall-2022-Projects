#include <cstdlib>
#include <iostream>
using namespace std;
// #include "color.hpp"

// #include "elevation_dataset.hpp"

// #include "grayscale_image.hpp"

// #include "path.hpp"

// #include "path_image.hpp"

#include "color.cc"
#include "elevation_dataset.cc"
#include "grayscale_image.cc"
#include "path.cc"
#include "path_image.cc"

int main() {
  size_t w = 5;
  size_t h = 2;
  ElevationDataset test("prompt_5w_2h.dat", w, h);

  // cout << test.ElevationDataset::MinEle() << endl;
  // cout << test.ElevationDataset::MaxEle() << endl;

  GrayscaleImage gray(test);
  // Color color = gray.ColorAt(0, 4);
  //  cout << color.Red() << endl << color.Green() << endl << color.Blue() <<
  //  endl;
  gray.ToPpm("GrayPPM.ppm");
  Path path_zero(test, w, 0);
  cout << "path zero elechange: " << path_zero.EleChange() << endl;
  Path path_one(test, w, 1);
  cout << "path one elechage: " << path_one.EleChange() << endl;
  Path path_two(test, w, 2);
  cout << "path two elechange: " << path_two.EleChange() << endl;
  PathImage paths(gray, test);
  // cout << paths.Width() << endl;
  // cout << paths.Height() << endl;
  std::vector<std::vector<Color>> red_green = paths.GetPathImage();
  cout << "red: " << red_green[0][0].Red()
       << " green: " << red_green[0][0].Green();
  cout << " blue: " << red_green[0][0].Blue() << endl;
  paths.ToPpm("PathImagePPM.ppm");
}
