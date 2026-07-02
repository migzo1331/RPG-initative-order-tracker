#include "Entity.hpp"
#include "Enemy_template.hpp"

Entity::Entity(const String& name_oth, int max_hp_oth, int curr_hp_oth, int initiative_oth): name(name_oth)
{
    if (this->name.length() > max_name_length) { max_name_length = this->name.length(); }
    this->max_hp = max_hp_oth;
    this->curr_hp = curr_hp_oth;
    this->initiative = initiative_oth;

};
Entity::Entity(const String& name_oth, int max_hp_oth, int initiative_oth): name(name_oth)
{
    if (this->name.length() > max_name_length) { max_name_length = this->name.length(); }
    this->max_hp = max_hp_oth;
    this->curr_hp = max_hp_oth;
    this->initiative = initiative_oth;
};

int Entity::get_max_hp() const
{
    return this->max_hp;
};
int Entity::get_curr_hp() const
{
    return this->curr_hp;
};
int Entity::get_initiative() const
{
    return this->initiative;
};

const String& Entity::get_name() const
{
    return this->name;
}
const size_t Entity::get_max_name_length()
{
    return max_name_length;
}

void Entity::set_curr_hp(int n)
{
    if (n > this->max_hp) { this->curr_hp = max_hp; }
    else if (n < 0) { this->curr_hp = 0; }
    else { this->curr_hp = n; }
};
//TODO: remove
void Entity::dmg(int n)
{
    set_curr_hp(this->curr_hp - n);
};
void Entity::heal(int n)
{
    set_curr_hp(this->curr_hp + n);
};

void Entity::print()
{
    
};