#include "Orc.h"
#include <random>
#include <algorithm>

static int randInRange(int a, int b) {
    std::random_device rd; std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(a, b);
    return dist(rng);
}

Orc::Orc(int level) {
    health_ = randInRange(level * 200, level * 300);
    attack_ = randInRange(level * 50, level * 100);
}

void Orc::takeDamage(int damage) {
    if (damage < 0) damage = 0;
    health_ = std::max(0, health_ - damage);
}
