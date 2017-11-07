#ifndef DFA_H
#define DFA_H

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "state.hpp"
#include "word.hpp"
#include "alphabet.hpp"

typedef std::set<CYA::State> setStates_t;
typedef std::set<setStates_t> partition_t;

namespace CYA{
    class Dfa{
    private:
        Alphabet sigma_;
        int start_;
        int totalStates_;
        setStates_t Q_;
        Word str2Analyze_;

        /** 
         * @brief tras un símbolo devuelve el siguiente estado
         * @param int: estado actual
         * @param const char: símbolo de transición
         * @return id del estado siguiente
         */
        int funcTrans(int, const char);

        /**
         * @brief obtiene el estado a través de un id
         * @param int: el id
         * @return el objeto estado correspondiente
         */
        State obtState(int);

        /**
         * @brief crea una nueva partición
         * @param typedef std::set<setStates_t> partition_t:
         * @return devuelve una partición
         */
        partition_t createNewPartition(partition_t);

        /**
         * @brief descompone la partición dada
         * @param typedef std::set<CYA::State> setStates_t:
         * @param typedef std::set<setStates_t> partition_t:
         * @return devuelve la partición
         */
        partition_t descomp(setStates_t, partition_t);

        /**
         * @brief parte la partición
         * @param 
         * @param
         * @return
         */
        partition_t breaker(setStates_t, char, partition_t);

        /**
         * @brief
         * @param
         * @param
         * @return
         */
        partition_t unionPart(partition_t, partition_t);

        /**
         * @brief
         * @param
         * @param
         * @return
         */
        bool comparePart(partition_t, partition_t);

        bool isIn(int, setStates_t);

        bool isIn(int, partition_t);

        bool checkAcceptance(setStates_t);

        std::ostream& showPartition(std::ostream&, partition_t);
        
        std::ostream& showSetStates(std::ostream&, setStates_t);

        void buildDfa(partition_t);

        State obtMainS(setStates_t);
                
    public:

        /**
         * @brief abre el archivo
         * @param std::ifstream&: flujo de archivo
         */
        void openFile(std::ifstream&);

        /**
         * @brief constructor del dfa
         * @param std::ifstream&: se le pasa un flujo desde un fichero
         */
        Dfa(std::ifstream&);

        Dfa();

        /**
         * @brief muestra el dfa
         * @param std::ostream& manda un flujo
         * @return devuelve un flujo
         */
        std::ostream& showDFA(std::ostream&);

        /**
         * @brief pone una cadena para ser analizada
         * @param std::istream&: flujo
         * @return devuelve un flujo
         */
        std::istream& putString(std::istream&);

        /**
         * @brief muestra los estados de muerte
         * @param std::ostream&
         * @return devuelve un flujo
         */
        std::ostream& showStatesDeath(std::ostream&);

        /**
         * @brief minimiza el dfa
         */
        void minDfa(void);

        /**
         * @brief comprueba si la cadena es aceptada
         * @return devuelve verdadero si la cadena se acepta
         */
        bool accepted(void);

        void exportDfa(const char*);
    };
}

#endif  // 
