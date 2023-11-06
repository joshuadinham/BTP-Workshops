#pragma once
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include <string>
#include <iostream>
namespace sdds
{
	class Book
	{
		std::string m_author{};
		std::string m_title{};
		std::string m_country{};
		size_t m_year{};
		double m_price{};
		std::string m_desc{};

	public:
		Book() {};
		const std::string& title() const { return m_title; };
		template<typename T> void fixSpelling(T& spellChecker);
		const std::string& country() const { return m_country; };
		const size_t& year() const { return m_year; };
		double& price() { return m_price; };
		Book(const std::string& strBook);
		friend std::ostream& operator<<(std::ostream& out, const Book& book);
		Book& operator=(const Book& book);
	};
	template<typename T>
	inline void Book::fixSpelling(T& spellChecker)
	{
		spellChecker(m_desc);
	}
}

#endif // !SDDS_BOOK_H


