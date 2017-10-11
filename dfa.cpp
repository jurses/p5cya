#include "dfa.hpp"

typedef std::set<CYA::State> transcition_t; //modificar el nombre del typedef

namespace CYA{

    Dfa::Dfa(std::ifstream& ifs){
        openFile(ifs, false);
    }

    Dfa::Dfa(const char *nameFile){
        std::ifstream ifs(nameFile, std::ifstream::in);
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

    State Dfa::obtState(int q)const{
        for(transcition_t::iterator it = transcition_.begin(); it != transcition_.end(); it++)
            if(it->getID() == q)
                return (*it);
            
    }

    int Dfa::funcTrans(int actualState, char trans){
        int nextS = obtState(actualState).getNextS(trans);
        return nextS;
    }

    int Dfa::funcTrans(State s, char trans){
        return s.getNextS(trans);
    }

    std::istream& Dfa::putString(std::istream& is){
        is >> str2Analyze_;
        return is;
    }
    
    bool Dfa::accepted(void){
        int qState = start_;
        for(int i = 0; i < str2Analyze_.size(); i++)
            qState = funcTrans(qState, str2Analyze_[i]);
        
        return obtState(qState).isAceptance();
    }

    std::ostream& Dfa::showStatesDeath(std::ostream& os){
        Alphabet A;
        std::stack<int> sStates;
        A = str2Analyze_.obtAlphabet();
        std::set<char> tempSet = A.obtSet();
        for(transcition_t::iterator it = transcition_.begin(); it != transcition_.end(); it++){
            if(it->isAceptance()){
                for(std::set<char>::iterator it2 = tempSet.begin(); it2 != tempSet.end(); it2 ++)
                    sStates.push(funcTrans(*it, *it2));
                
                while(!sStates.empty()){
                    if(*it == sStates.top())
                        sStates.pop();
                    else
                        break;

                    if(sStates.empty())
                        os << it->getID() << ": es un estado de muerte" << std::endl;
                }
            }
        }
        return os;
    }
}