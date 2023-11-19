#include "CovidCollection.h"
#include <fstream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <iomanip>
#include <functional>
#define FIELD 79
#define COUNTRY_FIELD 84
#define PERCENTAGE_FIELD 86

void reduce(std::string& str, std::string whitespace = " /t/v");
void reduce(std::string& str, std::string whitespace)
{
	size_t begin = str.find_first_not_of(whitespace);
	size_t end = str.find_last_not_of(whitespace);
	str = str.substr(begin, end - begin + 1);

}


sdds::CovidCollection::CovidCollection(const char* filename)
{
	
	std::ifstream fin(filename);
	if (!fin)
	{
		throw "file not open!";
	}
	else
	{
		std::string line;
		Covid covid;
		std::stringstream ss;
		
		char country[26], city[26], variant[26], year[6], cases[6], deaths[6];
		while(fin)
		{
			std::getline(fin, line, '\n');
			if (line != "")
			{
				ss.str(line);
				ss.get(country, 26, '\n');
				ss.get(city, 26, '\n');
				ss.get(variant, 26, '\n');
				ss.get(year, 6, '\n');
				ss.get(cases, 6, '\n');
				ss.get(deaths, 6, '\n');
				covid.m_country = country;
				reduce(covid.m_country);
				covid.m_city = city;
				reduce(covid.m_city);
				covid.m_variant = variant;
				reduce(covid.m_variant);
				covid.m_year = std::stoi(year);
				covid.m_cases = std::stoi(cases);
				covid.m_deaths = std::stoi(deaths);
				m_collection.push_back(covid);
				ss.clear();
			}

		}
	}
}

void sdds::CovidCollection::display(std::ostream& out, const std::string& country) const
{
	int totalDeaths{};
	int totalCases{};
	int countryDeaths{};
	int countryCases{};
	double deathPercent{};
	double casePercent{};
	if (country != "ALL")
		out << "Displaying information of country = " << country << std::endl;
	std::for_each(m_collection.begin(), m_collection.end(), [&](const Covid& theCovid)
	{

				totalDeaths += theCovid.m_deaths;
				totalCases += theCovid.m_cases;
				if (country == "ALL")
				{
					out << theCovid << std::endl;
				}
				else if (theCovid.m_country == country)
				{
					countryDeaths += theCovid.m_deaths;
					countryCases += theCovid.m_cases;
					out << theCovid << std::endl;
				}
				

	});
	
	if (country == "ALL")
	{
		out << "| " << std::right << std::setw(FIELD) << "Total cases around the world: " << std::setw(5) << totalCases << " |\n"
			<< "| " << std::setw(FIELD) << "Total deaths around the world: " << std::setw(5) << totalDeaths << " |\n";
	}
	else
	{
		casePercent = ((countryCases * 1.0) / (totalCases * 1.0))*100.0;
		std::stringstream stream;
		stream << std::fixed << std::setprecision(6) << casePercent;
		std::string casePerStr = stream.str();
		stream.clear();
		stream.str(std::string());
		deathPercent = ((countryDeaths * 1.0) / (totalDeaths * 1.0)) * 100.0;
		stream << std::fixed << std::setprecision(6) << deathPercent;
		std::string deathPerStr = stream.str();
		stream.clear();
		stream.str(std::string());
		std::string totalCasesText = "Total cases in " + country + ": " + std::to_string(countryCases);
		std::string totalDeathsText = "Total deaths in " + country + ": " + std::to_string(countryDeaths);

		std::string percentagesText = country + " has " + casePerStr + "% of global cases and " + deathPerStr + "% of global deaths |";
		out << std::setw(89) << std::setfill('-') << "\n"
			<< "| " << std::setw(COUNTRY_FIELD) << std::setfill(' ') << totalCasesText << " |\n"
			<< "| " << std::setw(COUNTRY_FIELD) << totalDeathsText << " |\n"
			<< "| " << std::setw(PERCENTAGE_FIELD) << percentagesText << std::endl;
	}
}

