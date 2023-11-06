#include "Book.h"
#include <iomanip>
#include <sstream>
namespace sdds
{
	//reduction lambda function that takes the count for the amount of instance variables in the class, the string to be extracted from, and the function that removes leading and trailing spaces
	auto reduction = [&](size_t count, const std::string& str, std::string(* reduce)(const std::string& str,
		const std::string& fill,
		const std::string& whitespace))
		{
			std::stringstream ss;
				std::string line;
				std::string* members{};

			ss.str(str);
			
			members = new std::string[count];
			for (size_t i = 0; i < count; i++)
			{
				if (i == count - 1)
					std::getline(ss, line, '\n');
				else

					std::getline(ss, line, ',');
				line = reduce(line, " "," \t");
				members[i] = line;
			}
			return members;
		};
	 std::string trim(const std::string& str, const std::string& whitespace = " \t");
	 std::string reduce(const std::string& str,
		const std::string& fill = " ",
		const std::string& whitespace = " \t");

	std::ostream& operator<<(std::ostream& out, const Book& book)
	{
		// TODO: insert return statement here
		out << std::right << std::setfill(' ') << std::setw(20) << book.m_author << " | " << std::setw(22) << book.m_title << " | " << std::setw(5) << book.m_country << " | " << std::setw(4) << book.m_year << " | " << std::setw(6) << std::fixed << std::setprecision(2) << book.m_price << " | " << book.m_desc << std::endl;
		return out;

	}


	Book::Book(const std::string& strBook)
	{
		//create a string pointer to hold the temporary variables of the book details
		std::string* members{};
		//create a function pointer that returns a string that holds my reduce function
		std::string(* reduceStr)(const std::string & str,
			const std::string & fill,
			const std::string & whitespace) = reduce;
		//call the function that reads from the string and puts book details into temporary variables
		//I used 6 to represent the amount of member variables to create which correspond to the amount of instance variables for the class
		members = reduction(6, strBook, reduceStr);
		/*std::stringstream ss;
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
		desc = reduce(desc);*/

		m_author = members[0];
		m_title = members[1];
		m_country = members[2];
		m_price = std::stod(members[3]);
		m_year = std::stoi(members[4]);
		m_desc = members[5];
		delete[]members; 
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