#pragma once

#include<iostream>
#include<cassert>

template<typename T>
class Vector
{
private:
	size_t m_Size{ 0 };
	size_t m_Capacity{ 0 };
	T* m_Arr{ nullptr };
public:
	class const_Iterator
	{
	public:
		const_Iterator() = default;
		const_Iterator(const T* vector, size_t index) : m_Vector(vector), m_Index(index){}
		const T& operator*() const
		{
			return m_Vector[m_Index];
		}

		const_Iterator operator + (const size_t n)
		{
			return const_Iterator{ this->m_Vector, m_Index + n };
		}

		const_Iterator operator - (const size_t n)
		{
			return const_Iterator{ this->m_Vector, m_Index - n };
		}

		friend const_Iterator operator+(int n, const const_Iterator& it)
		{
			return const_Iterator{ it.m_Vector, it.m_Index + n };
		}

		const_Iterator& operator++()
		{
			++m_Index;
			return *this;
		}

		const_Iterator operator++(int)
		{
			int temp = m_Index++;
			return Iterator{ this->m_Vector, temp };
		}

		const_Iterator& operator--()
		{
			--m_Index;
			return Iterator{ this->m_Vector, m_Index };
		}

		const_Iterator operator--(int)
		{
			int temp = m_Index--;
			return const_Iterator{ this->m_Vector, temp };
		}

		const_Iterator& operator+=(const int i)
		{
			int temp{ i };
			if (temp >= 0)
			while (temp--)
				++m_Index;
			else while (temp++)
				--m_Index;
			return *this;
		}

		const_Iterator& operator-=(const int i)
		{
			//return Vector<T>::Iterator{ this->m_Vector, m_Index };
			return *this += -i;
		}

		bool operator!=(const const_Iterator &other) const
		{
			return m_Index != other.m_Index;
		}

		bool operator==(const const_Iterator &other) const
		{
			return m_Index == other.m_Index;
		}

		bool operator<(const const_Iterator &other) const
		{
			return m_Index < other.m_Index;
		}

		bool operator<=(const const_Iterator &other) const
		{
			return m_Index <= other.m_Index;
		}

		bool operator>(const const_Iterator &other) const
		{
			return m_Index > other.m_Index;
		}

		bool operator>=(const const_Iterator &other) const
		{
			return m_Index >= other.m_Index;
		}

	private:
		const T* m_Vector{ nullptr };
		size_t m_Index{ 0 };
	};


class Iterator
{
public:
	Iterator() = default;
	Iterator(T* vector, size_t index) : m_Vector(vector), m_Index(index){}
	 T& operator*() const
	{
		return m_Vector[m_Index];
	}

	Iterator operator + (const size_t n)
	{
		return Iterator{ this->m_Vector, m_Index + n };
	}

	Iterator operator - (const size_t n)
	{
		return Iterator{ this->m_Vector, m_Index - n };
	}

	friend Iterator operator+(int n, const Iterator& it)
	{
		return Iterator{ it.m_Vector, it.m_Index + n };
	}

	Iterator& operator++()
	{
		++m_Index;
		return *this;
	}

	Iterator operator++(int)
	{
		int temp = m_Index++;
		return Iterator{ this->m_Vector, temp };
	}

	Iterator& operator--()
	{
		--m_Index;
		return Iterator{ this->m_Vector, m_Index };
	}

	Iterator operator--(int)
	{
		int temp = m_Index--;
		return Iterator{ this->m_Vector, temp };
	}

	Iterator& operator+=(const int i)
	{
		int temp{ i };
		if (temp >= 0)
		while (temp--)
			++m_Index;
		else while (temp++)
			--m_Index;
		return *this;
	}

	Iterator& operator-=(const int i)
	{
		//return Vector<T>::Iterator{ this->m_Vector, m_Index };
		return *this += -i;
	}

	bool operator!=(const Iterator &other) const
	{
		return m_Index != other.m_Index;
	}

	bool operator==(const Iterator &other) const
	{
		return m_Index == other.m_Index;
	}

	bool operator<(const Iterator &other) const
	{
		return m_Index < other.m_Index;
	}

