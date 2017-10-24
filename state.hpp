#ifndef STATE_H
#define STATE_H

#include <set>
#include <ostream>
#include <utility>

//finite states ID set, conjuntos id de estados finitos
typedef std::set<int> FSIDS_t;
typedef std::pair<char, FSIDS_t> trans_t;
typedef std::set<trans_t> transS_t;

namespace CYA{
	class State{
	private:
		int id_;
		bool acceptance_;
		transS_t adjacency_;
		int obtainFirst(FSIDS_t)const;
		
	public:
		State(int, bool);   // id, acceptance
		int getID(void)const;
		bool operator<(const State&)const;
		void setAdj(char, int);
		int getNextS(const char)const;
	};
}

#endif  // STATE_H