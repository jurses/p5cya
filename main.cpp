//#include "dfa.hpp"
#include <iostream>
#include <fstream>
#include "dfa.hpp"
#include "glr.hpp"
using namespace CYA;

void menu(void);

int main(void){
	menu();
}

void menu(void){
	int option;
	Dfa M;
	Glr G;
	do{
		std::cout << "[1] Leer Dfa" << std::endl;
		std::cout << "[2] Mostrar Dfa" << std::endl;
		std::cout << "[3] Identificar estados de muerte" << std::endl;
		std::cout << "[4] Analizar cadena" << std::endl;
		std::cout << "[5] Minimizar el dfa" << std::endl;
		std::cout << "[6] Exportar el dfa" << std::endl;
		std::cout << "[7] Sacar la gramática" << std::endl;
		std::cout << "[0] Salir" << std::endl;
		std::cin >> option;
		switch(option){
			case 0: break;
			case 1: {
					std::cout << "Ingrese el nombre del fichero: ";
					std::string nombre;
					std::cin >> nombre;
					std::ifstream ifs(nombre.c_str(), std::ifstream::in);
					M.openFile(ifs);
			}
					break;
			case 2:	M.showDFA(std::cout);
					break;
			case 3: M.showStatesDeath(std::cout);
					break;
			case 4:	std::cout << "Cadena a analizar: ";
					M.putString(std::cin);
					if(M.accepted())
						std::cout << "La cadena es aceptada" << std::endl;
					else
						std::cout << "La cadena no es aceptada" << std::endl;
					break;
			case 5: M.minDfa();
					break;
			case 6: {
					std::cout << "Introduzca nombre de archivo: ";
					std::string nombre;
					std::cin >> nombre;
					M.exportDfa(nombre.c_str());
					break;
			}

			case 7: {
				G.openG(M.exportDfa());
				std::string nombre;
				std::cout << "Introduzca nombre de archivo: ";
				std::cin >> nombre;
				G.genFile();
				break;
			}
			default: std::cout << "Opción incorrecta" << std::endl;
		}
	}while(option != 0);
}