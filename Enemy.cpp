#define _CRT_SECURE_NO_WARNINGS
#include "Enemy.hpp"
#include <iomanip>

Enemy::Enemy(): Entity(), creature_number(-1){};
Enemy::Enemy(const Enemy_template& template_enemy): 
    Entity(template_enemy.get_name(), roll(template_enemy.get_hp_pool()), roll_dice(20) + template_enemy.add_initiative_bonus())
{
    this->creature_number = -1;
    std::cout << "hp: " << this->get_max_hp() << " initiative: " << this->get_initiative() << " name: " << this->get_name() << '\n';
    std::cout << "enemy created!\n";
};

int Enemy::get_creature_number() const
{
    return this->creature_number;
};
void Enemy::set_creature_number(int n)
{
    this->creature_number= n;
}
int Enemy::roll(const char dice[10])
{
    int amount = 0, bonus = 0;
    int sides = 0;
    int result = 0;

    unsigned i = 0;
    //extract amount
    for (; dice[i] != 'd'; ++i)
    {
        if (dice[i] == '\0')
        {
            std::cerr << "Hp dice pool entered incorrectly (missing d seperator)";
            throw(std::bad_exception());
        }
        amount *= 10;
        amount += dice[i] - '0';
    }
    amount = amount == 0 ? 1 : amount;
    i++;
    //extract sides
    for (; dice[i] != '+' && dice[i] != '\0'; ++i) {
        sides *= 10;
        sides += dice[i] - '0';
    }
    i += dice[i] != '\0' ? 1 : 0;

    //extract bonus (if any)
    for (; dice[i] != '\0'; ++i) {
        bonus *= 10;
        bonus += dice[i] - '0';
    }

    //roll S times of K sided dice and return the result + B (SdK+B)
    for (unsigned j = 0; j < amount; ++j)
    {
        result += roll_dice(sides);
    }
    return result + bonus;
}

void Enemy::print()
{
    std::cout << std::left << std::setfill(' ');
    std::cout << std::setw(get_max_name_length()) << get_name();

    std::cout << " #";
    std::cout << std::setw(2) << this->creature_number;

    std::cout << std::right;
    std::cout << " (" << get_initiative() / 10 << get_initiative() % 10;
    std::cout << "), hp:" << get_curr_hp() << '/' << get_max_hp() << '\n';

}