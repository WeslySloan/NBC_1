#include "BossDragon.h"
#include <algorithm>

BossDragon::BossDragon() {
    // health_/attack_은 멤버 초기값(450, 50) 그대로 사용
}

void BossDragon::takeDamage(int damage) {
    if (damage < 0) damage = 0;
    health_ = std::max(0, health_ - damage);
}
