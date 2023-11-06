#pragma once
#ifndef SDDS_FILESYSTEM_H
#define SDDS_FILESYSTEM_H
#include <iostream>
#include <string>
namespace sdds
{
	class Resource;
	class File;
	class Directory;
	class Filesystem
	{
		Directory* m_root{};
		Directory* m_current{};
	public:
		Filesystem() = default;
		Filesystem(const std::string& fileName, const std::string& root = "");
		~Filesystem();
		Filesystem& operator=(const Filesystem&) = delete;
		Filesystem(const Filesystem&) = delete;
		Filesystem& operator=(Filesystem&&);
		Filesystem(Filesystem&&);
		Filesystem& operator+=(Resource*);
		Directory* change_directory(const std::string& dir = "");
		Directory* get_current_directory() const;

	};
}
#endif // !SDDS_FILESYSTEM_H



