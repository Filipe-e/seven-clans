#include <iostream>
#include <string>

using namespace std;

class OffensiveWeapon{
    private:
        string name;
        double exdamage;
        double resistence;
    public:
        OffensiveWeapon(){}
        OffensiveWeapon(string name, double exdamage, double resistence){
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
        Character(){};
        Character(string name, double life=100, double damage=10, double resistance=5){  
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

        ~Character();



};

class Knight : public Character{
    private:
        double armor;
        double armor_resistence;
    public:
        Knight(){};
        Knight(string name, double life, double damage, double resistance, double armor=2){  
            Character(name, life, damage, resistance);
            this->armor = armor;
        };

        bool status_armor(){
            if(armor_resistence > 0) return true;
            return false;
        }

        // actions
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
                damage += aweapon.getexdamage();
                aweapon.deterioration(aweapon.getexdamage());
            }
            actual_damage = target.defense(actual_damage);
            target.setlife(actual_damage);
            return actual_damage;
        }

};


class Muder : public Character{
    private:
        double armor;
        double armor_resistence;
    public:
        Muder(){};
        Muder(string name, double life, double damage, double resistance, double armor=2){  
            Character(name, life, damage, resistance);
            this->armor = armor;
        };

        bool status_armor(){
            if(armor_resistence > 0) return true;
            return false;
        }

        // actions
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
                damage += aweapon.getexdamage();
                aweapon.deterioration(aweapon.getexdamage());
            }
            actual_damage = target.defense(actual_damage);
            target.setlife(actual_damage);
            return actual_damage;
        }

};

class Mage : public Character{
    private:
        double manna;
    public:
        Mage(){};
        Mage(string name, double life, double damage, double resistance, double manna=2){  
            Character(name, life, damage, resistance);
            this->manna = manna;
        };

        bool status_manna(){
            if(manna > 0) return true;
            return false;
        }

        // actions
        double defense(double damage_sustained) override {
            double actual_damage = damage_sustained;
            if(dweapon.status()){
                actual_damage -= dweapon.getexdefense();
                dweapon.deterioration(dweapon.getexdefense());
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
                damage += aweapon.getexdamage();
                aweapon.deterioration(aweapon.getexdamage());
            }
            actual_damage = target.defense(actual_damage);
            target.setlife(actual_damage);
            return actual_damage;
        }

};

class lancer : public Character{
    private:
        double armor;
        double armor_resistence;
    public:
        lancer(){};
        lancer(string name, double life, double damage, double resistance, double armor=2){  
            Character(name, life, damage, resistance);
            this->armor = armor;
        };

        bool status_armor(){
            if(armor_resistence > 0) return true;
            return false;
        }

        // actions
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
                damage += aweapon.getexdamage();
                aweapon.deterioration(aweapon.getexdamage());
            }
            actual_damage = target.defense(actual_damage);
            target.setlife(actual_damage);
            return actual_damage;
        }

};