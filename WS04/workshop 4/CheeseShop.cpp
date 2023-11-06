
#include "CheeseShop.h"
#include "Cheese.h"
sdds::CheeseShop& sdds::CheeseShop::operator=(const CheeseShop& Shop)
{
    if (this != &Shop)
    {
        for (unsigned i = 0; i < rows; i++)
            if (m_cheeseStock[i])
            {
                delete m_cheeseStock[i];
                m_cheeseStock[i] = nullptr;
            }
        if (m_cheeseStock)
        {
            delete[] m_cheeseStock;
            m_cheeseStock = nullptr;
        }
        rows = Shop.rows;
        m_name = Shop.m_name;
        if (Shop.m_cheeseStock != nullptr)
        {
            m_cheeseStock = new const Cheese * [rows];
            for (unsigned i = 0; i < rows; i++)
            {
                if (Shop.m_cheeseStock[i] != nullptr)
                    m_cheeseStock[i] = new Cheese(*Shop.m_cheeseStock[i]);
            }
        }
    }
    return *this;
}
sdds::CheeseShop::~CheeseShop()
{
        
        if (m_cheeseStock)
        {
            for (unsigned i = 0; i < rows; i++)
            {
                if (m_cheeseStock[i])
                {
                    delete m_cheeseStock[i];
                    m_cheeseStock[i] = nullptr;
                }
            }
            delete[] m_cheeseStock;
            m_cheeseStock = nullptr;
        }
    
}
sdds::CheeseShop& sdds::CheeseShop::operator=(CheeseShop&& shop)
{
   
        if (this != &shop)
        {
            for (unsigned i = 0; i < rows; i++)
                if (m_cheeseStock[i])
                {
                    delete m_cheeseStock[i];
                    m_cheeseStock[i] = nullptr;
                }
            if (m_cheeseStock)
            {
                delete[] m_cheeseStock;
                m_cheeseStock = nullptr;
            }
            rows = shop.rows;
            m_cheeseStock = shop.m_cheeseStock;
            m_name = shop.m_name;
            shop.m_cheeseStock = nullptr;
        }
        return *this;

}
sdds::CheeseShop& sdds::CheeseShop::addCheese(const Cheese& cheese)
{
    if (m_cheeseStock == nullptr)
    {
        rows++;
        m_cheeseStock = new const sdds::Cheese * [rows];
        m_cheeseStock[0] = new Cheese(cheese);
        return *this;
    }

    const sdds::Cheese** cheeseStock = m_cheeseStock;
    m_cheeseStock = new const sdds::Cheese * [rows+1];
    for (unsigned i = 0; i < rows; i++)
    {
        m_cheeseStock[i] = new Cheese(*cheeseStock[i]);
    }
    m_cheeseStock[rows] = new Cheese(cheese);
    for (unsigned i = 0; i < rows; i++)
    {

        if (cheeseStock[i])
        {
            delete cheeseStock[i];
            cheeseStock[i] = nullptr;
        }
    }
    if (cheeseStock)
    {
        delete[] cheeseStock;
        cheeseStock = nullptr;
    }
    rows++;
    return *this;
}

void sdds::CheeseShop::display(std::ostream& out) const
{
    bool empty = true;
    empty = m_cheeseStock == nullptr;
    out << "--------------------------\n";
    if (empty && rows > 0)
    {
        out << std::endl;
        out << "--------------------------\n";
        out << "This shop is out of cheese!\n";
    }
    else if (empty && rows == 0)
    {
        out << "Cheese Magic\n--------------------------\nThis shop is out of cheese!\n";
    }
    else if (!empty && rows > 0)
    {
        out << "Cheese Magic\n--------------------------\n";
        for (unsigned int i = 0; i < rows; i++)
        {
            if (m_cheeseStock[i] == nullptr)
            {

            }
            else
            {
                out << *m_cheeseStock[i];
            }

        }
    }
    out << "--------------------------\n";
}

std::ostream& sdds::operator<<(std::ostream& out, const sdds::CheeseShop& shop)
{
    shop.display(out);
    return out;
}
