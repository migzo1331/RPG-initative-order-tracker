#pragma once
#include "Creature.hpp" 
#include "string.hpp"
#include "const_values.hpp"
class Enemy_template
{
    char hp_pool[12] = { '\0' };
    char initiative_bonus[5] = { '\0' };
    String name; 


public:
    Enemy_template();
    Enemy_template(const Creature& request);


    const char* get_hp_pool() const;
    const char* get_initiative_bonus() const;
    const String get_name() const;

    int add_initiative_bonus()const;

};