void sdds::CovidCollection::sort(const std::string& field)
{
	std::string sortBy = field;

	
	if (sortBy == "city")
	{
		std::sort(m_collection.begin(), m_collection.end(), [](Covid a, Covid b)
			{
				if (a.m_city == b.m_city)
				{
					return a.m_deaths < b.m_deaths;
				}
				return a.m_city < b.m_city;
			});
	}
	else if (sortBy == "variant")
	{
		std::sort(m_collection.begin(), m_collection.end(), [](Covid a, Covid b)
			{
				if (a.m_variant == b.m_variant)
				{
					return a.m_deaths < b.m_deaths;
				}
				return a.m_variant < b.m_variant;
			});
	}
	else if(sortBy == "year")
		std::sort(m_collection.begin(), m_collection.end(), [](Covid a, Covid b)
			{
				if (a.m_year == b.m_year)
				{
					return a.m_deaths < b.m_deaths;
				}
				return a.m_year < b.m_year;
			});
	else if (sortBy == "cases")
	{
		std::sort(m_collection.begin(), m_collection.end(), [](Covid a, Covid b)
			{
				if (a.m_cases == b.m_cases)
				{
					return a.m_deaths < b.m_deaths;
				}
				return a.m_cases < b.m_cases;
			});
	}
	else if (sortBy == "deaths")
	{
		std::sort(m_collection.begin(), m_collection.end(), [](Covid a, Covid b)
			{
				
				return a.m_deaths < b.m_deaths;
			});
	}
	else
	{
		std::sort(m_collection.begin(), m_collection.end(), [](Covid a, Covid b)
			{
				if (a.m_country == b.m_country)
				{
					return a.m_deaths < b.m_deaths;
				}
				return a.m_country < b.m_country;
			});
	}

	
}

bool sdds::CovidCollection::inCollection(const std::string& variant, const std::string& country, unsigned int deaths) const
{
	std::vector<Covid>::const_iterator it;
	it = std::find_if(m_collection.begin(), m_collection.end(), [=](Covid a)
			{

				return a.moreDeaths(variant, country, deaths);
			});
	return it != m_collection.end();
}

std::list<sdds::Covid> sdds::CovidCollection::getListForDeaths(unsigned int deaths) const
{
	std::list<Covid> dList;
	std::copy_if(m_collection.begin(), m_collection.end(), std::back_inserter(dList), [=](Covid a)
		{
			return a.m_deaths >= deaths;
		});

	
	return dList;
}

void sdds::CovidCollection::updateStatus()
{
	std::vector<Covid> newCollection = m_collection;
	m_collection.clear();
	std::transform(newCollection.begin(), newCollection.end(), back_inserter(m_collection), [=](Covid a)
		{
			if (a.m_deaths > 300)
			{
				a.m_severity = "EPIDEMIC";
			}
			else if (a.m_deaths < 50)
			{
				a.m_severity = "EARLY";
			}
			else
			{
				a.m_severity = "MILD";
			}
			return a;
		});
}



std::ostream& sdds::operator<<(std::ostream& out, const Covid& theCovid)
{
	int year = theCovid.m_year;
	
	out << "| " << std::setfill(' ') << std::left << std::setw(21) << theCovid.m_country <<
		" | " << std::setw(15) << theCovid.m_city <<
		" | " << std::setw(20) << theCovid.m_variant <<
		" | " << std::right;
	if (year <= 0)
	{
		out <<std::setw(6)<< "";
	}
	else
	{
		out << std::setw(6) << year;
	}
	out << " | " << std::setw(4) << theCovid.m_cases <<
		" | " << std::setw(3) << theCovid.m_deaths << " |"
		<< " | " << std::setw(8) << theCovid.m_severity << " |";

	return out;
}

bool sdds::Covid::moreDeaths(const std::string& variant, const std::string& country, unsigned int deaths) const
{
	if (m_country == country && m_variant == variant)
	{
		return m_deaths > deaths;
	}
	return false;
}
