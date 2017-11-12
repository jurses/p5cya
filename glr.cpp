#include "glr.hpp"

namespace CYA{
    Glr::Glr():
    linR_(true){
    }
    
    void Glr::genFile(std::string name){
		std::ofstream ofs(name.c_str(), std::ofstream::out);
		ofs << st_.size();
		ofs << std::endl;
		for(setSymbol_t::iterator it = st_.begin(); it != st_.end(); it++){
			ofs << it->obtSymbol();
			ofs << ' ';
		}
		ofs << std::endl;
		ofs << snt_.size();
		for(setSymbol_t::iterator it = snt_.begin(); it != snt_.end(); it++){
			ofs << it->obtSymbol();
			ofs << ' ';
		}
		ofs << axiom_.showProd();
		ofs << std::endl;
		for(setSymbol_t::iterator it = snt_.begin(); it != snt_.end(); it++)
			if(!(*it == axiom_)){
				ofs << it->showProd();
				ofs << std::endl;
			}
    }
    
    void Glr::openG(std::string input){
        std::stringstream ss;
        int terminal, total, initial, id, nprod;
        bool accept;
        ss << input;
        ss >> terminal;
        for(int i = 0; i < terminal; i++){
            char rep;
            ss >> rep;
            Symbol x(true, rep);
            st_.insert(x);
        }
        ss >> total;
        ss >> initial;
        for(int i = 0; i < total; i++){
            char rep;
            ss >> id;
            ss >> accept;
            rep = id + 'A';
            Symbol X(false, rep);
            ss >> nprod;
            for(int j = 0; j < nprod; j++){
                char term, noTerm;
                ss >> noTerm;
                ss >> term;
                X.setProd(term, noTerm + 'A');
            }

            if(accept)
                X.setAccept();
            
            if(id == initial)
                axiom_ = X;
            
            st_.insert(X);
        }
    }
}