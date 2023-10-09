#include "Cheese.h"
std::ostream& sdds::operator<<(std::ostream& out, const Cheese& cheese)
{
	out << "|" << std::left << std::setfill(' ') << std::setw(21) << cheese.getName()
		<< "|" << std::setw(5) << cheese.getWeight() << "|" << std::fixed << std::setprecision(2) << std::setw(5) << cheese.getPrice() << "|" << std::right << std::setw(34) << cheese.getFeatures() << "|";
	return out;
}

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

sdds::Cheese::Cheese(const std::string& str)
{
	std::string cheeseline = str;
	if (cheeseline != "")
	{
		std::string name{};
		std::string sWeight{};
		std::string sPrice{};
		std::string features{};
		//insert string into a stringstream input
		std::stringstream input(cheeseline);
		if (input)
		{
			//extract from input into string variables and erase whitespaces
			std::getline(input, name, ',');
			name = reduce(name);
			std::getline(input, sWeight, ',');
			sWeight = reduce(sWeight);
			std::getline(input, sPrice, ',');
			sPrice = reduce(sPrice);
			//extract the rest of the string until new line
			std::getline(input, features, '\n');

			//remove leading and trailing space from the beginning and end of the token, keeping any commas separating them.
			do
			{
				//removing commas one at a time until there are none to be found
				features.erase(features.find(','));
			} while (features.find(',') != std::string::npos);
			features = reduce(features);
			//insert into instance members;
			m_name = name;
			m_weight = std::stoi(sWeight);
			m_price = std::stod(sPrice);
			m_features = features;

			m_features.append(" ");
		}
	}
	
}

sdds::Cheese sdds::Cheese::slice(size_t weight)
{
	int iWeight = static_cast<int>(weight);
	//check if there is enough cheese to slice
	if (iWeight <= m_weight)
	{
		//return a copy of the current cheese with the desired weight.
		Cheese cheese = *this;
		cheese = iWeight;
		//update the current cheese with the subtracted weight
		*this - iWeight;
		/*if ((*this).getWeight() == 0)
		{
			*this = Cheese();
		}*/
		return cheese;
	}
	else {
	//not enough cheese, return empty state cheese.
		return Cheese();
	}
}

sdds::Cheese& sdds::Cheese::operator-(const int weight)
{
	m_weight -= weight;
	return *this;
}

sdds::Cheese& sdds::Cheese::operator=(const Cheese& cheese)
{
	if (this != &cheese)
	{
		m_name = cheese.m_name;
		m_weight = cheese.m_weight;
		m_price = cheese.m_price;
		m_features = cheese.m_features;
	}
	return *this;
}

sdds::Cheese& sdds::Cheese::operator=(size_t weight)
{
	int iWeight = static_cast<int>(weight);
	m_weight = iWeight;
	return *this;
}


