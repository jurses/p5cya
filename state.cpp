#include "state.hpp"

namespace CYA{
	State::State(int id, bool acceptance):
	id_(id),
	acceptance_(acceptance)
	{}
	
	void State::setAdj(char t, int q){
		trans_t transAux;
		FSIDS_t fsAux;
		
		fsAux.insert(q);

		transAux.first = t;
		transAux.second = fsAux;

		adjacency_.insert(transAux);
	}

	int State::obtainFirst(FSIDS_t fs)const{
		return *fs.begin();
	}

	int State::getNextS(const char t)const{
		for(transS_t::iterator it = adjacency_.begin(); it != adjacency_.end(); it++)
			if(it->first == t)
				return obtainFirst(it->second);
		
		return -1;
	}

	int State::getID(void)const{
		return id_;
	}

	bool State::operator<(const State& q)const{
		return id_ < q.id_;
	}
}