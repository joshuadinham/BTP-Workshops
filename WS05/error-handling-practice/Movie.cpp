#include "Movie.h"
#include <sstream>
#include <iomanip>
namespace sdds
{
	extern std::string trim(const std::string& str, const std::string& whitespace = " \t");
	extern std::string reduce(const std::string& str,
		const std::string& fill = " ",
		const std::string& whitespace = " \t");

	Movie::Movie(const std::string& strMovie)
	{
		if (strMovie == "")
		{
			return;
		}
		std::stringstream ss(strMovie);
		std::string title{};
		std::string year{};
		std::string desc{};

		std::getline(ss, title, ',');
		title = reduce(title);
		std::getline(ss, year, ',');
		year = reduce(year);
		std::getline(ss, desc, '\n');
		desc = reduce(desc);

		if (title != "" && year != "" && desc != "")
		{
			m_title = title;
			m_year = std::stoi(year);
			m_desc = desc;
		}
		else
		{
			return;
		}
	}

	std::ostream& operator<<(std::ostream& out, const Movie& mov)
	{
		out << std::right << std::setfill(' ') << std::setw(40) << mov.m_title << " | " <<
			std::setw(4) << mov.m_year << std::left << mov.m_desc;
		return out;
	}
}