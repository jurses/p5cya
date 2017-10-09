#include "dfa.hpp"
#include <iostream>
#include <fstream>
using namespace CYA;

int main(void){
	std::ifstream ifs("ejemplo.dfa", std::ifstream::in);
	Dfa a(ifs);
}