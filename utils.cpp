#include "types.hpp"
#include "utils.hpp"


Clan loadclan(const string& arq_name) {
    Clan clan;
    ifstream file_read(arq_name);
    size_t parameter;
    file_read >> parameter;
    file_read.ignore();
    
    if (file_read.is_open()) {
        string name, oweapon, dweapon;
        getline(file_read, name);
        clan.name = name; // Substitui clan.name
        
        while (getline(file_read, name, ';')) {
            getline(file_read, oweapon, ';');
            getline(file_read, dweapon);
            
            // Exemplo de como fica a adição de um guerreiro:
            if (parameter % 5 == 0) {
                clan.warriors.push_back(new Warrior(name, ((rand() % 200) + 1), ((rand() % 100) + 1), ((rand() % 20) + 1), dweapon, ((rand() % 20) + 1), ((rand() % 60) + 1), oweapon, ((rand() % 20) + 1), ((rand() % 40) + 1), ((rand() % 50) + 1), ((rand() % 100) + 1)));
                continue;
            }
            // ... (mantenha os outros if/else com push_back em clan.warriors) ...
        }
    } else {
        cout << "File was not opened " << endl;
    }
    file_read.close();
    return clan;
}


int random_status(int max){
    return ((rand() % max) + 1);
}