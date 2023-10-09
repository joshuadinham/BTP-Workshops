#pragma once
#include <string>
#include <iostream>
#ifndef SDDS_CHEESESHOP_H
#define SDDS_CHEESESHOP_H
namespace sdds
{
	class Cheese;
	class CheeseShop
	{
		std::string m_name{ "No Name" };
		const Cheese** m_cheeseStock{};
		unsigned rows{ 0 };
	public:
		CheeseShop(const std::string& name = "No Name") : m_name(name) {};
		~CheeseShop();
		CheeseShop& operator=(const CheeseShop& Shop);
		CheeseShop& operator=(CheeseShop&& Shop);
		CheeseShop(const CheeseShop& Shop)
		{
			*this = Shop;
		};
		CheeseShop(CheeseShop&& Shop)
		{
			*this = std::move(Shop);
		};
		CheeseShop& addCheese(const Cheese& cheese);
		void display(std::ostream& out) const;
	};
	std::ostream& operator<<(std::ostream& out, const CheeseShop& shop);

}
#endif
