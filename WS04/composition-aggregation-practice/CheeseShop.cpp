#include "CheeseShop.h"
#include "Cheese.h"
sdds::CheeseShop& sdds::CheeseShop::addCheese(const Cheese& cheese)
{
    if (m_cheeseStock == nullptr)
    {
        rows++;
        m_cheeseStock = new const sdds::Cheese * [rows];
        m_cheeseStock[0] = &cheese;
        return *this;
    }

    const sdds::Cheese** cheeseStock = m_cheeseStock;
    m_cheeseStock = new const sdds::Cheese * [rows+1];
    for (unsigned i = 0; i < rows; i++)
    {
        m_cheeseStock[i] = cheeseStock[i];
    }
    m_cheeseStock[rows] = &cheese;
    rows++;
    delete[] cheeseStock;
    return *this;
}

void sdds::CheeseShop::display(std::ostream& out) const
{
    bool empty = true;
    empty = m_cheeseStock == nullptr;
    if (empty)
    {
        out << "This shop is out of cheese!";
    
    }
    out << m_name << std::endl;
    for (unsigned int i = 0; i < rows; i++)
    {
        if (m_cheeseStock[i] != nullptr)
        {

        }
        out << *m_cheeseStock[i] << std::endl;
    }
    
}

std::ostream& sdds::operator<<(std::ostream& out, const sdds::CheeseShop& shop)
{
    shop.display(out);
    return out;
}
