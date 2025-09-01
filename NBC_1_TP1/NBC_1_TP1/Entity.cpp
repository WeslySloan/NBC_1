#include "Entity.h"
#include <iostream>

using namespace std;

Entity::Entity(const string& entityName, int lvl, int hp, int stam, int atk, int def)
    : name(entityName), level(lvl), maxHP(hp), currentHP(hp), stamina(stam), attack(atk), defense(def) {}

Entity::~Entity() {}

void Entity::TakeDamage(int damage) 
{
    int finalDamage = damage - defense;
    if (finalDamage < 0) 
        finalDamage = 0;

    currentHP -= finalDamage;
    if (currentHP < 0) 
        currentHP = 0;

    cout << name << "은(는) " << finalDamage << "의 피해를 입었습니다! (남은 HP: " << currentHP << ")\n";
}

void Entity::Heal(int amount) 
{
    currentHP += amount;
    if (currentHP > maxHP) 
        currentHP = maxHP;

    cout << name << "의 HP가 " << amount << "만큼 회복되었습니다! (현재 HP: " << currentHP << ")\n";
}

void Entity::UseStamina(int amount) 
{
    stamina -= amount;
    if (stamina < 0) 
        stamina = 0;

}

void Entity::RecoverStamina(int amount) 
{
    stamina += amount;
}

void Entity::PrintStatus() const 
{
    cout << "--------------------\n";
    cout << "이름: " << name << "\n";
    cout << "레벨: " << level << "\n";
    cout << "HP: " << currentHP << " / " << maxHP << "\n";
    cout << "스태미나: " << stamina << "\n";
    cout << "공격력: " << attack << "\n";
    cout << "방어력: " << defense << "\n";
    cout << "--------------------\n";
}

string Entity::GetName() const { return name; }
int Entity::GetLevel() const { return level; }
int Entity::GetCurrentHP() const { return currentHP; }
int Entity::GetMaxHP() const { return maxHP; }
int Entity::GetStamina() const { return stamina; }
int Entity::GetAttack() const { return attack; }
int Entity::GetDefense() const { return defense; }