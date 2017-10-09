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
		int getID(void)const;
		bool operator<(const State&)const;
		void setAdj(char, int);
		int getNextS(const char)const;
	};
}

#endif  // STATE_H