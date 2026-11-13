#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <iostream>
#include <string>

using namespace std;

// DECLARAÇÕES DAS ARMAS
class OffensiveWeapon {
private:
    string name;
    double exdamage;
    double resistence;
public:
    OffensiveWeapon(string name = "\0", double exdamage = 1, double resistence = 2);
    
    string getname();
    double getexdamage();
    double getresistence();
    
    void deterioration(double deterioration_up);
    bool status();
};

class DefenseWeapon {
private:
    string name;
    double exdefense;
    double resistence;
public:
    DefenseWeapon(string name = "\0", double exdefense = 2, double resistence = 4);
    
    string getname();
    double getexdefense();
    double getresistence();
    
    void deterioration(double deterioration_up);
    bool status();
};

// DECLARAÇÃO DO CHARACTER BASE
class Character {
protected:
    string name;
    double life;
    double damage;
    double resistance;
    OffensiveWeapon aweapon;
    DefenseWeapon dweapon;
public:
    Character(string name = "\0", double life = 100, double damage = 10, double resistance = 5, 
              string name_dweapon = "\0", double exdefense = 2, double dweaponresistence = 4, 
              string name_oweapon = "\0", double exdamage = 1, double oweaponresistence = 2);

    virtual ~Character();

    string getname();
    double getlife();
    double getdamage();
    double getresistance();
    OffensiveWeapon getoweapon();
    DefenseWeapon getdweapon();
    
    void setlife(double newlife);
    void setdamage(double newdamage);
    void setresistance(double newresistance);

    bool hero_critical();
    bool state();
    
    virtual double defense(double damage_sustained);
    virtual double attack(Character& target);
};

// DECLARAÇÕES DAS CLASSES FILHAS
class Knight : public Character {
private:
    double armor;
    double armor_resistence;
public:
    Knight(string name = "\0", double life = 100, double damage = 10, double resistance = 5, 
           string name_dweapon = "\0", double exdefense = 2, double dweaponresistence = 4, 
           string name_oweapon = "\0", double exdamage = 1, double oweaponresistence = 2, 
           double armor = 2, double armor_resistence = 10);

    bool status_armor();
    bool defesenve_stance();
    
    double defense(double damage_sustained) override;
    double attack(Character& target) override;
};

class Muder : public Character {
public:
    Muder(string name = "\0", double life = 100, double damage = 10, double resistance = 5, 
          string name_dweapon = "\0", double dweaponresistence = 4, 
          string name_oweapon = "\0", double exdamage = 1, double oweaponresistence = 2);

    bool stealthy_posture();
    
    double defense(double damage_sustained) override;
    double attack(Character& target) override;
};

class Spearman : public Character {
private:
    double armor;
    double armor_resistence;
    int speed;
public:
    Spearman(string name = "\0", double life = 100, double damage = 10, double resistance = 5, 
             string name_dweapon = "\0", double exdefense = 2, double dweaponresistence = 4, 
             string name_oweapon = "\0", double exdamage = 1, double oweaponresistence = 2, 
             double armor = 2, double armor_resistence = 10, int speed = 1);

    bool status_armor();
    bool provision();
    bool impulse();
    
    double defense(double damage_sustained) override;
    double attack(Character& target) override;
};

class Warrior : public Character {
private:
    double life_to_berserker;
    double armor;
    double armor_resistence;
public:
    Warrior(string name = "\0", double life = 100, double damage = 10, double resistance = 5, 
            string name_dweapon = "\0", double exdefense = 2, double dweaponresistence = 4, 
            string name_oweapon = "\0", double exdamage = 1, double oweaponresistence = 2, 
            double armor = 2, double armor_resistence = 10);

    bool status_armor();
    bool berserker();
    
    double defense(double damage_sustained) override;
    double attack(Character& target) override;
};

#endif