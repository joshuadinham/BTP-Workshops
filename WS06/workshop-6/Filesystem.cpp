#include "Filesystem.h"
#include "File.h"
#include "Directory.h"
#include <fstream>
#include <sstream>
#include <vector>

std::string& reduce(std::string& str, const std::string& whitespace = " \t\v\r\n")
{
	std::size_t start = str.find_first_not_of(whitespace);
	std::size_t end = str.find_last_not_of(whitespace);

	str = str.substr(start, end - start + 1);
	return str;
}

//receives a string representing the directory path and returns a vector containing the names of all directories and files in the path
std::vector<std::string> trimDirectory(const std::string& str, const std::string& backslash = "/")
{
	
	std::string tempStr = str;
	std::vector <std::string> dir;
	std::string temp2;
	
	std::stringstream ss(str);
	
	do
	{
	
			std::getline(ss, temp2, '/');
			if (temp2.find(".") == std::string::npos)
				temp2 += "/";
			dir.push_back(temp2);
			if (ss.peek() == std::char_traits<char>::eof())
			{
				ss.setstate(std::ios::failbit);
			}
	} while (ss);

	return dir;
}

sdds::Filesystem::Filesystem(const std::string& fileName, const std::string& root)
{
	std::ifstream fin(fileName);
	if (!fin)
	{
		throw "**EXCEPTION: Filesystem not created with invalid filename.\n";
	}
	if (fin)
	{
		 
		m_root = new Directory("/");
		m_current = m_root;

		std::stringstream ss;
		std::string line;
		std::string file;
		std::string directory;
		std::string contents;
		size_t count = 0u;
		std::vector<OpFlags> flags;
		std::vector<std::string> dir;
		flags.push_back(OpFlags::RECURSIVE);

		do
		{
			
			if (std::getline(fin, line, '\n'))
				count++;
			
		} while (fin);

		fin.clear();
		fin.seekg(std::ios::beg);

		for (size_t i = 0u; i < count; i++)
		{
			//read the line from the file, and insert into string stream
			std::getline(fin, line, '\n');
			ss.str(line);

			//if this line of the file has "|" then it is a File Resource
			if (line.find('|') != std::string::npos)
			{
				//extract the File's directory leading to the file name, extract the contents of the file, remove leading and trailing spaces
				std::getline(ss, file, '|');
				std::getline(ss, contents, '\n');
				file = reduce(file);
				contents = reduce(contents);

				//convert the directory path string into a list of names
				dir = trimDirectory(file);

				//loop through the list of names
				for (std::string str : dir)
				{
					//if the current directory does not have this name in it then check if its a file or a directory.
					//If it is a file, simply add it to the directory and proceed
					//If it is a directory add the directory to the current directory and set the current directory to the newly added directory and proceed
					
					if (!m_current->find(str))
					{

						if (str.find('.') == std::string::npos)
						{

							*m_current += new Directory(str);
							change_directory(str);
						}
						else
						{
							*m_current += new File(str, contents);
						}

					}
					//if the current directory does have this name in it then set the current directory to that name and proceed
					else
					{
							change_directory(str);

					}
				}
			}
			//This line of the file is a directory only
			else
			{
				//extract the line from the stringstream and remove leading and trailing spaces
				std::getline(ss, directory, '\n');
				directory = reduce(directory);

				//convert the directory path string to a list of directory names
				dir = trimDirectory(directory);
				for (std::string str : dir)
				{
					//if the current directory does not contain this name add it to the directory and change the current directory to it, else, just change the current directory to it
					if (!m_current->find(str))
					{
						
						*m_current += new Directory(str);
						change_directory(str);


					}
					else
					{
						change_directory(str);
					}
				}
			}
			//clear the string stream and change the directory back to root at the end of each extraction from the file
			ss.clear();
			change_directory();
		}

	}
}

sdds::Filesystem::~Filesystem()
{
	delete m_root;
}

sdds::Filesystem& sdds::Filesystem::operator=(Filesystem&& fs)
{
	if (this != &fs)
	{
		delete m_root;
		m_root = fs.m_root;
		m_current = fs.m_current;
	}
	return *this;
}

sdds::Filesystem::Filesystem(Filesystem&& fs)
{
	*this = std::move(fs);
}

sdds::Filesystem& sdds::Filesystem::operator+=(Resource* rc)
{
	*m_current += rc;
	return *this;
}

sdds::Directory* sdds::Filesystem::change_directory(const std::string& dir)
{
	if (dir == "")
	{
		m_current = m_root;
	}
	else
	{
		std::vector<OpFlags> flags;
		flags.push_back(OpFlags::RECURSIVE);
		m_current = dynamic_cast<Directory*>( m_root->find(dir, flags));
		if (!m_current)
		{
			m_current = m_root;
			throw std::invalid_argument("Cannot change directory! " + dir + " not found!");
		}
	}
	return m_current;
}

sdds::Directory* sdds::Filesystem::get_current_directory() const
{
	return m_current;
}
