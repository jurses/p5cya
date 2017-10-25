#ifndef	WORD_H
#define	WORD_H

#include <string>
#include <cstring>
#include <cmath>
#include <iostream>
#include "alphabet.hpp"

namespace CYA{
	class Word{
	private:
		Alphabet alphabet_;
		std::string wordStr_;
		bool empty_;	// indica si es la cadena vacía

		/**
		 * @brief indica si la cadena se puede formar con el alfabeto dado
		 * @return valor booleano, verdadero si está bien
		 */
		bool goodWord(void);

	public:
		/**
		 * @brief constructor por defecto de la clase word
		 */
		Word();

		/**
		 * @brief sobrecarga del operador = para asignar la cadena
		 * @param const char*:
		 * @return devuelve la palabra para múltiples asignaciones
		 */
		Word& operator=(const char*);

		/**
		 * @brief sobrecarga del operador = para asignar la cadena
		 * @param const Word&:
		 * @return devuelve la palabra para múltiples asignaciones
		 */
		Word& operator=(const Word&);

		/**
		 * @brief sobrecarga del operador == para comparación de cadenas
		 * @param const Word&:
		 * @return devuelve verdadero si son iguales
		 */
		bool operator==(const Word&)const;

		/**
		 * @brief obtiene la palabra
		 * @return devuelve una cadena de char
		 */
		const char* obtWord(void)const;

		/**
		 * @brief sobrecarga del operador < para poder meterlos en std::set
		 * @return devuelver un valor booleano
		 */
		bool operator<(const Word&)const;

		/**
		 * @brief concatena la cadena
		 * @param Word: cadena a concatenar con
		 */
		void concatenate(Word);

		/**
		 * @brief invierte la cadena
		 */
		void invert(void);

		/**
		 * @brief indica si es la cadena vacía
		 * @return devuelve verdadero si está vacía
		 */
		bool isEmpty(void);

		/**
		 * @brief función externa para inyectarle un objeto word al objeto
		 * @param std::istream&: un flujo de entrada
		 * @param Word&: el objeto a inyectar
		 */
		friend std::istream& operator>>(std::istream&, Word&);//friend es necesario?

		/**
		 * @brief sobrecarga del operador[] para acceder indexadamente
		 * @param int: índice
		 * @return devuelve el carácter correspondiente
		 */
		const char operator[](int);

		/**
		 * @brief aunque tenga el carácter '~' su tamaño es 0
		 * @return el tamaño de la cadena
		 */
		int size(void);

		/**
		 * @brief función para escribir mediante un flujo
		 * @param std::ostream&: flujo
		 * @return flujo
		 */
		std::ostream& write(std::ostream&);

		/**
		 * @brief sobrecarga del tipo para que pueda comportarse como un std::string()
		 */
		operator std::string();

		/**
		 * @brief mete el alfabeto
		 * @param Alphabet&: el alfabeto con el que estará formado esta palabra
		 */
		void setAlphabet(Alphabet&);
	};
}


#endif	// WORD_H	