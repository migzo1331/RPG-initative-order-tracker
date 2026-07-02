#pragma once
#include <stdexcept>
template<typename T>
class Vector
{
	T* list;
	size_t size, capacity;
	void free()
	{
		delete[] list;
	};
	void copy(const Vector& other)
	{
		this->capacity = other.capacity;
		this->size = other.size;
		this->list = new T[this->capacity];
		for (unsigned i = 0; i < this->size; ++i)
		{
			this->list[i] = other.list[i];
		}
	}
	void move(Vector&& other)
	{
		this->capacity = other.capacity;
		this->size = other.size;
		this->list = other.list;
		other.list = nullptr;
	}
	void resize()
	{
		this->capacity *= 2;
		T* temp_list = new T[this->capacity];
		for (unsigned i = 0; i < this->size; ++i)
		{
			temp_list[i] = this->list[i];
		}
		free();
		this->list = temp_list;
	};

public:
	Vector() : size(0), capacity(1)
	{
		this->list = new T[this->capacity];
	}
	Vector(const T& item) : size(1), capacity(1)
	{
		this->list = new T[this->capacity];
		this->list[0] = item;
	}
	Vector(const T* ptr, size_t size) : size(size), capacity(size+1)
	{
		if(ptr==nullptr)
			throw std::out_of_range("Null array(empty) passed, construction failed.");
		this->list = new T[this->capacity];
		for (unsigned i = 0; i < size; i++)
		{
			this->list[i]= ptr[i];
		}
	}
	~Vector()
	{
		free();
	}
	Vector(const Vector& other)
	{
		copy(other);
	}
	Vector operator= (const Vector& other)
	{
		if (this != &other)
		{
			free();
			copy(other);
		}
		return *this;
	}

	Vector(Vector&& other)
	{
		move(std::move(other));
	}
	Vector operator=(Vector&& other) noexcept
	{
		if (this != &other)
		{
			free();
			move(std::move(other));
		}
		return *this;
	}

	void push_back(const T& item)
	{
		if (this->size >= this->capacity)
		{
			resize();
		}
		this->list[this->size++] = item;
	};
	void pop_back()
	{
		if (this->size > 0)
			this->size--;
	}
	void clear()
	{
		free();
		this->capacity = 1;
		this->size = 0;
		this->list = new T[this->capacity];
	};
	int get_size() const 
	{
		return this->size;
	}
	T& operator[](int n)const 
	{
		if (n > this->size-1 || n<0)
			throw std::out_of_range("element out of range");
		return this->list[n];
	}
	T& operator[](int n)
	{
		if (n > this->size-1|| n<0)
			throw std::out_of_range("element out of range");
		return this->list[n];
	}


	T* begin()
	{
		return this->list;
	}
	T* end()
	{
		return this->list + this->size;
	}

	const T* begin() const
	{
		return this->list;
	}
	const T* end() const
	{
		return this->list + this->size;
	}

	
};