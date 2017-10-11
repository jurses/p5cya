#ifndef DFA_H
#define DFA_H

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include "state.hpp"
#include "alphabet.hpp"
#include "word.hpp"
#include <stack>

typedef std::set<CYA::State> transcition_t; // set deestados

namespace CYA{
    class Dfa{
    private:
        void openFile(std::ifstream&, bool);
        int start_;
        int totalStates_;
        bool optimaze_;
        transcition_t transcition_;
        int funcTrans(int, const char);
        int funcTrans(State, const char);
        State obtState(int)const;
        Word str2Analyze_;
        
    public:
        Dfa(std::ifstream&, bool);  // el segundo parámetro indica si se quiere indicar los estados de muerte antes
        Dfa(std::ifstream&);
        Dfa(const char*);
        std::ostream& showDFA(std::ostream&);
        std::istream& putString(std::istream&);
        std::ostream& showStatesDeath(std::ostream&);
        bool accepted(void);
    };
}

#endif  // 