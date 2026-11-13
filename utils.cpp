#include "types.hpp"
#include "utils.hpp"



int random_status(int max){
    return ((rand() % max) + 1);
}

Clan loadclan(const string& arq_name) {
    Clan clan;
    ifstream file_read(arq_name);
    size_t parameter;
    
    file_read >> parameter;
    file_read.ignore();
    
    if (file_read.is_open()) {
        string name, oweapon, dweapon;
        getline(file_read, name);
        clan.name = name; 
        
        while (getline(file_read, name, ';')) {
            getline(file_read, oweapon, ';');
            getline(file_read, dweapon);
            
            // Múltiplo de 5: Warrior
            if (parameter % 5 == 0) {
                clan.warriors.push_back(new Warrior(name, 
                    random_status(200), random_status(100), random_status(20), // Atributos base
                    dweapon, random_status(20), random_status(60),          // Arma de defesa
                    oweapon, random_status(20), random_status(40),          // Arma de ataque
                    random_status(50), random_status(100)                   // Armadura
                ));
                continue;
            }
            // Múltiplo de 3: Muder (Assassino)
            if (parameter % 3 == 0) {
                clan.warriors.push_back(new Muder(name, 
                    random_status(200), random_status(100), random_status(20), // Atributos base
                    dweapon, random_status(20),                          // Arma de defesa
                    oweapon, random_status(20), random_status(40)           // Arma de ataque
                ));
                continue;
            }
            // Par: Knight
            if (parameter % 2 == 0) {
                clan.warriors.push_back(new Knight(name, 
                    random_status(200), random_status(100), random_status(20), // Atributos base
                    dweapon, random_status(10), random_status(20),          // Arma de defesa
                    oweapon, random_status(20), random_status(40),          // Arma de ataque
                    random_status(10), random_status(60)                    // Armadura
                ));
                continue;
            }
            // Ímpar: Spearman
            else {
                clan.warriors.push_back(new Spearman(name, 
                    random_status(200), random_status(100), random_status(20), // Atributos base
                    dweapon, random_status(20), random_status(40),          // Arma de defesa
                    oweapon, random_status(40), random_status(80),          // Arma de ataque
                    random_status(20), random_status(60), random_status(60)    // Armadura e Velocidade
                ));
                continue;
            }
        }
    } else {
        cout << "File was not opened " << endl;
    }
    
    file_read.close();
    return clan;
}