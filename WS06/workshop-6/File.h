#pragma once
#ifndef SDDS_FILE_H
#define SDDS_FILE_H
#include <string>
#include <iostream>
#include "Resource.h"
#include "Flags.h"

namespace sdds
{
	 
	class File : public Resource
	{
		std::string m_contents;
	public:
		File() {};
		File(const std::string& name, const std::string& contents = "");
		void update_parent_path(const std::string&);
		NodeType type() const { return NodeType::FILE; };
		std::string path() const;
		std::string name() const;
		int count() const { return -1; };
		size_t size() const;

	};

}
#endif // !SDDS_FILE_H


