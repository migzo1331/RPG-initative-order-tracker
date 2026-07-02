#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include "string.hpp"
#include "const_values.hpp"


bool is_digit(char symbol);
int roll_dice(int sides);

class Creature
{
private:
    String name;
    int amount;

public:
    Creature();
    Creature(const int new_amount, const char* new_name);

    const String get_name() const;
    const int get_amount() const; 
};