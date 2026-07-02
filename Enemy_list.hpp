#pragma once
#include "Enemy.hpp"
#include "Vector.hpp"
class Enemy_list
{
private:
    Vector<Enemy> list;


public:
    const Enemy& operator[](int n) const;
    Enemy& operator[](int n);

    void add_element(const Enemy& enemy);

    void sort_list_alphabetically(int start, int end);
    void sort_list_alphabetically();
    void sort_list_initiative_order(int start, int end);
    void sort_list_initiative_order();

    void index_enemies(int start, int end);
    void index_enemies();

    void print_list();

};