	bool operator<=(const Iterator &other) const
	{
		return m_Index <= other.m_Index;
	}

	bool operator>(const Iterator &other) const
	{
		return m_Index > other.m_Index;
	}

	bool operator>=(const Iterator &other) const
	{
		return m_Index >= other.m_Index;
	}

private:
	T* m_Vector{ nullptr };
	size_t m_Index{ 0 };
};
public:
	Vector() = default;
	Vector(const size_t capacity) :m_Size{ 0 }, m_Capacity{ capacity }, m_Arr{ new T[m_Capacity] {T()} }{}
	Vector(const Vector& v) : m_Size{ v.m_Size }, m_Capacity{ v.m_Capacity }, m_Arr{ new T[m_Capacity]{T()} }
	{
		for (int i{ 0 }; i < m_Size; ++i)
		{
			m_Arr[i] = v.m_Arr[i];
		}
	}

	Vector& operator=(const Vector& v)
	{
		if (this != &v)
		{
			m_Size = v.m_Size;
			m_Capacity = v.m_Capacity;
			delete[] m_Arr;
			m_Arr = new T[m_Capacity];
			for (int i{ 0 }; i < m_Size; ++i)
			{
				m_Arr[i] = v.m_Arr[i];
			}
		}
		return *this;
	}

	Vector(Vector&& v)
	{
		std::swap(m_Size, v.m_Size);
		std::swap(m_Capacity, v.m_Capacity);
		std::swap(m_Arr, v.m_Arr);
	}

	Vector& operator=(Vector&& v)
	{
		if (this != &v)
		{
			std::swap(m_Size, v.m_Size);
			std::swap(m_Capacity, v.m_Capacity);
			std::swap(m_Arr, v.m_Arr);
		}
		return *this;
	}

	~Vector()
	{
		if (m_Arr)
			delete[] m_Arr;
	}

	size_t size() const
	{
		return m_Size;
	}

	size_t capacity() const
	{
		return m_Capacity;
	}

	void push_back(const T& num)
	{
		try
		{
			if (m_Capacity == 0)
			{
				++m_Capacity;
				m_Arr = new T[m_Capacity]{ T() };
			}
			else if (m_Capacity == m_Size)
			{
				m_Capacity *= 2;
				T* newArr = new T[m_Capacity]{ T() };
				for (size_t i{ 0 }; i < m_Size; ++i)
				{
					newArr[i] = m_Arr[i];
				}
				delete[]m_Arr;
				m_Arr = newArr;
			}
			m_Arr[m_Size++] = num;
		}
		catch (const std::exception& mem)
		{
			std::cout << mem.what() << std::endl;
			throw;
		}
	}

	void pop_back(T& num)
	{
		num = m_Arr[m_Size - 1];
		m_Arr[m_Size - 1] = T();
		m_Size--;
	}


	bool remove(const T& num)
	{
		for (size_t i{ 0 }; i < m_Size; ++i)
		{
			if (m_Arr[i] == num)
			{
				while (i < m_Size - 1)
				{
					m_Arr[i] = m_Arr[i + 1];
					i++;
				}
				m_Size--;
				return true;
			}
		}
		return false;
	}

	T& front() const
	{
		return m_Arr[0];
	}

	T& back() const
	{
		return m_Arr[m_Size - 1];
	}

	//T& operator[](const int i)
	//{
	//  assert(i >= 0 && i < m_Size);
	//  return m_Arr[i];
	//}

	T& operator[](const int i) const
	{
		assert(i >= 0 && i < m_Size);
		return m_Arr[i];
	}

	void printVector(std::ostream& os) const
	{
		for (size_t i{ 0 }; i < m_Size; ++i)
		{
			os << m_Arr[i] << ' ';
		}
		os << std::endl;
	}

	const_Iterator begin() const
	{
		return const_Iterator{ this->m_Arr, 0 };
	}

	Iterator begin()
	{
		return Iterator{ this->m_Arr, 0 };
	}

	const_Iterator end() const
	{
		return const_Iterator{ this->m_Arr, m_Size };
	}
	
	Iterator end()
	{
		return Iterator{ this->m_Arr, m_Size };
	}
};


