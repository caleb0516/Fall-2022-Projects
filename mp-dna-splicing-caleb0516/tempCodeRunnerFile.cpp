int Numbers(int i){
    int j = i+5;
    i = 3;
    return i,j;
}
#include <iostream>
int main(){
    int i =0;
    int j=0;
    i, j =Numbers(i);
    std::cout<< i <<std::endl <<j<<std::endl;

}