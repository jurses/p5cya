#ifndef GLR_H_
#define GLR_H_

#include "alphabet.hpp"
#include "symbol.hpp"
#include <set>
#include <vector>
#include <utility>

typedef std::set<Symbol> setSymbol_t;
typedef std::vector<Symbol> vecSymbol_t;    //el vector está guay porque mantiene el orden por símbolos ingresados
typedef std::pair<Symbol, std::set<vecSymbol_t>> production_t;
typedef std::set<production_t> setProd_t;   //conjunto de producciones

namespace CYA{
    class Glr{
    public:
        Glr();
        
    private:
        bool linR_; // lineal por la derecha -> en este sentido
        Alphabet sigma_;
        setSymbol_t snt_;
        setSymbol_t st_;
        Symbol axiom_;
        setProd_t rules_;
    };
}

#endif  // GLR_H_