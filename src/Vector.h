#pragma once

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector
{
public:
	Vector();
	~Vector();
	Vector(const size_t count);
	Vector(const size_t count, const T &value);

	T& operator[](const size_t index);

	friend std::ostream& operator<<(std::ostream &os, const Vector<T> &vec) 
	{
		os << "[";

		for (size_t i = 0; i < vec.m_size; ++i)
		{
			os << vec.m_data[i];
			if (i + 1 < vec.m_size) os << ", ";
		}
		os << "]\n";
		return os;
	}

	void Insert(const T &newItem, const int index);
	void AddBack(const T &newItem);
	void AddFront(const T &newItem);
	bool RemoveAt(const int index);
	bool Remove(const T& item);
	void RemoveBack();
	void RemoveFront();

	T& Get(const size_t index) const;

	size_t Size() const;

private:
	void Reserve(const size_t newCapacity);

	T* m_data;
	size_t m_size;
	size_t m_capacity;
	
};

template <typename T>
Vector<T>::Vector() : m_data(nullptr), m_size(0), m_capacity(0)
{

}

template <typename T> 
Vector<T>::~Vector() 
{
	delete[] m_data;
	m_size = 0;
	m_capacity = 0;
}

template <typename T>
Vector<T>::Vector(const size_t count)
{
	m_size = count;
	m_data = new T[count];

	for (size_t i = 0; i < m_size; ++i)
		m_data[i] = 0;
}

template <typename T> 
Vector<T>::Vector(const size_t count, const T &value) : m_size(count), m_capacity(count * 2) 
{
	m_data = new T[m_capacity];

	for (size_t i = 0; i < m_size; ++i)
	{
		m_data[i] = value;
	}
}

template <typename T>
T& Vector<T>::operator[](const size_t index)
{
    return m_data[index];
}

template <typename T>
void Vector<T>::Insert(const T &newItem, const int index)
{
	if (m_size + 1 > m_capacity)
		Reserve(m_capacity == 0 ? 1 : m_capacity * 2);

	for (size_t i = m_size; i > index; --i)
		m_data[i] = m_data[i - 1];

	m_data[index] = newItem;
	++m_size;
}

template <typename T>
void Vector<T>::AddBack(const T &newItem)
{
	Insert(newItem, m_size);
}

template <typename T>
void Vector<T>::AddFront(const T &newItem)
{
	Insert(newItem, 0);
}

template <typename T>
bool Vector<T>::RemoveAt(const int index)
{
	if (index < 0 || index >= m_size) return false;

	for (size_t i = index; i < m_size - 1; ++i)
		m_data[i] = m_data[i + 1];

	--m_size;

	return true;
}

template <typename T>
bool Vector<T>::Remove(const T &item)
{
	for (size_t i = 0; i < m_size; ++i)
	{
		if (m_data[i] == item)
		{
			RemoveAt(i);
			return true;
		}
	}

	return false;
}

template <typename T>
void Vector<T>::RemoveBack()
{
	RemoveAt(m_size);
}

template <typename T>
void Vector<T>::RemoveFront()
{
	RemoveAt(0);
}

template <typename T>
T &Vector<T>::Get(const size_t index) const
{
	if (index > m_size || index < 0) std::out_of_range("Vector: index out of range");
}

template <typename T>
size_t Vector<T>::Size() const
{
	return m_size;
}

template <typename T>
void Vector<T>::Reserve(const size_t newCapacity)
{
	if (newCapacity < m_capacity) return;

	T* newData = new T[newCapacity];

	for (size_t i = 0; i < m_size; ++i) 
		newData[i] = m_data[i];
	
	delete[] m_data;
	m_data = newData;
}
