#include <iostream>
#include <string>

using namespace std;

int main(void){
    string cadena;
    cadena.append("Hola      ");
    cadena.append("¿Qué tal?");
    std::cout << cadena << '|' <<  std::endl;
}