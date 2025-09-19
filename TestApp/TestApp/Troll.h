#ifndef TEXTRPG_TROLL_H
#define TEXTRPG_TROLL_H

#include "Monster.h"
#include <string>

class Troll : public Monster {
public:
    explicit Troll(int level);

    std::string getName()  const override { return name_; }
    int         getHealth() const override { return health_; }
    int         getAttack() const override { return attack_; }
    void        takeDamage(int damage) override;

private:
    std::string name_{ "Troll" };
    int health_{ 0 };
    int attack_{ 0 };
};

#endif
