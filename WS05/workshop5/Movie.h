#pragma once
#ifndef SDDS_MOVIE_H
#define SDDS_MOVIE_H
#include <iostream>
#include <string>
namespace sdds
{

	class Movie
	{
		std::string m_title{};
		size_t m_year{};
		std::string m_desc{};
	public:
		Movie() {};
		const std::string& title() const { return m_title; };
		Movie(const std::string& strMovie);
		template<typename T> void fixSpelling(T& spellChecker) 
		{
			spellChecker(m_title);
			spellChecker(m_desc);
		}
		friend std::ostream& operator<<(std::ostream& out, const Movie& mov);
	};

}
#endif // !SDDS_MOVIE_H

