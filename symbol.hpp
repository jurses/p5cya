#ifndef SYMBOL_H_
#define SYMBOL_H_

namespace CYA{
    class Symbol{
    private:
        bool terminal_;
        char symbol_;
    public:
        Symbol();
        Symbol(bool, char);
        bool isTerminal(void);
        char obtSymbol(void);
        bool operator <(const Symbol&);
    };
}

#endif  //SYMBOL_H_