#ifndef TEXTRPG_BOSSDRAGON_H
#define TEXTRPG_BOSSDRAGON_H

#include "Monster.h"
#include <string>

// 보스: 고정 스펙 (HP=450, ATK=50)
class BossDragon : public Monster {
public:
    BossDragon();

    std::string getName()  const override { return name_; }
    int         getHealth() const override { return health_; }
    int         getAttack() const override { return attack_; }
    void        takeDamage(int damage) override;

private:
    std::string name_{ "Dragon" };
    int health_{ 450 };
    int attack_{ 50 };
};

#endif
