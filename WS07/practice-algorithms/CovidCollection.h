#pragma once
#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
namespace sdds
{
	struct Covid
	{
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		int m_year{};
		unsigned m_cases{};
		unsigned m_deaths{};
		std::string m_severity = "General";
		bool moreDeaths(const std::string& variant, const std::string& country, unsigned int deaths) const;
		
	};
	class line : public std::string {};

	class CovidCollection
	{
		
		std::vector<Covid> m_collection;
		
		
	public:
		CovidCollection() = default;
		CovidCollection(const char* filename);
		void display(std::ostream& out, const std::string& country = "ALL") const;
		void sort(const std::string& field = "country");
		bool inCollection(const std::string& variaant, const std::string& country, unsigned int deaths) const;
		std::list<Covid> getListForDeaths(unsigned int deaths) const;
		void updateStatus();
		
		
	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
	
	

}
#endif // !SDDS_COVIDCOLLECTION_H


