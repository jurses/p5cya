#include "alphabet.hpp"

namespace CYA{
	const std::set<char> Alphabet::obtSet(void){
		assert(!setAlphab_.empty());	// el alfabeto no puede estar vacío
		return setAlphab_;
	}

	Alphabet& Alphabet::operator=(const Alphabet& A){
		setAlphab_ = A.setAlphab_;
		return *this;
	}

	Alphabet::Alphabet(){
		std::ifstream ifs("alpha1.abc", std::ifstream::in);
		char tempC;
		while(ifs >> tempC)
			setAlphab_.insert(tempC);

		ifs.close();
	}

	Alphabet::Alphabet(const char* filename){
		std::ifstream ifs(filename, std::ifstream::in);
		char tempC;
		while(ifs >> tempC)
			setAlphab_.insert(tempC);

		ifs.close();
	}
}