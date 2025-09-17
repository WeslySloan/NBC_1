#include "Character.h"
#include <iostream>
#include "AttackBoost.h"

void AttackBoost::use(Character* character) {
	if (!character) return;
	character->increaseAttack(attackIncrease);
	std::cout << "아이템 사용: " << getName()
		<< " (+" << attackIncrease << " ATK)\n";
}