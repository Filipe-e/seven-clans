#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>
#include <vector>

// Declaramos que a classe Character existe, 
// para o compilador não reclamar do ponteiro Character*
class Character; 

struct Clan {
    std::string name;
    std::vector<Character*> warriors;
};

#endif