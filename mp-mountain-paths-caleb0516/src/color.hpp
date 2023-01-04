#ifndef COLOR_H
#define COLOR_H
#include <cstdlib>  // for size_t
#include <vector>
#include <string>
#include <stdexcept>
class Color {
public:
  Color() = default;
  Color(int r, int g, int b);
  int Red() const { return red_; }
  int Green() const { return green_; }
  int Blue() const { return blue_; };

private:
  bool ValidColor(int value) const;
  static constexpr int kColorValueMin = 0;
  static constexpr int kColorValueMax = 255;
  int red_ = 0;
  int green_ = 0;
  int blue_ = 0;
};

bool operator==(const Color& rhs, const Color& lhs);

#endif