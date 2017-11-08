#include "state.hpp"

namespace CYA{
	State::State(int id, bool acceptance):
	id_(id),
	acceptance_(acceptance)
	{}

	State::State():
	id_(-1),
	acceptance_(false)
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

	bool State::isAcceptance(void)const{
		return acceptance_;
	}

	bool State::isDeath(void)const{
		for(transS_t::iterator it = adjacency_.begin(); it != adjacency_.end(); it++)
			if(id_ != obtainFirst(it->second))
				return false;
		return true;
	}

	std::ostream& State::showTrans(std::ostream& os)const{
		for(transS_t::iterator it = adjacency_.begin(); it != adjacency_.end(); it++)
			os << adjacency_.size() << ' ' << it->first << ' ' << obtainFirst(it->second) << ' ';
		return os;
	}

	bool State::operator==(State q)const{
		return q.id_ == id_;
	}

	std::ofstream& State::writeFS(std::ofstream& ofs)const{
		for(transS_t::iterator it = adjacency_.begin(); it != adjacency_.end(); it++)
			ofs << adjacency_.size() << ' ' << it->first << ' ' << obtainFirst(it->second) << ' ';
		return ofs;
	}

	void State::setTrans(State q){
		adjacency_ = q.obtAdj();
	}

	transS_t State::obtAdj(void){
		return adjacency_;
	}

	State State::operator=(const State& q){
		id_ = q.id_;
		acceptance_ = q.acceptance_;
		adjacency_ = q.adjacency_;
		return *this;
	}

	void State::setId(int id){
		id_ = id;
	}

	void State::setAcceptance(bool acceptance){
		acceptance_ = acceptance;
	}

	int State::obtNTrans(void)const{
		return adjacency_.size();
	}

	std::string State::obtStrTrans(void)const{
		std::string data;
		std::stringstream ss;
		char buffer[256];
		for(transS_t::iterator it = adjacency_.begin(); it != adjacency_.end(); it++){
			ss << ' ';
			ss << it->first;
			ss << ' ';
			sprintf(buffer, "%d", obtainFirst(it->second));
			ss << buffer;
		}
		ss >> data;
		return data;
	}
}