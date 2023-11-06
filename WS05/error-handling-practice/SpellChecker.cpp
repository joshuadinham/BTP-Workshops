#include "SpellChecker.h"
#include <iomanip>
#include <fstream>

void sdds::SpellChecker::increment(size_t index)
{
	m_count[index]++;
}

sdds::SpellChecker::SpellChecker(const char* filename)
{
	std::fstream fin(filename);
	std::string good;
	std::string bad;
	unsigned count = 0;
	if (!fin)
	{
		const char* message = "Bad file name!";
		throw message;
	}
	else
	{
		do
		{
				fin >> bad;
				fin >> good;
				if (count < WORDS)
				{
					m_goodWords[count] = good;
					m_badWords[count] = bad;
				count++;
				}
		} while (fin);
	}
}

void sdds::SpellChecker::operator()(std::string& text)
{
	if (text == "")
	{
		return;
	}
	
	for (size_t i = 0; i < WORDS; i++)
	{
	
		std::size_t found{};
		do
		{
			found = text.find(m_badWords[i]);
			if (found != std::string::npos)
			{
				text.replace(found, m_badWords[i].length(), m_goodWords[i]);
				increment(i);
			}

		} while (found != std::string::npos);
	}
}

void sdds::SpellChecker::showStatistics(std::ostream& out) const
{
	
	out << "Spellchecker Statistics" << std::endl;
	for (size_t i = 0; i < WORDS; i++)
	{
		out << std::right << std::setfill(' ') << std::setw(15) << m_badWords[i] << ": " << m_count[i] << " replacements" << std::endl;

	}

}
