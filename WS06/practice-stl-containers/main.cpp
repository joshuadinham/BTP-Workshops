#include <iostream>
#include "Resource.h"
#include "Flags.h"
#include "File.h"
#include "Directory.h"
#include "Filesystem.h"

std::string& reduce(std::string& str, const std::string& whitespace = " \t\v\r\n");
std::vector<std::string> trimDirectory(const std::string& str, const std::string& backslash = "/");


int main(int argc, char* argv[])
{
	std::vector<sdds::FormatFlags> fflags;
	fflags.push_back(sdds::FormatFlags::LONG);
	sdds::Directory* root = new sdds::Directory("root");
	sdds::Resource* fileSystem[7]{};
	
	sdds::Directory* etc = new sdds::Directory("etc");

	sdds::Directory* bin = new sdds::Directory("bin");
	sdds::Directory* src = new sdds::Directory("src");
	fileSystem[0] = new sdds::File("graphics.txt");
	fileSystem[1] = new sdds::File("image.txt");
	fileSystem[2] = new sdds::File("hero.txt");
	fileSystem[3] = new sdds::File("villain.txt");
	fileSystem[4] = new sdds::File("source.txt");
	fileSystem[5] = new sdds::File("sample.txt");
	fileSystem[6] = new sdds::File("sample.txt");

	try
	{
		*root += etc;
		*root += bin;
		*root += fileSystem[5];
		*etc += fileSystem[0];
		*etc += fileSystem[1];
		*bin += fileSystem[2];
		*bin += fileSystem[3];
		*bin += src;
		*src += fileSystem[4];
		*src += fileSystem[6];
		*src += fileSystem[5];
	}
	catch (const std::string& msg)
	{
		std::cerr << msg;
	}
	std::vector<sdds::OpFlags> flags;
	std::vector<std::string> dir;
	flags.push_back(sdds::OpFlags::RECURSIVE);
	root->find("hero.txt", flags);

	std::string str = "    images/cat.jpg    ";
	std::string str2 = "   Listne to me for I am here.    ";
	std::cout << str2 << "\n reducing \n";
	str2 = reduce(str2);
	std::cout << str2 << "\n";

	
	dir = trimDirectory("documents/docs/letters.pdf");
	for (std::string str : dir)
		std::cout << str << "/";
	std::cout << std::endl;
	sdds::Filesystem unix("filesystem.txt");
	try
	{

		std::cout << unix.get_current_directory()->path() << std::endl;
		root = unix.change_directory("images");
		std::cout << unix.get_current_directory()->path() << std::endl;
		std::cout << root->path() << std::endl;
		root = unix.change_directory("pngs");
		std::cout << unix.get_current_directory()->path() << std::endl;
		std::cout << root->path() << std::endl;
		root = unix.change_directory("docs");
		std::cout << unix.get_current_directory()->path() << std::endl;
		std::cout << root->path() << std::endl;
		root = unix.change_directory(".letter.pdf");
		std::cout << unix.get_current_directory()->path() << std::endl;
		std::cout << root->path() << std::endl;
		root = unix.change_directory("simon");
		std::cout << unix.get_current_directory()->path() << std::endl;
		std::cout << root->path() << std::endl;
		root = unix.change_directory("images");
		std::cout << unix.get_current_directory()->path() << std::endl;
		std::cout << root->path() << std::endl;
		unix.change_directory();
		
		

	}
	catch  (std::invalid_argument arg)
	{
		std::cerr << arg.what();
	}
	catch (const char* msg)
	{
		std::cout << msg << std::endl;
	}
	catch (const std::string& msg)
	{
		std::cout << msg << std::endl;
	}
	

	try
	{
		unix.change_directory();
		unix += etc;
		unix += bin;
		unix += fileSystem[5];
		std::cout << unix.get_current_directory()->path() << std::endl;
		root = unix.change_directory("etc/");
		std::cout << root->path() << std::endl;
		std::cout << unix.get_current_directory()->path() << std::endl;
		root = unix.change_directory("bin/");
		std::cout << root->path() << std::endl;
		root = unix.change_directory();
		std::cout << root->path() << std::endl;
		
		unix.get_current_directory()->display(std::cout, fflags);
		unix.get_current_directory()->remove("src/", flags);
		unix.get_current_directory()->display(std::cout, fflags);

		//unix.get_current_directory()->remove("/", flags);
		//std::cout << unix.change_directory("src")->name() << std::endl;
		unix.get_current_directory()->remove("notes.txt");
		

	}
	catch ( std::invalid_argument arg)
	{
		std::cerr << arg.what() << std::endl;
	}
	catch (const std::string& err)
	{
		std::cerr << err << std::endl;
	}
	
	sdds::Directory* classified = new sdds::Directory("classified/");
	*classified += new sdds::File(".aliens.txt", "Are aliens real? Go to Area 51 and find out!");
	*classified += new sdds::File(".polls.txt", "Polling results for the current election are in here.");
	
	try
	{
		unix.change_directory("documents/");
		unix += classified;
		unix.change_directory("images/");
		unix.get_current_directory()->display(std::cout, fflags);
		unix.change_directory("documents/");
		unix.get_current_directory()->display(std::cout, fflags);
		unix.change_directory();
		unix.get_current_directory()->display(std::cout, fflags);
		unix.get_current_directory()->remove("documents/", flags);
		unix.get_current_directory()->display(std::cout, fflags);
	}
	catch (const std::invalid_argument& arg)
	{
		std::cerr << arg.what() << std::endl;
	}
	catch (const std::string& err)
	{
		std::cerr << err << std::endl;
	}


	//for (int i = 0; i < 7; i++)

	//{
	//	delete fileSystem[i];
	//}
	
	return 0;
}