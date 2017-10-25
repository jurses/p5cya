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
		setStates_t noAcceptanceS, acceptanceS;
		for(setStates_t::iterator it = Q_.begin(); it != Q_.end(); it++)
			if(it->isAcceptance())
				acceptanceS.insert(*it);
			else
				noAcceptanceS.insert(*it);

		partition_t p, oldP;
		p.insert(noAcceptanceS);
		p.insert(acceptanceS);

		do{
			oldP = p;
			p = createNewPartition(oldP);
        }while(!comparePart(oldP, p));	// mientras no sean iguales
        
        totalStates_ = p.size();
        Q_.clear();
        for(partition_t::iterator it1 = p.begin(); it1 != p.end(); it1++){
            bool acceptance;
            for(setStates_t::iterator it2 = it1->begin(); it2 != it1->end(); it2++){
                if(acceptance == it2->isAcceptance())
                    acceptance = true;
                State qAux(it2->begin()->getID(), acceptance);
                qAux.addTrans(it2->begin());   // copia las transiciones del primer elemento del primer conjunto
            }
            Q_.insert(qAux);
        }
    }

    bool Dfa::comparePart(partition_t P1, partition_t P2){
        partition_t P3;
        P3 = unionPart(P1, P2);
        return (P3.size() == P1.size() && P3.size() == P2.size());
    }

	partition_t Dfa::createNewPartition(partition_t oldP){
		partition_t p;

		for(partition_t::iterator it = oldP.begin(); it != oldP.end(); it++)
			p = unionPart(p, descomp(*it, oldP));

		return p;
	};

	partition_t Dfa::descomp(setStates_t G, partition_t p){
		partition_t T;
		T.insert(G);
		std::set<char> sigmaS = sigma_.obtSet();
		for(std::set<char>::iterator it1 = sigmaS.begin(); it1 != sigmaS.end(); it1++){	//iterador del alfabeto
			partition_t k;	// se llama p, pero yo lo llamo k
			for(partition_t::iterator it2 = T.begin(); it2 != T.end(); it2++){
				partition_t Tp;	// T prima
				Tp = (breaker(*it2, *it1, p));
				k = unionPart(k, Tp);
			}
			T = k;
		}
		return T;
    }

	partition_t Dfa::breaker(setStates_t G, char a, partition_t p){
        partition_t T;
        setStates_t X;
		for(partition_t::iterator itPart = p.begin(); itPart != p.end(); itPart++){	// *it = H
			setStates_t Gp = allStates2(G, a);  // todos los estados de G que van con 'a'
			for(setStates_t::iterator it1 = Gp.begin(); it1 != Gp.end(); it1++)
				for(setStates_t::iterator it2 = itPart->begin(); it2 != itPart->end(); it2++)
                    if(*it1 == *it2)
                        X.insert(*it1);
        }
        
		T.insert(X);
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

	setStates_t Dfa::allStates2(setStates_t G, char a){
		setStates_t Gp;
		for(setStates_t::iterator it = G.begin(); it != G.end(); it++)
			Gp.insert(obtState(funcTrans(it->getID(), a)));

		// G' = {t(q0, a), t(q1, a), t(q2, a)...}
		return Gp;
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
}
