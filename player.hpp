#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class OffensiveWeapon{
    private:
        string name;
        double exdamage;
        double resistence;
    public:
        OffensiveWeapon(){}
        OffensiveWeapon(string name, double exdamage=1, double resistence=2){
            this->name = name;
            this->exdamage = exdamage;
            this->resistence = resistence;
        }
        //getters
        string getname(){
            return name;
        }
        double getexdamage(){
            return exdamage;
        }
        double getresistence(){
            return resistence;
        }

        //actions
        void deterioration(double deterioration_up){
            resistence -= deterioration_up;
            if(resistence < 0){
                resistence = 0;
            }
        }
        bool status(){
            if(resistence == 0){
                return false;
            }
            return true;
        }
};

class DefenseWeapon{
    private:
        string name;
        double exdefense;
        double resistence;
    public:
        DefenseWeapon(){}
        DefenseWeapon(string name, double exdefense=2, double resistence=4){
            this->name = name;
            this->exdefense = exdefense;
            this->resistence = resistence;
        }
        //getters
        string getname(){
            return name;
        }
        double getexdefense(){
            return exdefense;
        }
        double getresistence(){
            return resistence;
        }

        //actions
        void deterioration(double deterioration_up){
            resistence -= deterioration_up;
            if(resistence < 0){
                resistence = 0;
            }
        }
        bool status(){
            if(resistence == 0){
                return false;
            }
            return true;
        }
};


class Character{
    protected:
        string name;
        double life;
        double damage;
        double resistance;
        OffensiveWeapon aweapon;
        DefenseWeapon dweapon;
    public:
        Character(string name="\0", double life=100, double damage=10, double resistance=5, string name_dweapon="\0", double exdefense=2, double dweaponresistence=4, string name_oweapon="\0", double exdamage=1, double oweaponresistence=2) : 
        aweapon(name_oweapon, exdamage, oweaponresistence), dweapon(name_dweapon, exdefense, dweaponresistence) {  //Se eu nao fizer assim o programa cracha por causa do jeito que o C++ le isso em tempo de alocacao
            this->name = name;
            this->life = life;
            this->damage = damage;
            this->resistance = resistance;
        };

        // getters
        string getname(){
            return name;
        }
        double getlife(){
            return life;
        }
        double getdamage(){
            return damage;
        }
        double getresistance(){
            return resistance;
        }
        OffensiveWeapon getoweapon(){
            return aweapon;
        }
        DefenseWeapon getdweapon(){
            return dweapon;
        }
        
        // setters
        void setlife(double newlife){
            life += newlife;
            if(life < 0){
                life = 0;
            }
        }
        void setdamage(double newdamage){
            damage = newdamage;
        }
        void setresistance(double newresistance){
            resistance = newresistance;
        }

        // actions
        bool hero_critical(){ //critical-hit starts here - Por causa da mudanca de estrutura achei melhor por aqui.
            if(name.find("(H)") != string::npos){
                size_t prob = rand() % 2;
                if(prob == 0) return true;
                }
            return false;
        }
        bool state(){
            if(life > 0){
                return true;
            }
            return false;
        }
        virtual double defense(double damage_sustained){
            double actual_damage = damage_sustained - resistance ;
            if(actual_damage > 0){
                return actual_damage;
            }
            return 0;
        }
        virtual double attack(Character& target){
            double actual_damage = target.defense(damage);
            target.setlife(actual_damage);
            return actual_damage;
        }

        virtual ~Character(){};



};

class Knight : public Character{
    private:
        double armor;
        double armor_resistence;
    public:
        Knight(string name="\0", double life=100, double damage=10, double resistance=5, string name_dweapon="\0", double exdefense=2, double dweaponresistence=4, string name_oweapon="\0", double exdamage=1, double oweaponresistence=2, double armor=2, double armor_resistence = 10)  : 
            Character(name, life, damage, resistance, name_dweapon, exdefense, dweaponresistence, name_oweapon, exdamage, oweaponresistence) , armor(armor), armor_resistence(armor_resistence)
        {};

        bool status_armor(){
            if(armor_resistence > 0) return true;
            return false;
        }

        // actions
        bool defesenve_stance(){
            size_t prob = rand() % 3;
            if(prob == 1) return true;
            return false;
        }
        double defense(double damage_sustained) override {
            double actual_damage = damage_sustained;
            if(dweapon.status()){
                if(defesenve_stance()){actual_damage -= (2 * dweapon.getexdefense());}
                else{actual_damage -= dweapon.getexdefense();}
                dweapon.deterioration(dweapon.getexdefense());
            }
            if(actual_damage > 0 && armor_resistence > 0){
                actual_damage -= armor;
                armor_resistence -= armor;
            }
            if(actual_damage > 0){
                actual_damage -= resistance;
                if(actual_damage > 0) return actual_damage;
            }
            return 0;
        }
        double attack(Character& target) override {
            double actual_damage = damage;
            if(defesenve_stance()){actual_damage /= 2;}
            if(hero_critical()){actual_damage *= 1.5;}
            if(aweapon.status()){
                actual_damage += aweapon.getexdamage();
                aweapon.deterioration(aweapon.getexdamage());
            }
            actual_damage = target.defense(actual_damage);
            target.setlife(-actual_damage);
            return actual_damage;
        }

};


