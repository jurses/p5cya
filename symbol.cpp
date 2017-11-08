#include "symbol.hpp"

namespace CYA{
    Symbol::Symbol(){}
    Symbol::Symbol(bool isTerm, char rep):
    symbol_(rep),
    terminal_(isTerm)
    {}

    bool Symbol::operator<(const Symbol& s)const{
        return symbol_ < s.symbol_;
    }

    Symbol& Symbol::operator=(const Symbol& s){
        terminal_ = s.terminal_;
        symbol_ = s.symbol_;
        return *this;
    }

    void Symbol::setProd(char x, char X){
        production_t prod;
        prod.first = x;
        prod.second = X;
        prods_.insert(prod);
    }

    void Symbol::setAccept(void){
        production_t prod;
        prod.first = '\0';
        prod.second = '~';
        prods_.insert(prod);
    }
    
    char Symbol::obtSymbol(void)const{
      return symbol_;
    }
    
    std::string showProd(void)const{
      std::string strProd;
      std::stringstream ss;
      ss << *prods_.begin();
      for(setProd_t::iterator it = prods_.begin() + 1; it != prods_.end(); it++){
	ss << '|';
	ss << ' ';
	ss << prods_.first;
	ss << prods_.second;
      }
      ss >> strProd;
      return strProd;
    }
}