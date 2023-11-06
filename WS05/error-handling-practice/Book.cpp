#include "Book.h"
#include <iomanip>
#include <sstream>
namespace sdds
{
	 std::string trim(const std::string& str, const std::string& whitespace = " \t");
	 std::string reduce(const std::string& str,
		const std::string& fill = " ",
		const std::string& whitespace = " \t");

	std::ostream& operator<<(std::ostream& out, const Book& book)
	{
		// TODO: insert return statement here
		out << std::right << std::setfill(' ') << std::setw(20) << book.m_author << " | " << std::setw(22) << book.m_title << " | " << std::setw(5) << book.m_country << " | " << std::setw(4) << book.m_year << " | " << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | " << book.m_desc;
		return out;

	}


	Book::Book(const std::string& strBook)
	{
		std::stringstream ss;
		ss.str(strBook);
		std::string author{};
		std::string title{};
		std::string country{};
		std::string year{};
		std::string price{};
		std::string desc{};

		std::getline(ss, author, ',');
		author = reduce(author);
		std::getline(ss, title, ',');
		title = reduce(title);
		std::getline(ss, country, ',');
		country = reduce(country);
		std::getline(ss, price, ',');
		price = reduce(price);
		std::getline(ss, year, ',');
		year = reduce(year);
		std::getline(ss, desc, '\n');
		desc = reduce(desc);

		m_author = author;
		m_title = title;
		m_country = country;
		m_price = std::stod(price);
		m_year = std::stoi(year);
		m_desc = desc;
	}

	Book& Book::operator=(const Book& book)
	{
		m_author = book.m_author;
		m_title = book.m_title;
		m_country = book.m_country;
		m_year = book.m_year;
		m_price = book.m_price;
		m_desc = book.m_desc;
		return *this;
	}

}