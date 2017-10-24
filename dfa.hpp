#ifndef DFA_H
#define DFA_H

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include "state.hpp"
#include "word.hpp"

typedef std::set<CYA::State> setStates_t;

namespace CYA{
    class Dfa{
    private:
        void openFile(std::ifstream&, bool);
        int start_;
        int totalStates_;
        bool optimaze_;
        setStates_t Q_;
        int funcTrans(int, const char);
        Word str2Analyze_;
        
    public:
        Dfa(std::ifstream&);
        std::ostream& showDFA(std::ostream&);
        std::istream& putString(std::istream&);
        std::ostream& showStatesDeath(std::ostream&);
        bool accepted(void);
    };
}

#endif  // 