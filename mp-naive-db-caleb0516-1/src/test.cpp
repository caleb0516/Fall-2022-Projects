#include <iostream>
#include <vector>
using namespace std;

int main() {
  vector<int> vec = {1, 2, 3, 4, 5};
  vec.erase(vec.begin() + 1, vec.begin() + 2);
  for (int i = 0; i < 0; i++) {
    cout << vec.at(i) << endl;
  }
  int test = 0;
  cout << typeid(test).name() << endl;
}