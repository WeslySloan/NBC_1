#ifndef TEXTRPG_GOBLIN_H
#define TEXTRPG_GOBLIN_H

#include "Monster.h"
#include <string>

class Goblin : public Monster {
public:
    explicit Goblin(int level);

    std::string getName()  const override { return name_; }
    int         getHealth() const override { return health_; }
    int         getAttack() const override { return attack_; }
    void        takeDamage(int damage) override;

private:
    std::string name_{ "Goblin" };
    int health_{ 0 };
    int attack_{ 0 };
};

#endif
