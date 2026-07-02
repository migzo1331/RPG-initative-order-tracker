#include "const_values.hpp"
#include "Creature.hpp"
#include "Enemy.hpp"
#include "Enemy_list.hpp"
#include "Enemy_template.hpp"
#include "Vector.hpp"
#include <functional>
#include <map>

size_t Enemy::max_name_length = 0;



bool seperator_check(char* curr_symbol)
{
    return (*curr_symbol == ',' && is_digit(*(curr_symbol+2)));
}
bool last_creature_end_check(char curr_symbol, int num)
{
    return (curr_symbol == '\0' && num == 1);
}


int count_types(char* text)
{
    int count = 1; 
    for (unsigned i = 0; text[i + 2] != '\0'; ++i)
    {
        if (seperator_check(text+i))
        {
            count++;
        }
    }
    return count;
}
int extract(char* name, char*& text, int num)
{
    unsigned n = 0;
    int counter = 0;
    do
    {
        n = n * 10 + (*text - '0');
        ++text;
    } while (*(text) != ' ');
    text++;

    while (!last_creature_end_check(*(text + counter), num) &&
           !seperator_check(text + counter))
    {
        *(name + counter) = *(text + counter);
        counter++;
    }
    name[counter] = '\0';

    text += (last_creature_end_check(*(text + counter), num)) ? 0:counter + 2 ; //skips ", "
    return n;
}


bool get_input_request(char request_buffer[Max_size])
{
    std::cout << "Enter Request- *amount* *name* (e.g. 3 cat, 4 dog): ";
    std::cin.getline(request_buffer, Max_size, '\n');
    return (is_digit(request_buffer[0]));
} 
bool combat_enemy_set_up(Enemy_list& enemy_combat_list){

    char request_buffer[Max_size];
    char* request_ptr = request_buffer; //use?
    char name[Max_size / 2]; //TODO: make string
    int amount = 0, temp_amount = 0, types= 0;

    Vector <Creature> creature_request_list;
    Vector <Enemy_template> enemy_template_list;

    do {
        if (get_input_request(request_buffer)) { break; };
    } while (true);


    types = count_types(request_buffer);
    std::cout << "types found:" << types << '\n' << '\n';

    for (unsigned i = 0; i < types; ++i)
    {
        creature_request_list.push_back(Creature(extract(name, request_ptr, types - i), name));
        enemy_template_list.push_back(Enemy_template(creature_request_list[i]));
        if (!(enemy_template_list[i].get_name()==creature_request_list[i].get_name()))
        {
            std::cerr << "creature #" << i + 1 << " error: " << creature_request_list[i].get_name() << "\n\n";
            return false;
        }
        amount += creature_request_list[i].get_amount();
    }

    for (unsigned i = 0; i < types; ++i)
    {
        for (unsigned j = 0; j < creature_request_list[i].get_amount(); ++j)
        {
            enemy_combat_list.add_element(Enemy(enemy_template_list[i]));
        };
        std::cout << '\n';
        enemy_combat_list.index_enemies(temp_amount, (temp_amount + creature_request_list[i].get_amount()));
        temp_amount += creature_request_list[i].get_amount();
    }
    return true;
};



int main()
{
    std::map<String, std::function<bool(Enemy_list&, String&)>> command_dispatcher = {

       {"dmg", [](Enemy_list& enemy_combat_list, String& arguments) -> bool {
            int space_idx = arguments.find(" ");
            if (space_idx == -1) {
                std::cout << "Invalid input for dmg, try again\n";
                return true;
            }

            String amount_str = arguments.extract(" ");
            int dmg_amount = atoi(amount_str.c_str());

            if (!dmg_amount) {
                std::cout << "dmg 0 or invalid input, try again\n";
                return true;
            }

            if (arguments.length() > 1 && arguments[0] == '[') {
                int index = arguments[1] - '1';
                enemy_combat_list[index].dmg(dmg_amount);
                std::cout << enemy_combat_list[index].get_name()
                          << " #"<< enemy_combat_list[index].get_creature_number()
                          << " took " << dmg_amount << " damage\n";
            }
            return true;
        }},

        {"heal", [](Enemy_list& enemy_combat_list, String& arguments) -> bool {
            int space_idx = arguments.find(" ");
            if (space_idx == -1) {
                std::cout << "Invalid input for heal, try again\n";
                return true;
            }

            String amount_str = arguments.extract(" ");
            int heal_amount = atoi(amount_str.c_str());

            if (!heal_amount) {
                std::cout << "heal 0 or invalid input, try again\n";
                return true;
            }

            if (arguments.length() > 1 && arguments[0] == '[') {
                int index = arguments[1] - '0';
                enemy_combat_list[index - 1].heal(heal_amount);
                std::cout << enemy_combat_list[index - 1].get_name() << " got healed for "
                          << heal_amount << " damage\n";
            }
            return true;
        }},

        {"add", [](Enemy_list& enemy_combat_list, String& arguments) -> bool {
            // TODO: Use arguments to extract player/enemy details similarly
            // enemy_combat_list.add_element();
            return true;
        }},

        {"list", [](Enemy_list& enemy_combat_list, String& arguments) -> bool {
            enemy_combat_list.print_list();
            return true;
        }},

        {"help", [](Enemy_list& enemy_combat_list, String& arguments) -> bool {
            std::cout << "\n Commands available:\n"
                      << " dmg amount [index]\n"
                      << " heal amount [index]\n"
                      << " add: \n"
                      << "   1. add player Player_Name initiative curr_hp(optional)\n"
                      << "   2. add enemy Enemy_name\n"
                      << " end\n"
                      << " list\n";
            return true;
        }},

        {"end", [](Enemy_list& enemy_combat_list, String& arguments) -> bool {
            return false;
        }}
    };
do
{

    Enemy_list enemy_combat_list;
    String buffer;
    String command;

    do
    {
        if (combat_enemy_set_up(enemy_combat_list))  break;
    } while (true);
   

        enemy_combat_list.sort_list_initiative_order();
        enemy_combat_list.print_list();


    do
    {
        std::cout << "\n>";
        getline(std::cin, buffer); 

        if (buffer.length() == 0) continue;

        int space_index = buffer.find(" ");
        if (space_index != -1) {
            command = buffer.extract(" "); 
        } else {
            command = buffer;
            buffer.clear();
        }

        auto it = command_dispatcher.find(command);

        if (it != command_dispatcher.end()) {
            bool keep_running = it->second(enemy_combat_list, buffer);
            if (!keep_running) {
                return 0; // "end" command returns false and triggers this
            }
        }
        else {
            std::cout << "command not recognised\n";
        }
        std::cin.clear();

    } while (true);

} while (true);
return 0;
}
