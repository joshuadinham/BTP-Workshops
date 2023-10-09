#pragma once
#ifndef SDDS_CHEESE_H
#define SDDS_CHEESE_H
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
namespace sdds
{

	class Cheese
	{
		std::string m_name{"NaC"};
		int m_weight{};
		double m_price{};
		std::string m_features{" "};

	public:
		Cheese() {};
		Cheese(const std::string& str);
		 Cheese slice(size_t weight);
		 Cheese& operator-(const int weight);
		 Cheese& operator=(const Cheese& cheese);
		 Cheese& operator=(size_t weight);
		std::string getName() const { return m_name; }
		int getWeight() const { return m_weight; }
		double getPrice() const { return m_price; }
		std::string getFeatures() const { return m_features; }
		bool isEmpty()
		{
			bool flag = true;
			flag = m_name == "NaC" || m_weight == 0 || m_price == 0.0 || m_features == " ";
			return flag;
		}


	};
	std::ostream& operator<<(std::ostream& out, const Cheese& cheese);

}

#endif // !SDDS_CHEESE_H


