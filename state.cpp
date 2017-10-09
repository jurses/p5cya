#include "state.hpp"

namespace CYA{
	State::State(int id, bool acceptance):
	id_(id),
	acceptance_(acceptance)
	{}
	
	void State::setAdj(char t, int q){
		adjacency_[t] = q;
	}

	int State::getNextS(const char t)const{
		return adjacency_.at(t);
	}

	int State::getID(void)const{
		return id_;
	}

	bool State::operator<(const State& q)const{
		return id_ < q.id_;
	}
}