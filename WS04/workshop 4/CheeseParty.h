#pragma once
#ifndef SDDS_CHEESEPARTY_H
#define SDDS_CHEESEPARTY_H
#include <iostream>
namespace sdds
{
	class Cheese;
	class CheeseParty
	{
		const Cheese** m_cheeseStack{};
		unsigned int rows{};
		CheeseParty& resize();
	public:
		CheeseParty() = default;
		~CheeseParty();
		CheeseParty& addCheese(const Cheese& cheese);
		CheeseParty& removeCheese();
		CheeseParty& operator=(const CheeseParty& party)
		{
			if (this != &party)
			{
				if (m_cheeseStack)
				{
					delete[] m_cheeseStack;
					m_cheeseStack = nullptr;
				}
				rows = party.rows;
				m_cheeseStack = new const Cheese * [rows];
				for (unsigned i = 0; i < rows; i++)
				{
					m_cheeseStack[i] = party.m_cheeseStack[i];
				}
			}
			return *this;
		};
		CheeseParty& operator=(CheeseParty&& party) noexcept
		{
			if (this != &party)
			{
				if (m_cheeseStack)
				{
					delete[] m_cheeseStack;
					m_cheeseStack = nullptr;
				}
				rows = party.rows;
				m_cheeseStack = party.m_cheeseStack;
				party.m_cheeseStack = nullptr;
			}
			return *this;
		};
		CheeseParty(const CheeseParty& party)
		{
			*this = party;
		};
		CheeseParty(CheeseParty&& party) noexcept
		{
			*this = std::move(party);
		};
		void display(std::ostream& out) const;
	};
	std::ostream& operator<<(std::ostream& out, const CheeseParty& cheese);
}
#endif // !SDDS_CHEESEPARTY


