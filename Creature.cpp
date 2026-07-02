#include "Creature.hpp"
#pragma warning (disable : 4996)

int roll_dice(int sides)
{
    std::cout << "rolling d" << sides<< ' ';

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::uniform_int_distribution<> distrib(1, sides);
    int n = distrib(gen);
    std::cout <<",rolling result: "<< n << '\n';
    return n;
}
bool is_digit(char symbol)
{
    return symbol >= '0' && symbol <= '9';
}


Creature::Creature() :amount(0), name()
{
};
Creature::Creature(const int amount_oth, const char* name_oth) :
    amount(amount_oth), name(name_oth)
{
}

const String Creature::get_name() const
{
    return name.c_str();
}
const int Creature::get_amount() const
{
    return this->amount;
}
;

