#ifndef TEXTRPG_ORC_H
#define TEXTRPG_ORC_H

#include "Monster.h"
#include <string>

class Orc : public Monster {
public:
    explicit Orc(int level);

    std::string getName()  const override { return name_; }
    int         getHealth() const override { return health_; }
    int         getAttack() const override { return attack_; }
    void        takeDamage(int damage) override;

private:
    std::string name_{ "Orc" };
    int health_{ 0 };
    int attack_{ 0 };
};

#endif
