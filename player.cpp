#include "player.hpp"
#include <iostream>

using namespace std;

// --- Implementação: OffensiveWeapon ---
OffensiveWeapon::OffensiveWeapon(string name, double exdamage, double resistence) {
    this->name = name;
    this->exdamage = exdamage;
    this->resistence = resistence;
}

string OffensiveWeapon::getname() { return name; }
double OffensiveWeapon::getexdamage() { return exdamage; }
double OffensiveWeapon::getresistence() { return resistence; }

void OffensiveWeapon::deterioration(double deterioration_up) {
    resistence -= deterioration_up;
    if (resistence < 0) resistence = 0;
}

bool OffensiveWeapon::status() { return resistence > 0; }

// --- Implementação: DefenseWeapon ---
DefenseWeapon::DefenseWeapon(string name, double exdefense, double resistence) {
    this->name = name;
    this->exdefense = exdefense;
    this->resistence = resistence;
}

string DefenseWeapon::getname() { return name; }
double DefenseWeapon::getexdefense() { return exdefense; }
double DefenseWeapon::getresistence() { return resistence; }

void DefenseWeapon::deterioration(double deterioration_up) {
    resistence -= deterioration_up;
    if (resistence < 0) resistence = 0;
}

bool DefenseWeapon::status() { return resistence > 0; }

// --- Implementação: Character ---
Character::Character(string name, double life, double damage, double resistance, 
                     string name_dweapon, double exdefense, double dweaponresistence, 
                     string name_oweapon, double exdamage, double oweaponresistence) 
    : aweapon(name_oweapon, exdamage, oweaponresistence), 
      dweapon(name_dweapon, exdefense, dweaponresistence) 
{
    this->name = name;
    this->life = life;
    this->damage = damage;
    this->resistance = resistance;
}

Character::~Character() {}

string Character::getname() { return name; }
double Character::getlife() { return life; }
double Character::getdamage() { return damage; }
double Character::getresistance() { return resistance; }
OffensiveWeapon Character::getoweapon() { return aweapon; }
DefenseWeapon Character::getdweapon() { return dweapon; }

void Character::setlife(double newlife) {
    life += newlife;
    if (life < 0) life = 0;
}

void Character::setdamage(double newdamage) { damage = newdamage; }
void Character::setresistance(double newresistance) { resistance = newresistance; }

bool Character::hero_critical() {
    if (name.find("(H)") != string::npos) {
        return (rand() % 2) == 0;
    }
    return false;
}

bool Character::state() { return life > 0; }

double Character::defense(double damage_sustained) {
    double actual_damage = damage_sustained - resistance;
    return (actual_damage > 0) ? actual_damage : 0;
}

double Character::attack(Character& target) {
    double actual_damage = target.defense(damage);
    target.setlife(-actual_damage); // Corrigido de target.setlife(actual_damage) baseado na sua logica das classes filhas
    return actual_damage;
}

// --- Implementação: Knight ---
Knight::Knight(string name, double life, double damage, double resistance, 
               string name_dweapon, double exdefense, double dweaponresistence, 
               string name_oweapon, double exdamage, double oweaponresistence, 
               double armor, double armor_resistence) 
    : Character(name, life, damage, resistance, name_dweapon, exdefense, dweaponresistence, name_oweapon, exdamage, oweaponresistence), 
      armor(armor), armor_resistence(armor_resistence) {}

bool Knight::status_armor() { return armor_resistence > 0; }
bool Knight::defesenve_stance() { return (rand() % 3) == 1; }

double Knight::defense(double damage_sustained) {
    double actual_damage = damage_sustained;
    if (dweapon.status()) {
        if (defesenve_stance()) actual_damage -= (2 * dweapon.getexdefense());
        else actual_damage -= dweapon.getexdefense();
        dweapon.deterioration(dweapon.getexdefense());
    }
    if (actual_damage > 0 && armor_resistence > 0) {
        actual_damage -= armor;
        armor_resistence -= armor;
    }
    if (actual_damage > 0) {
        actual_damage -= resistance;
        if (actual_damage > 0) return actual_damage;
    }
    return 0;
}

double Knight::attack(Character& target) {
    double actual_damage = damage;
    if (defesenve_stance()) actual_damage /= 2;
    if (hero_critical()) actual_damage *= 1.5;
    if (aweapon.status()) {
        actual_damage += aweapon.getexdamage();
        aweapon.deterioration(aweapon.getexdamage());
    }
    actual_damage = target.defense(actual_damage);
    target.setlife(-actual_damage);
    return actual_damage;
}

