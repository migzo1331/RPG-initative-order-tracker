#pragma once
#include "Enemy_template.hpp"
#include "Entity.hpp"
#include "String.hpp"
#include "const_values.hpp"
class Enemy : public Entity
{
    int creature_number;

public:
    Enemy();
    Enemy(const Enemy_template& template_enemy);

    int get_creature_number() const;
    void set_creature_number(int n);
    void print() override;
    int roll(const char dice[10]);
};
