//#include "dfa.hpp"
#include <iostream>
#include <fstream>
#include "alphabet.hpp"
#include "word.hpp"
#include "dfa.hpp"

using namespace CYA;

//void menu(void);
//std::ifstream& selectFile(std::istream&);

int main(void){
	Alphabet A;	
	Dfa M("ejemplo2.dfa");
	M.putString(std::cin);
	std::cout << M.accepted() << std::endl;
	M.showStatesDeath(std::cout);
	std::cout << std::endl;
	return 0;
}
/*
std::ifstream& selectFile(std::istream& is){
	char nameFile[256];
	is >> nameFile;
	std::ifstream ifs(nameFile, std::ifstream::in);
	return ifs;
}

void menu(void){
	Alphabet A;
	Word W(A);
	Dfa M(selectFile(std::cin));
	int option;
	do{
		std::cin >> option;
		std::cout << "0. Salida" << std::endl
		<< "1. Leer DFA" << std::endl
		<< "2. Mostrar DFA" << std::endl
		<< "3. Identificar estados de muerte" << std::endl
		<< "4. Analizar cadena" << std::end;
		switch(option){
			case 1:
			break;
			case 2:
			break;
			case 3: std::cout << "Identificar estados de muerte" << std::endl
			break;
			case 4:
				M.putString(std::cin);
				if(M.accepted())
					std::cout << "Cadena aceptada" << std::endl;
				else
					std::cout << "Cadena no aceptada" << std::endl;
			break;
			default: std::cout << "Opción incorrecta" << std::endl;
		}
	}while(option != 0);
}
*/