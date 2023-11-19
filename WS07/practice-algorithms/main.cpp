#include <iostream>
#include <string>
#include "CovidCollection.h"
int main()
{
	std::string filename = "covids.txt";
	std::string name = "test";
	sdds::CovidCollection covid(filename, name);
	covid.display(std::cout);
	std::string us = "Canada";
	covid.display(std::cout, us);
	covid.sort();

	covid.sort("DEFAULT");

	covid.sort("year");
	covid.sort("variant");
	std::string sort = "variant";
	std::string variant = "Omicron";
	unsigned int deaths = 300;
	
	covid.display(std::cout, us);
	std::cout << "More than 400 deaths" << std::endl;
	for (const auto& item : covid.getListForDeaths(400))
		std::cout << item << "\n";
	std::cout << "More than 500 deaths" << std::endl;
	for (const auto& item : covid.getListForDeaths(500))
		std::cout << item << "\n";
	std::cout << std::endl;
	covid.inCollection(variant, us, deaths);
	covid.updateStatus();
	covid.display(std::cout);
}