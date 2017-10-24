#ifndef	WORD_H
#define	WORD_H

#include <string>
#include <cmath>
#include <iostream>
#include "alphabet.hpp"

namespace CYA{
	class Word{
	private:
		Alphabet alphabet_;
		std::string wordStr_;
		bool empty_;	// indica si es la cadena vacía
		bool badWord(void);

	public:
		Word();
		Word& operator=(const char*);
		Word& operator=(const Word&);
		bool operator==(const Word&)const;
		const char* obtWord(void)const;
		bool operator<(const Word&)const;
		void concatenate(Word);
		void invert(void);
		bool isEmpty(void);
		friend std::istream& operator>>(std::istream&, Word&);//friend es necesario?
		const char operator[](int);
		int size(void);
		std::ostream& write(std::ostream&);
		operator std::string();
	};
}


#endif	// WORD_H	