// --- Implementação: Muder ---
Muder::Muder(string name, double life, double damage, double resistance, 
             string name_dweapon, double dweaponresistence, 
             string name_oweapon, double exdamage, double oweaponresistence) 
    : Character(name, life, damage, resistance, name_dweapon, (exdamage / 2), dweaponresistence, name_oweapon, exdamage, oweaponresistence) {}

bool Muder::stealthy_posture() { return (rand() % 2) == 0; }

double Muder::defense(double damage_sustained) {
    double actual_damage = damage_sustained;
    if (dweapon.status()) {
        actual_damage -= dweapon.getexdefense();
        dweapon.deterioration(dweapon.getexdefense());
    }
    if (actual_damage > 0) {
        actual_damage -= resistance;
        size_t chance_of_dodging = 1;
        if (stealthy_posture()) chance_of_dodging = rand() % 2;
        if (actual_damage > 0 && chance_of_dodging != 0) return actual_damage;
    }
    return 0;
}

double Muder::attack(Character& target) {
    double actual_damage = damage;
    if (stealthy_posture()) actual_damage *= 2;
    if (hero_critical()) actual_damage *= 1.5;
    if (aweapon.status()) {
        actual_damage += aweapon.getexdamage();
        aweapon.deterioration(aweapon.getexdamage());
    }
    actual_damage = target.defense(actual_damage);
    target.setlife(-actual_damage);
    return actual_damage;
}

// --- Implementação: Spearman ---
Spearman::Spearman(string name, double life, double damage, double resistance, 
                   string name_dweapon, double exdefense, double dweaponresistence, 
                   string name_oweapon, double exdamage, double oweaponresistence, 
                   double armor, double armor_resistence, int speed) 
    : Character(name, life, damage, resistance, name_dweapon, exdefense, dweaponresistence, name_oweapon, exdamage, oweaponresistence), 
      armor(armor), armor_resistence(armor_resistence), speed(speed) {}

bool Spearman::status_armor() { return armor_resistence > 0; }
bool Spearman::provision() { return speed > 1; }
bool Spearman::impulse() { return (rand() % 100) < 30; }

double Spearman::defense(double damage_sustained) {
    double actual_damage = damage_sustained;
    if (dweapon.status()) {
        actual_damage -= dweapon.getexdefense();
        dweapon.deterioration(dweapon.getexdefense());
    }
    if (actual_damage > 0 && armor_resistence > 0) {
        actual_damage -= armor;
        armor_resistence -= armor;
    }
    if (actual_damage > 0) {
        actual_damage -= resistance;
        if (actual_damage > 0) return actual_damage;
    }
    return 0;
}

double Spearman::attack(Character& target) {
    double actual_damage = damage;
    if (aweapon.status()) {
        actual_damage += aweapon.getexdamage();
        aweapon.deterioration(aweapon.getexdamage());
    }
    if (provision() && impulse()) {
        actual_damage *= speed;
        speed--;
    }
    if (hero_critical()) actual_damage *= 1.5;
    actual_damage = target.defense(actual_damage);
    target.setlife(-actual_damage);
    return actual_damage;
}

// --- Implementação: Warrior ---
Warrior::Warrior(string name, double life, double damage, double resistance, 
                 string name_dweapon, double exdefense, double dweaponresistence, 
                 string name_oweapon, double exdamage, double oweaponresistence, 
                 double armor, double armor_resistence) 
    : Character(name, life, damage, resistance, name_dweapon, exdefense, dweaponresistence, name_oweapon, exdamage, oweaponresistence), 
      life_to_berserker(life / 2), armor(armor), armor_resistence(armor_resistence) {}

bool Warrior::status_armor() { return armor_resistence > 0; }
bool Warrior::berserker() { return life < life_to_berserker; }

double Warrior::defense(double damage_sustained) {
    double actual_damage = damage_sustained;
    if (!berserker()) {
        if (dweapon.status()) {
            actual_damage -= dweapon.getexdefense();
            dweapon.deterioration(dweapon.getexdefense());
        }
        if (actual_damage > 0 && armor_resistence > 0) {
            actual_damage -= armor;
            armor_resistence -= armor;
        }
    }
    if (actual_damage > 0) {
        actual_damage -= resistance;
        if (actual_damage > 0) return actual_damage;
    }
    return 0;
}

double Warrior::attack(Character& target) {
    double actual_damage = damage;
    if (aweapon.status()) {
        actual_damage += aweapon.getexdamage();
        aweapon.deterioration(aweapon.getexdamage());
    }
    if (berserker()) actual_damage *= 4;
    if (hero_critical()) actual_damage *= 1.5;
    actual_damage = target.defense(actual_damage);
    target.setlife(-actual_damage);
    return actual_damage;
}