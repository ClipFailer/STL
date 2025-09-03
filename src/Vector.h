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
	Vector(const Vector& other);
	Vector(Vector&& rhs);

	Vector<T>& operator=(const Vector& rhs);
	Vector<T>& operator=(Vector&& rhs);
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
	void Clear();
	void ShrinkToFit();
	bool IsEmpty() const;
	void ClearAndShrink();
	void ChangeGrowthFactor(const float newGrowthFactor);

	T& Get(const size_t index) const;

	size_t Size() const;

private:
	void Reserve(const size_t newCapacity);

	T* m_data;
	size_t m_size;
	size_t m_capacity;
	float m_growthFactor = 2;
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
		m_data[i] = T{};
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
Vector<T>::Vector(const Vector &other)
{
	m_size = other.m_size;
	m_data = new T[m_size];

	for(size_t i = 0; i < m_size; ++i)
		m_data[i] = other.m_data[i];

	m_capacity = other.m_capacity;
}

template <typename T>
Vector<T>::Vector(Vector &&rhs) : m_data(rhs.m_data),
								  m_size(rhs.m_size),
								  m_capacity(rhs.m_capacity)
{
	rhs.m_data = nullptr;
	rhs.m_size = 0;
	rhs.m_capacity = 0;
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector &rhs)
{
	delete[] m_data;

	m_size = rhs.m_size;
	m_data = new T[m_size];

	for(size_t i = 0; i < m_size; ++i)
		m_data[i] = rhs.m_data[i];

	m_capacity = rhs.m_capacity;

	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector &&rhs)
{
	delete[] m_data;
	m_size = rhs.m_size;
	m_capacity = rhs.m_capacity;

	m_data = rhs.m_data;

	rhs.m_data = nullptr;
	rhs.m_size = 0;
	rhs.m_capacity = 0;

	return *this;
}

template <typename T>
T &Vector<T>::operator[](const size_t index)
{
    return m_data[index];
}

template <typename T>
void Vector<T>::Insert(const T &newItem, const int index)
{
	if (m_size + 1 > m_capacity)
		Reserve(m_capacity == 0 ? 4 : m_capacity * m_growthFactor);

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
	if (m_size > 0)
		RemoveAt(m_size - 1);
}

template <typename T>
void Vector<T>::RemoveFront()
{
	RemoveAt(0);
}

template <typename T>
void Vector<T>::Clear()
{
	for (size_t i = 0; i < m_size; ++i)
		m_data[i].~T();

	m_size = 0;
}

template <typename T>
void Vector<T>::ShrinkToFit()
{
	if (m_capacity == m_size) return;

	m_capacity = m_size;
	Reserve(m_capacity);
}

template <typename T>
bool Vector<T>::IsEmpty() const
{
	return m_size == 0;
}

template <typename T>
void Vector<T>::ClearAndShrink()
{
	Clear();
	ShrinkToFit();
}

template <typename T>
void Vector<T>::ChangeGrowthFactor(const float newGrowthFactor)
{
	if (newGrowthFactor < 1.f || newGrowthFactor > 4.f) 
		throw std::invalid_argument("Growth must be between 1.0 and 4.0");

	m_growthFactor = newGrowthFactor;
}

template <typename T>
T &Vector<T>::Get(const size_t index) const
{
	if (index > m_size - 1 || index < 0) throw std::out_of_range("Vector: index out of range");

	return m_data[index];
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
	m_capacity = newCapacity;
}
