#pragma once
#ifndef TEXTRPG_HEALTHPOTION_H
#define TEXTRPG_HEALTHPOTION_H

#include "Item.h"

// [UML] HealthPotion
//  - name: string
//  - healthRestore: int
class HealthPotion : public Item {
public:
    explicit HealthPotion(int restore = 50)
        : Item("HealthPotion"), healthRestore(restore) {
    }

    // 캐릭터의 HP를 healthRestore만큼 회복
    void use(Character* character) override;
    int healthRestore; // 회복량(예: 50)
};

#endif