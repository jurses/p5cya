#ifndef DFA_H
#define DFA_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "state.hpp"

typedef std::vector<State> transcition_t;

namespace CYA{
    class Dfa{
    private:
        void openFile(std::ifstream&);
        int start_;
        int totalStates_;
        bool optimaze_;
        transcition_t transcition_;
    public:
        Dfa(std::ifstream&, bool = false);  // el segundo parámetro indica si se quiere indicar los estados de muerte antes
        std::ostream& showDFA(std::ostream&);
        bool analyzeString(std::string);
        std::ostream& showStatesDeath(std::ostream&);
    };
}

#endif  // 