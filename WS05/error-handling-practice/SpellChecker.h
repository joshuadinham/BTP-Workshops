#pragma once
#ifndef SDDS_SPELLCHECKER_H
#define SDDS_SPELLCHECKER_H
#include <iostream>
#include <string>
#define WORDS 6
namespace sdds
{
	class SpellChecker
	{
		std::string m_badWords[WORDS]{};
		std::string m_goodWords[WORDS]{};
		size_t m_count[WORDS]{};
		void increment(size_t index);
	public:
		SpellChecker() {};
		SpellChecker(const char* filename);
		void operator()(std::string& text);
		void showStatistics(std::ostream& out) const;

	};
}

#endif // !SDDS_SPELLCHECKER_H


