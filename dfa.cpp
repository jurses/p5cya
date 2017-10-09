#include "dfa.hpp"

typedef std::set<CYA::State> transcition_t;

namespace CYA{

    Dfa::Dfa(std::ifstream& ifs){
        openFile(ifs, false);
    }

    Dfa::Dfa(std::ifstream& ifs, bool optimaze = false){
        openFile(ifs, optimaze);
    }

    void Dfa::openFile(std::ifstream& ifs, bool optimaze = false){
        optimaze_ = optimaze_;
        ifs >> totalStates_;
        ifs >> start_;
        for(int i = 0; i < totalStates_; i++){
            bool acceptance;
            int state, nStates;
            ifs >> acceptance;
            ifs >> nStates;
            ifs >> state;
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

    int Dfa::funcTrans(int actualState, char trans){
        for(transcition_t::iterator it = transcition_.begin(); it != transcition_.end(); it++)
            if(it->getID() == actualState){
                return it->getNextS(trans);
            }
        return -1;
    }

    std::istream& Dfa::putString(std::istream& is){
        //std::getline(is, str2Analyze_);
        is >> str2Analyze_;
        return is;
    }
    
    bool Dfa::accepted(void){
        int qState = start_;
        for(int i = 0; i < str2Analyze_.size(); i++){

        }
    }
}