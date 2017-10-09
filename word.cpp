#include "word.hpp"
#include <iostream>
namespace CYA{
	Word::Word(){
		word_.resize(0);
		empty_ = true;
		assert(badWord());
	}

	Word::Word(const Alphabet& A)
	{
		alphabet_ = A;
		assert(badWord());
	}

	Word::Word(char c){
		if(c == '&')
			empty_ = true;

		word_.push_back(c);
		assert(badWord());
	}

	Word::Word(const std::string& ws){
		word_ = ws;
		empty_ = false;
		assert(badWord());
	}

	Word::Word(const Word& w){
		alphabet_ = w.alphabet_;
		word_ = w.word_;
		empty_ = w.empty_;
	}

	const char* Word::obtWord(void)const{
		return word_.c_str();
	}

	Word& Word::operator=(const Word& word){
		word_ = word.word_;
		empty_ = word.empty_;
		assert(badWord());
		return *this;
	}

	Word& Word::operator=(const char* word){
		word_ = word;
		assert(badWord());
		empty_ = false;
		return *this;
	}

	bool Word::operator<(const Word& word)const{	// necesario, promete al compilador no tocar el word
		if(word_.size() != word.word_.size())
			return word_.size() < word.word_.size();

		for(int i = 0; i < word_.size(); i++)
			if(word_[i] != word.word_[i])
				return word_[i] < word.word_[i];
		
		return false;	// es la misma palabra
	}

	void Word::invert(void){
		char swapTemp;
		for(int i = 0; i < word_.size()/2; i++){
			swapTemp = word_[i];
			word_[i] = word_[word_.size() - 1 - i];
			word_[word_.size() - 1 - i] = swapTemp;
		}
	}

	Word::operator std::string(void){
		return word_;
	}

	void Word::concatenate(Word w){
		if(!empty_)
			word_ += w;
		else
			word_ = w;
		
		assert(badWord());
	}

	bool Word::operator==(const Word& w)const{
		if(word_.compare(w.word_) == 0)
			return true;
		else
			return false;
	}

	std::ostream& Word::write(std::ostream& os){
		os << word_;
		return os;
	}

	bool Word::isEmpty(void){
		return empty_;
	}

	const char Word::operator[](int i){
		return word_[i];
	}

	bool Word::badWord(void){
		for(int i = 0; i < word_.size(); i++)
			if(!alphabet_.checkChar(word_[i]))
				return false;
		
		return true;
	}

	int Word::size(void){
		return word_.size();
	}

	std::istream& operator>>(std::istream& is, Word& w){
		is >> w.word_;
		assert(w.badWord());
		return is;
	}
}