class Muder : public Character{
    public:
        Muder(string name="\0", double life=100, double damage=10, double resistance=5, string name_dweapon="\0", double dweaponresistence=4, string name_oweapon="\0", double exdamage=1, double oweaponresistence=2)  : 
            Character(name, life, damage, resistance, name_dweapon, (exdamage/2), dweaponresistence, name_oweapon, exdamage, oweaponresistence)
        {};

        // actions
        bool stealthy_posture(){
            size_t prob = rand() % 2;
            if(prob == 0) return true;
            return false;
        }
        double defense(double damage_sustained) override {
            double actual_damage = damage_sustained;
            if(dweapon.status()){
                actual_damage -= dweapon.getexdefense();
                dweapon.deterioration(dweapon.getexdefense());
            }
            if(actual_damage > 0){
                actual_damage -= resistance;
                size_t chance_of_dodging = 1;
                if(stealthy_posture()) chance_of_dodging = rand() % 2;
                if(actual_damage > 0 && chance_of_dodging != 0){
                    return actual_damage;
                }
            }
            return 0;
        }
        double attack(Character& target) override {
            double actual_damage = damage;
            if(stealthy_posture()){actual_damage *= 2;}
            if(hero_critical()){actual_damage *= 1.5;}
            if(aweapon.status()){
                actual_damage += aweapon.getexdamage();
                aweapon.deterioration(aweapon.getexdamage());
            }
            actual_damage = target.defense(actual_damage);
            target.setlife(-actual_damage);
            return actual_damage;
        }

};

class Spearman : public Character{
    private:
        double armor;
        double armor_resistence;
        int speed;
    public:
        Spearman(string name="\0", double life=100, double damage=10, double resistance=5, string name_dweapon="\0", double exdefense=2, double dweaponresistence=4, string name_oweapon="\0", double exdamage=1, double oweaponresistence=2, double armor=2, double armor_resistence = 10, int speed=1)  : 
            Character(name, life, damage, resistance, name_dweapon, exdefense, dweaponresistence, name_oweapon, exdamage, oweaponresistence) , armor(armor), armor_resistence(armor_resistence), speed(speed)
        {};

        bool status_armor(){
            if(armor_resistence > 0) return true;
            return false;
        }

        // actions
        bool provision(){
            if(speed > 1) return true;
            return false;
        }
        bool impulse(){
            size_t prob = rand() % 100;
            if(prob < 30) return true;
            return false;
        }
        double defense(double damage_sustained) override {
            double actual_damage = damage_sustained;
            if(dweapon.status()){
                actual_damage -= dweapon.getexdefense();
                dweapon.deterioration(dweapon.getexdefense());
            }
            if(actual_damage > 0 && armor_resistence > 0){
                actual_damage -= armor;
                armor_resistence -= armor;
            }
            if(actual_damage > 0){
                actual_damage -= resistance;
                if(actual_damage > 0) return actual_damage;
            }
            return 0;
        }
        double attack(Character& target) override {
            double actual_damage = damage;
            if(aweapon.status()){
                actual_damage += aweapon.getexdamage();
                aweapon.deterioration(aweapon.getexdamage());
            }
            if(provision()){
                if(impulse()){
                    actual_damage *= speed;
                    speed--;
                }
            }
            if(hero_critical()){actual_damage *= 1.5;}
            actual_damage = target.defense(actual_damage);
            target.setlife(-actual_damage);
            return actual_damage;
        }

};


class Warrior : public Character{
    private:
        double life_to_berserker;
        double armor;
        double armor_resistence;
    public:
        Warrior(string name="\0", double life=100, double damage=10, double resistance=5, string name_dweapon="\0", double exdefense=2, double dweaponresistence=4, string name_oweapon="\0", double exdamage=1, double oweaponresistence=2, double armor=2, double armor_resistence = 10)  : 
            Character(name, life, damage, resistance, name_dweapon, exdefense, dweaponresistence, name_oweapon, exdamage, oweaponresistence),  life_to_berserker(life/2), armor(armor), armor_resistence(armor_resistence)
        {};

        bool status_armor(){
            if(armor_resistence > 0) return true;
            return false;
        }

        // actions
        bool berserker(){
            if(life < life_to_berserker) return true;
            return false;
        }
        double defense(double damage_sustained) override {
            double actual_damage = damage_sustained;
            if(!berserker()){
                if(dweapon.status()){
                    actual_damage -= dweapon.getexdefense();
                    dweapon.deterioration(dweapon.getexdefense());
                }
                if(actual_damage > 0 && armor_resistence > 0){
                    actual_damage -= armor;
                    armor_resistence -= armor;
                }
            }
            if(actual_damage > 0){
                actual_damage -= resistance;
                if(actual_damage > 0) return actual_damage;
            }
            return 0;
        }
        double attack(Character& target) override {
            double actual_damage = damage;
            if(aweapon.status()){
                actual_damage += aweapon.getexdamage();
                aweapon.deterioration(aweapon.getexdamage());
            }
            if(berserker()){
                actual_damage *= 4;
            }
            if(hero_critical()){actual_damage *= 1.5;}
            actual_damage = target.defense(actual_damage);
            target.setlife(-actual_damage);
            return actual_damage;
        }

};

struct Clan {
    string name;
    vector<Character*> warriors;
};

#endif