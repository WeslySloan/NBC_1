#pragma once
#ifndef TEXTRPG_ATTACKBOOST_H
#define TEXTRPG_ATTACKBOOST_H

#include "Item.h"

// [UML] AttackBoost
//  - name: string
//  - attackIncrease: int
class AttackBoost : public Item {
public:
    explicit AttackBoost(int inc = 10)
        : Item("AttackBoost"), attackIncrease(inc) {
    }

    // 캐릭터의 ATK를 attackIncrease만큼 증가
    void use(Character* character) override;

    int attackIncrease; // 증가량(예: 10)
};

#endif