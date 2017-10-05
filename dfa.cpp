#include "dfa.hpp"

typedef std::vector<State> transcition_t;

namespace CYA{
    void DFA::openFile(std::ifstream& ifs){
        ifs >> totalStates_;
        ifs >> start_;
        for(int i = 0; i < totalStates_; i++){
            bool acceptance;
            int nStates;
            ifs >> state;
            ifs >> acceptance;
            ifs >> nStates;
            State tempState(state, acceptance);
            transcition_.push_back(tempState)
            for(int j = 0; j < nStates; j++){
                char transTemp;
                int nextStateTemp;
                ifs >> transTemp;
                ifs >> nextStateTemp;
                transcition_[state].setAdj(transTemp, nextStateTemp);
            }
        }
    }

    DFA::DFA(std::ifstream& ifs){
        
    }

    DFA::
}