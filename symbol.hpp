#ifndef SYMBOL_H_
#define SYMBOL_H_

#include <set>
#include <vector>
#include <utility>

typedef std::pair<char, char> production_t;
typedef std::set<production_t> setProd_t;

namespace CYA{
    class Symbol{
    private:
        setProd_t prods_;
        bool terminal_;
        char symbol_;
    public:
        Symbol();
        Symbol(bool, char); //es terminal, simbolo representante
        bool isTerminal(void);
        char obtSymbol(void);
        bool operator<(const Symbol&)const;
        Symbol& operator=(const Symbol&);
        void setProd(char, char);
        void setAccept(void);
    };
}

#endif  //SYMBOL_H_