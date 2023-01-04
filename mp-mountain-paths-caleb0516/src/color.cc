#include "color.hpp"


Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  // need to ensure valid color has been constructed..
   if(!ValidColor(red_)||!ValidColor(green_)|| !ValidColor(blue_)){
    throw std::runtime_error ("Not a valid color value");
  }
}

bool Color::ValidColor(int value) const{
  bool valid = true;
  if(value <kColorValueMin || value >kColorValueMax){
    
    valid = false;
  }
  return valid;
}


// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}