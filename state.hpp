#ifndef STATE_H
#define STATE_H

#include <map>
#include <ostream>

namespace CYA{
	class State{
	private:
		int id_;
		bool acceptance_;
		std::map<char, int> adjacency_;
		
	public:
		State(int, bool);   // id, acceptance
		operator int();
		bool operator<(const State&)const;
		void setAdj(char, int);
		int getNextS(char);
	}
}

#endif  // STATE_H