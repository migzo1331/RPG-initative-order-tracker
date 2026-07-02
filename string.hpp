#pragma once
#include "vector.hpp"
#include <fstream>
#include <map>
class String
{
private:
	Vector<char> text;
public:
	String();
	String(const char* text_oth);
	String(const char* text_oth, size_t size);
	String(const char symbol);
	size_t length() const;
	int find(const char* arr) const;
	String substring(size_t start)const;
	String substring(size_t start, size_t end)const;
	String extract(const char* delim);
	const char* c_str() const;
	const char* c_str(size_t start);
	char& operator[](size_t index);
	const char& operator[](size_t index) const;
	bool operator==(const char* other) const;
	bool operator<(const char* other) const;
	bool operator>(const char* other) const;

	String& operator+=(const String& other);
	void clear();
	friend std::istream& getline(std::istream& is, String& str, char delim = '\n');
};
std::ostream& operator<<(std::ostream& os, const String& str);
bool operator==(const String& lhs, const String& rhs);
bool operator>(const String& lhs, const String& rhs);
bool operator<(const String& lhs, const String& rhs);