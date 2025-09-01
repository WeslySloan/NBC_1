#include "Enemy.h"
#include <iostream>
#include <cstdlib> // rand, srand
#include <ctime>   // time

using namespace std;

// 생성자
Enemy::Enemy(const string& name, int lvl, int hp, int stam, int atk, int def, int money, int exp)
    : Entity(name, lvl, hp, stam, atk, def), mob_name(name), drop_money(money), drop_exp(exp) {}

// AI 행동 함수
void Enemy::Act(Entity* target) 
{
    if (currentHP <= 0) 
        return;

    int actionChoice = rand() % 100;

    if (actionChoice < 70)      /// 완전랜덤 
    {
        cout << mob_name << "이(가) " << target->GetName() << "을(를) 공격합니다!\n";
        target->TakeDamage(attack);
    }
    else 
    {
        if (currentHP < maxHP / 2) 
        {
            cout << mob_name << "이(가) 회복 요술을 시전합니다!\n";
            Heal(attack);
        }
        else 
        {
            cout << mob_name << "이(가) " << target->GetName() << "을(를) 공격합니다!\n";
            target->TakeDamage(attack);
        }
    }
}

// 고유 속성 getter 함수
string Enemy::GetMob_Name() const { return mob_name; }
int Enemy::GetDrop_money() const { return drop_money; }
int Enemy::GetDrop_exp() const { return drop_exp; }