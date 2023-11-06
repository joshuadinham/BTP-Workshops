#pragma once
#ifndef SDDS_COLLECTION_H
#define SDDS_COLLECTION_H
#include <string>
#include <iostream>
namespace sdds
{
	template<typename T>
	class Collection
	{
		std::string m_name{};
		T* m_items{};
		size_t m_size{};
		void (*m_func)(const Collection<T>& col, const T& item) {};
	public:
		Collection() {};
		Collection(const std::string& name) { m_name = name; };
		Collection<T> operator=(const Collection<T>& col) = delete;
		Collection(const Collection<T>&) = delete;
		~Collection() 
		{
			if (m_items)
			{
				delete[] m_items;
				m_items = nullptr;
			}
		};
		const std::string name() const
		{
			return m_name;
		}
		size_t size() const
		{
			return m_size;
		}
		void setObserver(void (*observer)(const Collection<T>&, const T&));
		Collection<T>& operator+=(const T& item);
		T& operator[](size_t idx) const;
		T* operator[](const std::string& title) const;
		friend std::ostream& operator<<(std::ostream& out, const Collection<T>& col)
		{
	
			for (size_t i = 0; i < col.m_size; i++)
				out << col.m_items[i] << std::endl;
			return out;
			
		}
		
	};

	

	template<typename T>
	void Collection<T>::setObserver(void (*observer)(const Collection<T>&, const T&))
	{
		m_func = observer;
	}

	template<typename T>
	Collection<T>& Collection<T>::operator+=(const T& item)
	{
		bool exists = false;
		for (size_t i = 0; i < m_size; i++)
		{
			exists = m_items[i].title() == item.title();
			if (exists)
			{
				return *this;
			}
		}
		T* temp = m_items;
		m_items = new T[m_size + 1];
		for (size_t i = 0; i < m_size; i++)
		{
			m_items[i] = temp[i];
		}
		m_items[m_size] = item;
		if (temp)
		{
			delete[] temp;
			temp = nullptr;
		}
		m_size++;
		if (m_func)
		{
			m_func(*this, item);
		}
		return *this;
	}

	template<typename T>
	T& Collection<T>::operator[](size_t idx) const
	{
		if (idx >= m_size)
		{
			throw std::out_of_range("Bad Index [" + std::to_string(idx) + "]. Collection has [" + std::to_string(m_size) + "] items.");
		}
		return m_items[idx];
	}

	template<typename T>
	T* Collection<T>::operator[](const std::string& title) const
	{
		size_t index = 0;
		T* item{};
		if (title == "")
		{
			return item;
		}
		bool exists = false;
		for (size_t i  = 0; i < m_size; i++)
		{
			exists = m_items[i].title() == title;
			if (exists)
			{
				item= &(m_items[index]);
				return item;
			}
			index++;
		}
		if (!exists)
		{
			return item;
		}
		return item;
	}
}
#endif // !SDDS_COLLECTION_H


