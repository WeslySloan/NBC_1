#include "Enemy.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

Enemy::Enemy(const string& name, int lvl, int hp, int stam, int atk, int def, int money, int exp)
    : Entity(name, lvl, hp, stam, atk, def), mob_name(name), drop_money(money), drop_exp(exp) {}

void Enemy::Act(Entity* target)
{
    if (GetHP() <= 0)
        return;

    // 0 또는 1을 무작위로 선택 (0: 공격, 1: 이동)
    // std::rand() 함수는 main.cpp의 srand() 함수와 함께 사용
    int actionChoice = std::rand() % 2;

    // 적과 플레이어의 거리 계산
    int deltaX = std::abs(GetPosX() - target->GetPosX());
    int deltaY = std::abs(GetPosY() - target->GetPosY());

    // 공격 로직
    if (actionChoice == 0)
    {
        // 공격 범위 확인 (대각선 포함 1칸 이내)
        if (deltaX <= 1 && deltaY <= 1 && (deltaX > 0 || deltaY > 0))
        {
            cout << GetName() << "이(가) " << target->GetName() << "을(를) 공격합니다!\n";
            target->TakeDamage(GetATK());
        }
        else
        {
            cout << GetName() << "이(가) 공격하려 했지만, " << target->GetName() << "이(가) 공격 범위 밖에 있습니다.\n";
        }
    }
    // 이동 로직
    else if (actionChoice == 1)
    {
        cout << GetName() << "이(가) " << target->GetName() << "에게 다가갑니다.\n";

        // 플레이어에게 가장 가까운 방향으로 한 칸 이동
        int newX = GetPosX();
        int newY = GetPosY();

        if (newX < target->GetPosX()) newX++;
        else if (newX > target->GetPosX()) newX--;

        if (newY < target->GetPosY()) newY++;
        else if (newY > target->GetPosY()) newY--;

        setPosX(newX);
        setPosY(newY);
    }
}

string Enemy::GetMob_Name() const { return mob_name; }
int Enemy::GetDrop_money() const { return drop_money; }
int Enemy::GetDrop_exp() const { return drop_exp; }