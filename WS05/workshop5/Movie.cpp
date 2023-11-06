#include "Movie.h"
#include <sstream>
#include <iomanip>
namespace sdds
{
	std::string trim(const std::string& str, const std::string& whitespace = " \t")
	{

		const auto strBegin = str.find_first_not_of(whitespace);
		if (strBegin == std::string::npos)
		{
			return "";
		}
		const auto strEnd = str.find_last_not_of(whitespace);
		const auto strRange = strEnd - strBegin + 1;

		return str.substr(strBegin, strRange);
	}

	std::string reduce(const std::string& str,
		const std::string& fill = " ",
		const std::string& whitespace = " \t")
	{
		// trim first
		auto result = trim(str, whitespace);

		// replace sub ranges
		auto beginSpace = result.find_first_of(whitespace);
		while (beginSpace != std::string::npos)
		{
			const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
			const auto range = endSpace - beginSpace;

			result.replace(beginSpace, range, fill);


			const auto newStart = beginSpace + fill.length();
			beginSpace = result.find_first_of(whitespace, newStart);
		}

		return result;
	}

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
			std::setw(4) << mov.m_year << " | " << std::left << mov.m_desc << std::endl;
		return out;
	}
}