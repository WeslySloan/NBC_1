#include "AttackBoost.h"
#include "Character.h" // Character 클래스 정의 포함

void AttackBoost::use(Character* character) {
    character->increaseAttack(attackIncrease);
}