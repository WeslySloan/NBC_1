#include "HealthPotion.h"
#include "Character.h" // Character 클래스 정의 포함

void HealthPotion::use(Character* character) {
    character->heal(healthRestore);
}