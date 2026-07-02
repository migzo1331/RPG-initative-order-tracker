#include "string.hpp"
#include <fstream>
#include <cstring>
#include <stdexcept>
String::String(): text('\0'){}
String::String(const char* text_oth) : text(text_oth, strlen(text_oth)+1) {}
String::String(const char* text_oth, size_t size): text(text_oth,size)
{
    text.push_back('\0');
}
String::String(const char element): text(element)
{
}
size_t String::length() const {
    return this->text.get_size() - 1;
}
int String::find(const char* target) const {
    int target_len = strlen(target);
    if (target_len== 0) return 0;
    if (target_len > this->length()) return -1;
    for (int i = 0; i <= this->length() - target_len; i++) {
        int j = 0;
        for (; j < target_len; j++) {
            if (target[j] != text[i + j]) {
                break;
            }
        }
        if (j == target_len) {
            return i;
        }
    }
    return -1;
}
String String::substring(size_t start)const
{
    return substring(start, this->length());
}
String String::substring(size_t start, size_t end)const
{
    return String(&text[start], end - start);
}
String String::extract(const char* delim)
{
    int delim_index = find(delim);
    if (delim_index == -1)
        throw std::exception("Delim not found");
    String result = substring(0, delim_index);
    size_t remainder_start = delim_index + strlen(delim);
    String remainder = substring(remainder_start);
    *this = remainder;
    return result;
}

const char* String::c_str() const {
    return &text[0];
}
const char* String::c_str(size_t start)
{
    return &text[start];
};

char& String::operator[](size_t index) {
    return text[index];
}
const char& String::operator[](size_t index) const {
    return text[index];
}

bool String::operator==(const char* other) const 
{
    return std::strcmp(this->c_str(), other)==0;
}
bool String::operator<(const char* other) const
{
    return std::strcmp(this->c_str(), other) == -1;
};
bool String::operator>(const char* other) const
{
    return std::strcmp(this->c_str(), other) == 1;
};
bool operator==(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}
bool operator>(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str())>0;
}
bool operator<(const String& lhs, const String& rhs)
{
    return std::strcmp(lhs.c_str(), rhs.c_str())<0;
}

String& String::operator+=(const String& other) {
    this->text.pop_back();
    for (unsigned i = 0; i <=other.length(); i++) {
        this->text.push_back(other[i]);
    }
    return *this;
};
void String::clear()
{
    while (text.get_size() > 0)
    {
        text.pop_back();
    }
};

std::istream& getline(std::istream& is, String& str, char delim )
{
    str.clear();
    char c;
    while (is.get(c)) {
        if (c == delim) {
            break; 
        }
        str.text.push_back(c);
    }
    str.text.push_back('\0');
    return is;
}
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.c_str();
    return os;
}
