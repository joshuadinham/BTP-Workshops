#pragma once
#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H
#include "Resource.h"
#include <iostream>
#include <string>
#include <vector>
namespace sdds
{
	class Directory : public Resource
	{
		std::vector<Resource*> m_contents;
	public:
		Directory() = default;
		Directory(const std::string& name);
		void update_parent_path(const std::string&);
		NodeType type() const { return NodeType::DIR; };
		std::string path() const;
		std::string name() const;
		int count() const;
		size_t size() const;
		Directory& operator+=(Resource*);
		Resource* find(const std::string&, const std::vector<OpFlags>& = std::vector<OpFlags>());
		~Directory();
		Directory& operator=(const Directory&) = delete;
		Directory(const Directory&) = delete;
		Directory& operator=(Directory&&) = delete;
		Directory(Directory&&) = delete;
		void remove(const std::string&, const std::vector<OpFlags>& flag = std::vector<OpFlags>());
		void display(std::ostream&, const std::vector<FormatFlags>& flag = std::vector<FormatFlags>());


	};
}
#endif
