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
		CheeseShop& operator=(const CheeseShop& Shop)
		{
			if (this != &Shop)
			{
				delete[] m_cheeseStock;
				rows = Shop.rows;
				m_cheeseStock = new const Cheese * [rows];
				for (unsigned i = 0; i < rows; i++)
				{
					m_cheeseStock[i] = new Cheese(*Shop.m_cheeseStock[i]);
				}
			}
			return *this;
		};
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
