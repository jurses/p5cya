#include "state.hpp"

namespace CYA{
	State::State(int id, bool acceptance):
	id_(id),
	acceptance_(acceptance)
	{}
	
	void State::setAdj(char t, int q){
		adjacency[t] = q;
	}

	int State::getNextS(char t){
		return adjacency_[t];
	}

	State::operator int(){
		return id_;
	}

	bool State::operator<(const State& q)const{
		return id_ < q.id_;
	}
}