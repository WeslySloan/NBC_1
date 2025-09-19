#ifndef TEXTRPG_SLIME_H
#define TEXTRPG_SLIME_H

#include "Monster.h"
#include <string>

class Slime : public Monster {
public:
    explicit Slime(int level);

    std::string getName()  const override { return name_; }
    int         getHealth() const override { return health_; }
    int         getAttack() const override { return attack_; }
    void        takeDamage(int damage) override;

private:
    std::string name_{ "Slime" };
    int health_{ 0 };
    int attack_{ 0 };
};

#endif
