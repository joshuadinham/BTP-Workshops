
#include <iostream>
#include <fstream>
#include "Book.h"
#include "Collection.h"
#include "SpellChecker.h"
#include "Movie.h"

//template<typename Func>
//auto convert(sdds::Book& book, Func func)
//{
//	return func(book);
//}
void bookAddedObserver(const sdds::Collection<sdds::Book>& theCollection,
	const sdds::Book& theBook)
{
	std::cout << "Book \"" << theBook.title() << "\" added!\n";
}

void movieAddedObserver(const sdds::Collection<sdds::Movie>& theCollection, const sdds::Movie& theMovie)
{
	std::cout << "Movie \"" << theMovie.title() << "\" added\n";
}

int main(int argc, char** argv)
{
	/*double usdToCadRate = 1.3;
	double gbpToCadRate = 1.5;*/
	sdds::SpellChecker check;
	try
	{
		sdds::SpellChecker checker("Ddfdf");
	}
	catch (const char* exception)
	{
		std::cout << "EXCEPTION: " << exception << std::endl;
	}
	try
	{

		check = sdds::SpellChecker(argv[2]);
	}
	catch (const char* exception)
	{
		std::cout << "EXCEPTION: " << exception << std::endl;
	}
	sdds::Book library[7];
	sdds::Movie catalog[7];
	std::ifstream fin(argv[1]);
	unsigned countB = 0;
	if (fin)
	{
		std::string line{};
		do
		{
			std::getline(fin, line, '\n');
			if (line[0] != '#' && line != "")
				library[countB++] = sdds::Book(line);
		} while (fin);
	}
	unsigned countM = 0;
	fin.close();
	fin.open(argv[3]);
	if (fin)
	{
		std::string line{};
		do
		{
			std::getline(fin, line, '\n');
			if (line[0] != '#' && line != "")
				catalog[countM++] = sdds::Movie(line);
 		} while (fin);
	}
	
	sdds::Collection<sdds::Book> col1{};
	sdds::Collection<sdds::Movie> col2("Movie Catalogue");
	for (size_t i = 0; i < countB; i++)
	{
		library[i].fixSpelling(check);
	}
	check.showStatistics(std::cout);

	for (size_t i = 0; i < countM; i++)
		catalog[i].fixSpelling(check);
		

	check.showStatistics(std::cout);
	col1.setObserver(bookAddedObserver);
	col2.setObserver(movieAddedObserver);
	
	for (unsigned i = 0; i < countB; i++)
	{
		col1 += library[i];
	}
	std::cout << col1 << std::endl;
	for (size_t i = 0; i < countM; i++)
		col2 += catalog[i];
	std::cout << col2 << std::endl;

	try
	{
		std::cout << col1 << std::endl;
		std::cout << *col1["The Catcher in teh Rye"] << std::endl;
	}
	catch (const std::out_of_range& message)
	{
		std::cout << message.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "message not found" << std::endl;
	}

	return 0;
}