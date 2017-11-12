#ifndef GLR_H_
#define GLR_H_

#include "alphabet.hpp"
#include "symbol.hpp"
#include <set>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <fstream>

typedef std::set<CYA::Symbol> setSymbol_t;

namespace CYA{
    class Glr{
    public:
        Glr();
        void openG(std::string);
	    void genFile(std::string);
        
    private:
        bool linR_; // lineal por la derecha -> en este sentido
        Alphabet sigma_;
        setSymbol_t snt_;   // no terminales
        setSymbol_t st_;    // terminales
        Symbol axiom_;
    };
}

#endif  // GLR_H_