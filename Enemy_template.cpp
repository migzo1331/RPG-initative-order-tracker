#define _CRT_SECURE_NO_WARNINGS
#include "Enemy_template.hpp"

Enemy_template::Enemy_template(): name()
{
    hp_pool[0] = '\0';
    initiative_bonus[0] = '\0';
}
Enemy_template::Enemy_template(const Creature& request)
{
    std::ifstream library_file(file_name);
    if (!library_file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        throw(std::bad_exception());
    }

    char* ptr;
    String buffer;
    int skip_length =0;

    while (getline(library_file,buffer,'\n'))
    {
        if (buffer[0] == '\0' || buffer[0] == ' ' || buffer[0] == '\r')
        {
            continue;
        }
        else if (buffer.find(name_hp_seperator) == -1)
        {
            std::cerr << buffer << " Error, name_seperator between name and health pool not found: "
                << '\n';
            throw(std::bad_exception());
        }
        else
        {
            this->name=buffer.extract(name_hp_seperator);
            if (this->name == request.get_name())
            {
                std::cout << "Match found for: " << request.get_name() << '\n';

                int stop = buffer.find(hp_initiative_seperator);
                for (signed i = 0; i< stop; i++)
                {
                    this->hp_pool[i] = buffer[i];
                }

                this->hp_pool[stop] = '\0';
                skip_length += stop + strlen(hp_initiative_seperator);

                unsigned i = 0;
                for (; buffer[i + skip_length] != '\0'; i++)
                {
                    this->initiative_bonus[i] = buffer[i + skip_length];
                }
                this->initiative_bonus[i] = '\0';

                break;
            }
        }
    }
    if ( !(this->name==request.get_name()))
    {
        std::cerr << "Not correctly typed name or no such creature exists. Please retry. \n";
    }
    library_file.close();
};
int Enemy_template::add_initiative_bonus() const
{
    int result = 0;
    bool is_positive = true;
    int length = strlen(this->initiative_bonus);
    for (int i = 0; this->initiative_bonus[i] != '\0';++i)
    {
        if (this->initiative_bonus[i] == '-')
        {
            is_positive = false;
        }
        else if (is_digit(this->initiative_bonus[i]))
        {
            result *= 10;
            result += initiative_bonus[i] - '0';
        }
    }
    result *= is_positive ? 1 : -1;
    return result;
};

const char* Enemy_template::get_hp_pool() const { return this->hp_pool; };
const char* Enemy_template::get_initiative_bonus() const { return this->initiative_bonus; };
const String Enemy_template::get_name() const { return this->name; };
