#include "word.hpp"
#include <iostream>

namespace CYA{
	Word::Word(){
		wordStr_.resize(0);
		empty_ = true;
		assert(goodWord());
	}

	const char* Word::obtWord(void)const{
		return wordStr_.c_str();
	}

	void Word::setAlphabet(Alphabet& A){
		alphabet_ = A;
	}

	Word& Word::operator=(const Word& wordStr){
		wordStr_ = wordStr.wordStr_;
		empty_ = wordStr.empty_;
		assert(goodWord());
		return *this;
	}

	Word& Word::operator=(const char* wordStr){
		wordStr_ = wordStr;
		assert(goodWord());
		empty_ = false;
		return *this;
	}

	bool Word::operator<(const Word& wordStr)const{	// necesario, promete al compilador no tocar el wordStr
		if(wordStr_.size() != wordStr.wordStr_.size())
			return wordStr_.size() < wordStr.wordStr_.size();

		for(int i = 0; i < wordStr_.size(); i++)
			if(wordStr_[i] != wordStr.wordStr_[i])
				return wordStr_[i] < wordStr.wordStr_[i];
		
		return false;	// es la misma palabra
	}

	void Word::invert(void){
		char swapTemp;
		for(int i = 0; i < wordStr_.size()/2; i++){
			swapTemp = wordStr_[i];
			wordStr_[i] = wordStr_[wordStr_.size() - 1 - i];
			wordStr_[wordStr_.size() - 1 - i] = swapTemp;
		}
	}

	Word::operator std::string(void){
		return wordStr_;
	}

	void Word::concatenate(Word w){
		if(!empty_)
			wordStr_ += w;
		else
			wordStr_ = w;
		
		assert(goodWord());
	}

	bool Word::operator==(const Word& w)const{
		if(wordStr_.compare(w.wordStr_) == 0)
			return true;
		else
			return false;
	}

	std::ostream& Word::write(std::ostream& os){
		os << wordStr_;
		return os;
	}

	bool Word::isEmpty(void){
		return empty_;
	}

	const char Word::operator[](int i){
		return wordStr_[i];
	}

	bool Word::goodWord(void){
		if(!empty_)
			for(int i = 0; i < wordStr_.size(); i++)
				if(!alphabet_.checkChar(wordStr_[i]))
					return false;
					
		return true;
	}

	int Word::size(void){
		if(empty_)
			return 0;
		else
			return wordStr_.size();
	}

	std::istream& operator>>(std::istream& is, Word& w){
		std::string wAux;
		is >> wAux;
		w.wordStr_ = wAux;
		if(wAux.size() == 1 && wAux[0] == '~')
			w.empty_ = true;
		else
			w.empty_ = false;

		assert(w.goodWord());
		return is;
	}
}