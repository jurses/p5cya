/**
 * @title Clase Estado
 * @brief La cabecera de la clase estado
*/
#ifndef STATE_H
#define STATE_H

#include <set>
#include <ostream>
#include <fstream>
#include <utility>

//finite states ID set, conjuntos id de estados finitos
typedef std::set<int> FSIDS_t;
typedef std::pair<char, FSIDS_t> trans_t;
typedef std::set<trans_t> transS_t;

namespace CYA{
	class State{
	private:
		int id_;
		bool acceptance_;
		transS_t adjacency_;
		/**
		 * @brief nos da el primer elemento de un set de enteros, esto es gran parte de lo que lo diferencia del código del nfa
		 * @param typedef std::set<int> FSIDS_t:
		 * @return el id del primer elemento del set
		 */
		int obtainFirst(FSIDS_t)const;
		
	public:
		/**
		 * @brief constructor de la clase
		 * @param int: id del estado
		 * @param bool: si es de aceptación
		 */
		State(int, bool);   // id, acceptance
		State();

		/**
		 * @return devuelve el atributo del identificador
		 */
		int getID(void)const;

		/**
		 * @brief operador menor qué, necesario para poder insertar esta clase de objetos en un std::set
		 * @param State&: Otro objeto estado con el que comparar
		 * @return un valor de tipo booleano
		 */
		bool operator<(const State&)const;

		/**
		 * @brief pone la adyacencia con el símbolo al siguiente estado puesto por el identificador
		 * @param char: símbolo de la transición
		 * @param int: estado siguiente
		 */
		void setAdj(char, int);

		/**
		 * @brief obtiene el siguiente estado dado un símbolo
		 * @param const char: el símbolo
		 * @return id del siguiente estado
		 */
		int getNextS(const char)const;

		/**
		 * @brief nos dice si el estado es de aceptación comprobando el atributo acceptance_
		 * @return valor booleano
		 */
		bool isAcceptance(void)const;

		/**
		 * @brief comprueba si es un estado de muerte comprobando que todas las transiciones vayan a él
		 * @return valor booleano
		 */
		bool isDeath(void)const;

		/**
		 * @brief sobrecarga del operador == para comprobar si es el mismo estado usando el id
		 * @param State: nos indica el estado con el que comparar
		 * @return valor booleano
		 */
		bool operator==(State)const;

		State operator=(const State&);

		/**
		 * @brief nos manda un flujo mostrando todas las transiciones
		 * @param std::ostream&: un flujo
		 * @return un flujo
		 */
		std::ostream& showTrans(std::ostream&)const;

		std::ofstream& writeFS(std::ofstream&)const;

		void setTrans(State);
		transS_t obtAdj(void);

		void setId(int);

		void setAcceptance(bool);
	};
}

#endif  // STATE_H