#include "dfa.hpp"

typedef std::set<State> transcition_t;

namespace CYA{
    void DFA::openFile(std::ifstream& ifs, bool optimaze = false)
    optimaze_(optimaze)
    {
        ifs >> totalStates_;
        ifs >> start_;
        for(int i = 0; i < totalStates_; i++){
            bool acceptance;
            int nStates;
            ifs >> state;
            ifs >> acceptance;
            ifs >> nStates;
            State tempState(state, acceptance);
            for(int j = 0; j < nStates; j++){
                char transTemp;
                int nextStateTemp;
                ifs >> transTemp;
                ifs >> nextStateTemp;
                tempState.setAdj(transTemp, nextStateTemp);
            }
            transcition_.insert(tempState);
        }
    }

    int DFA::funcTrans(int, char){
        return transcition_();
    }
}