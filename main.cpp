//#include "dfa.hpp"
#include <iostream>
#include <fstream>
#include "dfa.hpp"
using namespace CYA;

int main(void){
	std::ifstream ifs("ejemplo.dfa", std::ifstream::in);
	Dfa M(ifs);
}