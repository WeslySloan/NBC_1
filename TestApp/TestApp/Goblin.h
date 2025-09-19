#ifndef TEXTRPG_GOBLIN_H
#define TEXTRPG_GOBLIN_H

#include "Monster.h"

// Goblin: 레벨 기반 랜덤 스탯 생성
class Goblin : public Monster {
public:
    explicit Goblin(int level);
};

#endif