#include "Directory.h"
#include <iomanip>
#include <algorithm>
#include <sstream>

std::vector<std::string> trimDirectory(const std::string& str, const std::string& backslash = "/");

sdds::Directory::Directory(const std::string& name)
{
	std::string temp = name;
	if (temp.find('/') == std::string::npos)
		temp += "/";
	Resource::m_name = temp;
}

void sdds::Directory::update_parent_path(const std::string& path)
{
	Resource::m_parent_path = path + m_name;
}

std::string sdds::Directory::path() const
{
	return Directory::m_parent_path;
}

std::string sdds::Directory::name() const
{
	return Directory::m_name;
}

int sdds::Directory::count() const
{
	return m_contents.size();
}

size_t sdds::Directory::size() const
{
	size_t size = 0u;
	if (!m_contents.empty())
	{
		for (Resource* content : m_contents)
		{
			size += content->size();
		}
	}

	return size;
}

sdds::Directory& sdds::Directory::operator+=(Resource* resource)
{
	
	for (Resource* rc : m_contents)
	{
		if (rc->name() == resource->name())
		{
			throw "**Expected exception " + resource->name() + " already exists in the root";
		}

	}
	m_contents.push_back(resource);
	if (resource->type() == NodeType::DIR)
		resource->update_parent_path(path());
	else
		resource->update_parent_path(path());
	return *this;
}

sdds::Resource* sdds::Directory::find(const std::string& name, const std::vector<OpFlags>& flags)
{
	Resource* dir{};
	//std::string temp;
	/*if (name.find("/") != std::string::npos)
	{
		std::vector<std::string> strDir = trimDirectory(name);
		temp = strDir[0];
	}
	else
	{
		temp = name;
	}*/
	bool recursive = false;
	size_t i = 0u;
	if (this->count() == 0)
		return nullptr;
	for (OpFlags flag : flags)
	{
		recursive = flag == OpFlags::RECURSIVE;
		if (recursive)
			break;
	}
	if (recursive)
	{
		for (size_t i = 0u; i < m_contents.size(); i++)
		{
			if (m_contents[i]->type() == NodeType::DIR)
			{
				if (m_contents[i]->name() == name)
					return m_contents[i];

				Directory* d = dynamic_cast<Directory*>(m_contents[i]);
				dir = d->find(name, flags);
				if (dir)
				{
					if (dir->name() == name)
						return dir;

				}
			}
			else
			{
				if (m_contents[i]->name() == name)
					return m_contents[i];
			}
		}
	}
	else
	{
		for (size_t i = 0u; i < m_contents.size(); i++)
		{
			if (m_contents[i]->name() == name)
				return m_contents[i];
		}
	}
	return dir;
}

sdds::Directory::~Directory()
{
	size_t count = m_contents.size();
	for (size_t i = 0; i < count ; i++)
	{
		delete m_contents[i];
		m_contents[i] = nullptr;
		
	}
	m_contents.clear();
}

//deletes a resource from the directory whose name matches the first argument and deallocates the memory for it.
void sdds::Directory::remove(const std::string& name, const std::vector<OpFlags>& flag)
{
	
		
		if (flag.size() == 0  && this->find(name)->type() == NodeType::DIR)
		{
			throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
		}
		else if(!this->find(name, flag))
		{
			throw std::string(name + " does not exist in " + this->name());
		}

		std::vector<std::string> path = trimDirectory((find(name, flag)->path()));
		std::string dir;
		if (path.size() >= 1)
			dir = *----path.end();
		else
			dir = *--path.end();
		Directory* parent{};
		if (dir == "" || dir == "/")
		{
			parent = this;
		}
		else
		{
			parent = dynamic_cast<Directory*>(find(dir, flag));
		}
		if (parent)
		{

			std::vector<Resource*>::iterator search;
			search = parent->m_contents.begin();
			bool found = false;
			for (size_t i = 0; i < parent->count() && !found; i++)
			{

				if (found = parent->m_contents[i]->name() == name)
				{
					delete parent->m_contents[i];
					parent->m_contents.erase(search);
				}
				else
				{
					search++;
				}
			}
		}
		
		


		
}


void sdds::Directory::display(std::ostream& out, const std::vector<FormatFlags>& flag)
{
	std::cout << "Total size: " << size() << " bytes\n";
	std::vector<Resource*>::iterator print = m_contents.begin();
	bool setLong = false;
	for (size_t i = 0; i < flag.size() && !setLong; i++)
	{
		setLong = flag[i] == FormatFlags::LONG;
	}
	bool isDir = false;
	for (print; print != m_contents.end(); print++)
	{
		if ((*print)->type() == NodeType::DIR)
		{
			std::cout << "D | ";
			isDir = true;
		}
		else
		{
			std::cout << "F | ";
			isDir = false;
		}

		std::cout << std::left << std::setfill(' ') << std::setw(15) << (*print)->name() << " | ";
		if (setLong && isDir)
		{
			std::cout << std::right <<std::setw(2)<< (*print)->count() << " | " << std::setw(4) << (*print)->size() << " bytes";
			std::cout << " |" << std::endl;
		}
		else if(setLong && !isDir)
		{
			std::cout << std::setw(2)<< "   | " << std::setw(10) << std::right << std::setw(4) << (*print)->size() << " bytes";
			std::cout << " |" << std::endl;
		}

		

	}


}


