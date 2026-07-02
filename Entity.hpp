#pragma once
#include "const_values.hpp"
#include "string.hpp"
class Entity 
{
    int max_hp, curr_hp;
    int initiative;
    String name;
    static size_t max_name_length;
public:
    Entity()= default;
    ~Entity() = default;
    Entity(const String& name_oth, int max_hp_oth, int curr_hp_oth, int initiative_oth);
    Entity(const String& name_oth, int max_hp_oth, int initiative_oth);

    int get_max_hp() const;
    int get_curr_hp() const;
    int get_initiative() const;
    const String& get_name() const;
    static const size_t get_max_name_length();
    void set_curr_hp(int n);
    void dmg(int n);
    void heal(int n);

    virtual void print();

};