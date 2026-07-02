#include "Enemy.hpp"
#include "Vector.hpp"
#include "Enemy_list.hpp"
#include <iomanip> // Required for setw and setfill

const Enemy& Enemy_list::operator[](int n) const
{
    return this->list[n];
};
Enemy& Enemy_list::operator[](int n) 
{
    return this->list[n];
};


void Enemy_list::add_element(const Enemy& enemy)
{
    this->list.push_back(enemy);
};

void Enemy_list::sort_list_alphabetically(int start, int end)
{
    for (unsigned i = start; i < end - 1; i++)
    {
        for (unsigned j = i + 1; j < end; j++)
        {
            if (this->list[i].get_name() == this->list[j].get_name())
            {
                if (this->list[i].get_initiative() < this->list[j].get_initiative())
                {
                    std::swap(this->list[i], this->list[j]);
                }
            }
            else if (this->list[i].get_name()> this->list[j].get_name())
            {
                std::swap(this->list[i], this->list[j]);
            }

        }
    }
};
void Enemy_list::sort_list_alphabetically()
{
    this->sort_list_alphabetically(0, this->list.get_size());
}
void Enemy_list::sort_list_initiative_order(int start, int end)
{
    for (unsigned i = start; i < end - 1; i++)
    {
        for (unsigned j = i + 1; j < end; j++)
        {
            if (this->list[i].get_initiative() < this->list[j].get_initiative())
            {
                Enemy temporary = this->list[i];
                this->list[i] = this->list[j];
                this->list[j] = temporary;
            }
            else if (this->list[i].get_initiative() == this->list[j].get_initiative())
            {
                if (this->list[i].get_name() ==this->list[j].get_name())
                {
                    Enemy temporary = this->list[i];
                    this->list[i] = this->list[j];
                    this->list[j] = temporary;
                }
            }

        }
    }
}
void Enemy_list::sort_list_initiative_order()
{
    sort_list_initiative_order(0, this->list.get_size());
}
void Enemy_list::index_enemies(int start, int end)
{
    int counter = 1;
    sort_list_alphabetically(start, end);
    this->list[start].set_creature_number(counter);
    for (unsigned i = start+1; i < end; i++)
    {
        if (this->list[i].get_name() == this->list[i-1].get_name())
        {
            this->list[i].set_creature_number(++counter);
        }
        else
        {
            counter = 1;
            this->list[i].set_creature_number(counter);
        }
    }
}
void Enemy_list::index_enemies()
{
    index_enemies(0, this->list.get_size());
}

void Enemy_list::print_list() {
    std::cout << "list of the enemies: \n";
    for (Enemy enemy: list)
    {
        enemy.print();
    }
};