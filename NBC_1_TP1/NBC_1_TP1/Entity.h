#ifndef ENTITY_H
#define ENTITY_H

#include <string>

using namespace std;

class Entity 
{
protected:
    string name;
    int level;
    int maxHP;
    int currentHP;
    int stamina;
    int attack;
    int defense;

public:
    Entity(const string& entityName, int lvl, int hp, int stam, int atk, int def);
    virtual ~Entity();

    virtual void TakeDamage(int damage);
    void Heal(int amount);
    void UseStamina(int amount);
    void RecoverStamina(int amount);
    void PrintStatus() const;

    string GetName() const;
    int GetLevel() const;
    int GetCurrentHP() const;
    int GetMaxHP() const;
    int GetStamina() const;
    int GetAttack() const;
    int GetDefense() const;
};

#endif