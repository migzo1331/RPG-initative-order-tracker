# RPG Initiative Order Tracker

This program was created as a personal practice project for an Object-Oriented Programming (OOP) course. 

It is a command-line utility designed to easily manage a combat encounter list by generating enemies from pre-determined rules. It follows classical RPG mechanics for health point pools (e.g., `4d6+3`) and initiative bonus, calculating HP and initative for each enemy automatically.

## How It Works

Upon starting the program, the user is asked for an arrangement of enemies (e.g., `3 cat, 4 dog`, `12 wizard`, etc.). 

The program then parses this request and constructs the given amount of enemies for that type. It calculates their stats by rolling their specific HP dice and adding a standard 1d20 roll to their initiative bonus.

## Combat Commands

Once the combat list is generated and sorted by initiative order, the program enters a loop. You can manage the combat encounter using the following commands:

*   **`dmg amount [index]`**: Deals a specific amount of damage to the creature at the provided index.
*   **`heal amount [index]`**: Restores HP to the creature at the provided index.
*   **`list`**: Prints the current initiative order, displaying each creature's index number, initiative score, and current/max HP.
*   **`add`**: allows adding a new enemy mid-combat (*TODO*: additonally it should allow adding a player character with the format **`add Player_name (Initiative) (HP_optional)`**.
*   **`help`**: Displays the list of available commands.
*   **`end`**: Exits the tracker and terminates the program.

## Library Configuration

To recognize the requested creatures, the program reads from a local `library.txt` file. 

Each creature entry in the library must follow a specific formatting rule using standard separators. The format is `[name] (1st sep) [hp_pool] (2nd sep) [initative_bonus]` (1st and 2nd sep are configurable in `const_values.hpp`). 
*   *Example:* `cat - 2d6+1, +7`

## TODOs

1.  **Polymorphism:** Add a `Player` class and rewrite `Enemy_list` into a heterogeneous container to hold both `Enemy` and `Player` objects.
2.  **Memory Management:** Phase out all remaining C-style strings (using `char*` buffers) in the main process and fully replace them with the custom `String` class (That's because the project originally didn't used any `Vector` or `String` class and they got implemented at a later point).
3.  **Refactoring:** Clean up the code and set up a better system for reading user preferences—specifically for parsing `library.txt` and dynamically changing the input separators.
