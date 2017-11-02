#include "dfa.hpp"

typedef std::set<CYA::State> setStates_t;

namespace CYA{

    Dfa::Dfa(std::ifstream& ifs){
        openFile(ifs);
    }

    Dfa::Dfa(){}

    void Dfa::openFile(std::ifstream& ifs){
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
                sigma_.insert(transTemp);
                ifs >> transTemp;
                ifs >> nextStateTemp;
                tempState.setAdj(transTemp, nextStateTemp);
            }
            Q_.insert(tempState);
        }
        str2Analyze_.setAlphabet(sigma_);
    }

    int Dfa::funcTrans(int actualState, char trans){
        for(setStates_t::iterator it = Q_.begin(); it != Q_.end(); it++)
            if(it->getID() == actualState)
                return it->getNextS(trans);
        return -1;
    }

    std::istream& Dfa::putString(std::istream& is){
        is >> str2Analyze_;
        return is;
    }
    
    bool Dfa::accepted(void){
        std::cout << "Estado actual" << '\t' << "Entrada" << '\t' << "Siguiente estado" << std::endl;
        int qState = start_;
        if(str2Analyze_.size() > 0) //redundante porque la condición ya la pone el for, pero...
            for(int i = 0; i < str2Analyze_.size(); i++){
                std::cout << qState << '\t' << str2Analyze_[i] << '\t' << funcTrans(qState, str2Analyze_[i]) << std::endl;
                qState = funcTrans(qState, str2Analyze_[i]);
                if(qState == -1)
                    return false;
            }
        else
            std::cout << "Tratamos la cadena vacía" << std::endl;

        return obtState(qState).isAcceptance();
    }

    State Dfa::obtState(int q){
        for(setStates_t::iterator it = Q_.begin(); it != Q_.end(); it++)
            if(it->getID() == q)
                return *it;
    }

    std::ostream& Dfa::showStatesDeath(std::ostream& os){
        for(setStates_t::iterator it = Q_.begin(); it != Q_.end(); it++)
            if(it->isDeath())
                os << "El estado " << it->getID() << " es un estado de muerte" << std::endl;
        return os;
    }

    std::ostream& Dfa::showDFA(std::ostream& os){
        os << totalStates_ << std::endl;
        os << start_ << std::endl;
        for(setStates_t::iterator it = Q_.begin(); it != Q_.end(); it++){
            os << it->getID() << ' ';
            os << it->isAcceptance() << ' ';
            it->showTrans(os);
            os << std::endl;
        } 
        return os;
    }

    void Dfa::minDfa(void){
        partition_t PI, oldPI;
        setStates_t F, NF;
        for(setStates_t::iterator its = Q_.begin(); its != Q_.end(); its++)
            if(its->isAcceptance())
                F.insert(*its);
            else
                NF.insert(*its);
        do{
            oldPI = PI;
            PI = createNewPartition(oldPI);
        }while(!comparePart(PI, oldPI));
        buildDfa(PI);
    }

    bool Dfa::checkAcceptance(setStates_t Q){
        for(setStates_t::iterator it = Q.begin(); it != Q.end(); it++)
            if(it->isAcceptance())
                return true;
        return false;
    }

    bool Dfa::comparePart(partition_t P1, partition_t P2){  //return true if equal
        partition_t P3;
        P3 = unionPart(P1, P2);
        return (P3.size() == P1.size() && P3.size() == P2.size());
    }

	partition_t Dfa::createNewPartition(partition_t oldPI){
		partition_t PI;

		for(partition_t::iterator it = oldPI.begin(); it != oldPI.end(); it++)
            PI = unionPart(PI, descomp(*it, oldPI));
        
		return PI;
    };
    
    std::ostream& Dfa::showPartition(std::ostream& os, partition_t p){
        os << '{';
        for(partition_t::iterator it = p.begin(); it != p.end(); it++){
            showSetStates(os, *it);
            os << ", ";
        }
        os << '}';
        return os;
    }

    std::ostream& Dfa::showSetStates(std::ostream& os, setStates_t Q){
        os << '{';
        for(setStates_t::iterator its = Q.begin(); its != Q.end(); its++)
            os << its->getID() << ", ";
        os << '}';
        return os;
    }

	partition_t Dfa::descomp(setStates_t G, partition_t PI){
		partition_t T, Tx, P;
		T.insert(G);
		std::set<char> sigmaS = sigma_.obtSet();
		for(std::set<char>::iterator it1 = sigmaS.begin(); it1 != sigmaS.end(); it1++){	//iterador del alfabeto
            P.clear();
            for(partition_t::iterator it2 = T.begin(); it2 != T.end(); it2++){
                Tx = breaker(G, *it1, PI);
                P = unionPart(P, Tx);
            }
            T = P;
		}
		return T;
    }

    bool Dfa::isIn(int id, setStates_t Q){
        for(setStates_t::iterator it = Q.begin(); it != Q.end(); it++)
            if(id == it->getID())
                return true;
        
        return false;
    }

    bool Dfa::isIn(int id, partition_t P){
        for(partition_t::iterator it1 = P.begin(); it1 != P.end(); it1++)
            if(isIn(id, *it1))
                return true;
    }

	partition_t Dfa::breaker(setStates_t G, char a, partition_t PI){
        partition_t T, auxP;
        setStates_t H, auxS;
        State qG, qH;
        for(partition_t::iterator it1 = PI.begin(); it1 != PI.end(); it1++){
            H = *it1;
            for(setStates_t::iterator it2 = H.begin(); it2 != H.end(); it2++){
                for(setStates_t::iterator it3 = G.begin(); it3 != G.end(); it3++){
                    State qGH;
                    qGH = obtState(funcTrans(it3->getID(), a));
                    if(it2->getID() == qGH.getID())
                        auxS.insert(*it2);
                    auxP.insert(auxS);
                    auxS.clear();
                    T = unionPart(T, auxP);
                    auxP.clear();
                }
            }
        }
		return T;
    }

	partition_t Dfa::unionPart(partition_t P1, partition_t P2){
		partition_t P3;
        partition_t::iterator it;

		for(it = P1.begin(); it != P1.end(); it++)
			P3.insert(*it);

		for(it = P2.begin(); it != P2.end(); it++)
            P3.insert(*it);
            
		return P3;
	}

    void Dfa::exportDfa(const char* name){
        std::ofstream ofs(name, std::ostream::out);
        ofs << totalStates_ << std::endl;
        ofs << start_ << std::endl;
        for(setStates_t::iterator it = Q_.begin(); it != Q_.end(); it++){
            ofs << it->getID() << ' ';
            ofs << it->isAcceptance() << ' ';
            State auxq = *it;
            auxq.writeFS(ofs);
            ofs << std::endl;
        }
        ofs.close();
    }

    void Dfa::buildDfa(partition_t P){
        setStates_t aux;
        partition_t Pp;
        for(partition_t::iterator it1 = P.begin(); it1 != P.end(); it1++){
            while(it1->size() > 1)
                Pp.insert(simpTrans(*it1));
        }
                    
    }

    setStates_t Dfa::simpTrans(setStates_t Q){
        setStates_t Qcopy;
        Qcopy = Q;
        std::set<char> sigmaS = sigma_.obtSet();
		for(std::set<char>::iterator it1 = sigmaS.begin(); it1 != sigmaS.end(); it1++){
            for(setStates_t::iterator it2 = Q.begin(); it2 != Q.end(); it2++)
                if(isIn(obtState(funcTrans(it2->getID(), *it1)).getID(), Q))
                    Qcopy.erase(*it2);
                else{
                    setStates_t aux;
                    aux.insert(*it2);
                    Qcopy = aux;
                }
        }
        return Qcopy;
    }
}
