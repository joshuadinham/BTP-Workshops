#include "Cheese.h"
#include "CheeseShop.h"
#include "CheeseParty.h"

int main()
{
	 sdds::Cheese gouda("      Buffalo Gouda        , 500  ,2.99,        Sweet   ,      , Creamy");
	 sdds::Cheese feta("Bulgarian Feta       ,800  ,  3.12,      Soft,     Crumbly,   Tangy");
	 sdds::Cheese mozz("   Smoked Mozzarella    ,   2000 ,2.12 ,Low-Moisture,    Semi-Soft,    Smokey  ");
	 sdds::Cheese empty;
	std::cout << gouda;
	sdds::Cheese gouda2 = gouda.slice(499);
	std::cout << gouda;
	std::cout << gouda2;
	sdds::CheeseShop shop("Dairy Store");
	std::cout << shop;
	shop.addCheese(gouda);
	shop.addCheese(mozz);
	shop.addCheese(mozz.slice(100));
	shop.addCheese(feta);
	shop.addCheese(feta.slice(100));
	std::cout << shop;
	std::cout << std::endl;
	shop.addCheese(gouda2);
	shop.addCheese(empty);
	std::cout << shop << std::endl;

	sdds::CheeseParty party;
	sdds::CheeseParty party2;
	sdds::CheeseParty party3;
	std::cout << party;
	party.addCheese(gouda);
	party.addCheese(gouda2);
	party.addCheese(feta);
	party.addCheese(mozz);
	party.addCheese(empty);
	std::cout << "Party 1: \n";
	std::cout << party <<  std::endl;
	std::cout << "Adding cheese to party 2" << std::endl; 
	party2.addCheese(gouda);
	party2.addCheese(mozz);
	std::cout << "Party 2:\n";
	std::cout << party2 << std::endl;
	std::cout << "Copy constructor Party 2 = Party 1\n";
	party2 = party;
	std::cout << "Party 2: \n";
	std::cout << party2 << std::endl;
	std::cout << "Adding cheese to party 2" << std::endl;

	party2.addCheese(gouda);
	party2.addCheese(gouda2.slice(499));
	std::cout << "Party 2: \n";
	std::cout << party2 << std::endl;
	std::cout << "Party 3: \n";
	std::cout << party3 << std::endl;
	std::cout << "Move constructor party 3 = party 2\n";
	party3 = std::move(party2);
	std::cout << "Party 3: \n";
	std::cout << party3 << std::endl;
	std::cout << "Party 2: \n";
	std::cout << party2 << std::endl;
	std::cout << "Party 1: \n";
	std::cout << party;
	std::cout << "Removing empty cheeses from party 1\n";
	party.removeCheese();
	std::cout << "Party 1: \n";
	std::cout << party << std::endl;
	return 0;
}