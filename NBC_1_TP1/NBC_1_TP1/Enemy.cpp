#include "Enemy.h"
#include "C_Move.hpp"
#include "C_Guard.hpp"
#include "C_Attack.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

void Enemy::AddCard(Card* newCard) {
    cards.push_back(newCard);
}

Enemy::~Enemy() {
    for (Card* card : cards) {
        delete card;
    }
    cards.clear();
}

void Enemy::Act(Entity* target)
{
    if (GetHP() <= 0)
        return;

    if (cards.empty()) {
        std::cout << GetName() << "은(는) 사용할 카드가 없습니다.\n";
        return;
    }

    int cardIndex = std::rand() % cards.size();
    Card* selectedCard = cards[cardIndex];

    C_Move* moveCard = dynamic_cast<C_Move*>(selectedCard);
    if (moveCard) {
        std::cout << GetName() << "이(가) '" << moveCard->C_GetName() << "' 카드를 사용합니다!\n";

        int newX = GetPosX();
        int newY = GetPosY();

        if (newX < target->GetPosX()) newX++;
        else if (newX > target->GetPosX()) newX--;

        if (newY < target->GetPosY()) newY++;
        else if (newY > target->GetPosY()) newY--;

        setPosX(newX);
        setPosY(newY);
        return;
    }

    C_Attack* attackCard = dynamic_cast<C_Attack*>(selectedCard);
    if (attackCard) {
        std::cout << GetName() << "이(가) '" << attackCard->C_GetName() << "' 카드를 사용합니다!\n";
        int deltaX = std::abs(GetPosX() - target->GetPosX());
        int deltaY = std::abs(GetPosY() - target->GetPosY());

        // 공격 범위 확인 (자신이 있는 칸 포함)
        if (deltaX <= 1 && deltaY <= 1) {
            target->TakeDamage(attackCard->A_GetATK());
        }
        else {
            std::cout << "하지만 " << target->GetName() << "이(가) 공격 범위 밖에 있습니다.\n";
        }
        return;
    }

    C_Guard* guardCard = dynamic_cast<C_Guard*>(selectedCard);
    if (guardCard) {
        std::cout << GetName() << "이(가) '" << guardCard->C_GetName() << "' 카드를 사용합니다! 방어 태세를 취합니다.\n";
        Heal(guardCard->G_GetDEF());
        return;
    }
    std::cout << GetName() << "은(는) 알 수 없는 카드를 사용했습니다.\n";
}