#include "Character.h"
#include <iostream>
#include "HealthPotion.h"

void HealthPotion::use(Character* character) {
    if (!character) return;
    character->heal(healthRestore);
    std::cout << "아이템 사용: " << getName()
        << " (+" << healthRestore << " HP)\n";
}
