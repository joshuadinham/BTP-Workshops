#include "CheeseParty.h"
#include "Cheese.h"
#include <iostream>

sdds::CheeseParty::~CheeseParty()
{
    if (m_cheeseStack)
    {
        delete[] m_cheeseStack;
        m_cheeseStack = nullptr;
    }

}

sdds::CheeseParty& sdds::CheeseParty::addCheese(const Cheese& cheese)
{
    //check if array has any cheeses
    if (rows == 0)
    {
        //add cheese
        m_cheeseStack = new const Cheese * [++rows];
        m_cheeseStack[0] = &cheese;
    }
    //search array and see if cheese matches any in the cheeseStack
    for (unsigned i = 0; i < rows; i++)
    {
        if (m_cheeseStack[i] == &cheese)
        {
            return *this;
        }
    }
    const Cheese** cheesestack = m_cheeseStack;
    m_cheeseStack = new const Cheese * [rows + 1];
    for (unsigned i = 0; i < rows; i++)
    {
        m_cheeseStack[i] = cheesestack[i];
    }
    m_cheeseStack[rows] = &cheese;
    if (m_cheeseStack) {
        delete[] cheesestack;
        cheesestack = nullptr;
    }
    rows++;
    return *this;
}

sdds::CheeseParty& sdds::CheeseParty::removeCheese()
{
    //make sure rows is greater than 0
    if (rows == 0)
        return *this;
    //search array for cheeses that have 0 weight
    for (unsigned i = 0; i < rows; i++)
    {
        if (m_cheeseStack[i]->getWeight() == 0)
        {
 
            m_cheeseStack[i] = nullptr;
        }
    }
    resize();
    return *this;
}

void sdds::CheeseParty::display(std::ostream& out) const
{
   
    bool empty = true;
    empty = m_cheeseStack == nullptr;
    out << "--------------------------\n";
    if (empty)
    {
        out << "Cheese Party\n" << "--------------------------\n";
        out << "This party is just getting started!\n";
    }
    else if(!empty && rows > 0)
    {
        out << "Cheese Party\n--------------------------\n";
        for (unsigned int i = 0; i < rows; i++)
        {
            if (m_cheeseStack[i] == nullptr)
            {
                
            }
            else
            {
                out << *m_cheeseStack[i]; 
            }

        }
    }
       out << "--------------------------\n";
}

sdds::CheeseParty& sdds::CheeseParty::resize()
{
    unsigned validRows = 0;
    if (rows == 0)
    {
        return *this;
    }
    //count how many rows are not = to nullptr
    for (unsigned i = 0; i < rows; i++)
    {
        if (m_cheeseStack[i] != nullptr)
        {
            validRows++;
        }
    }
    //resize the array
    const Cheese** cheeseStack = m_cheeseStack;
    m_cheeseStack = new const Cheese * [validRows];
    validRows = 0;
    for (unsigned i = 0; i < rows; i++)
    {
        if (cheeseStack[i] != nullptr)
            m_cheeseStack[validRows++] = cheeseStack[i];
    }
    if (cheeseStack)
    {
        delete[] cheeseStack;
        cheeseStack = nullptr;
    }
    rows = validRows;
    return *this;
}

std::ostream& sdds::operator<<(std::ostream& out, const CheeseParty& cheese)
{
    cheese.display(out);
    return out;
}
