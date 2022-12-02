#include <iostream>
#include <string>

#include "functions.cc"
//#include "functions.hpp"

/*int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./bin/exec word" << std::endl;
    return 1;
  }

  std::string word = argv[1];

  std::string phonetics = "hello";
  std::cout << phonetics << std::endl;d
}*/

int main() {
  std::string aloha = "alOHA";
  std::string awakea = "awakea";
  std::string alohaawakea = "Aloha awakea";
  std::string kakahiaka = "Kakahiaka";
  std::string mahalo = "Mahalo";
  std::string ekomomai = "E Komo MAI";
  std::string maui = "Maui";
  std::string kane = "kane";
  std::string makua = "makua";
  std::string keikikane = "keikikane";
  std::string humuhumunukunukuapuaa = "humuhumunukunukuapua'a";
  std::string keki = "keki";
  std::string hoaloha = "Hoaloha";
  std::string kaiapuni = "kaiapuni";
  std::string wahine = "wahine";
  std::string iwa = "iwa";
  std::string huaai = "Huaai";
  std::string hello_world = "Hello, World!";
  std::string zebras = "zebras";
  Convert(aloha);
  Convert(awakea);
  Convert(alohaawakea);
  Convert(kakahiaka);
  Convert(mahalo);
  Convert(ekomomai);
  Convert(maui);
  Convert(kane);
  Convert(makua);
  Convert(keikikane);
  Convert(humuhumunukunukuapuaa);
  Convert(keki);
  Convert(hoaloha);
  Convert(kaiapuni);
  Convert(huaai);
  Convert(hello_world);
  Convert(zebras);
  Convert(iwa);
  Convert(wahine);
}