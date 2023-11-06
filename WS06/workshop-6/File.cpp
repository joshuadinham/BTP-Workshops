#include "File.h"

sdds::File::File(const std::string& name, const std::string& contents)
{
	Resource::m_name = name;
	m_contents = contents;
}

void sdds::File::update_parent_path(const std::string& path)
{
	Resource::m_parent_path = path + m_name;
}

std::string sdds::File::path() const
{
	return Resource::m_parent_path;
}

std::string sdds::File::name() const
{
	return Resource::m_name;
}

size_t sdds::File::size() const
{
	return m_contents.size();
}
