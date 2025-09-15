#include "Character.h"
#include "Item.h"
#include <algorithm> // std::min

// 정적 멤버 초기화
Character* Character::instance_ = nullptr;

Character* Character::getInstance(const std::string& name) {
    // 아직 생성된 인스턴스가 없으면 최초 1회만 생성합니다.
    if (!instance_) {
        const std::string finalName = name.empty() ? "MyCharacter" : name;
        instance_ = new Character(finalName);
    }
    return instance_;
}

Character::Character(const std::string& name)
    : name_(name) {
}

void Character::displayStatus() const {
    std::cout << "==============================\n";
    std::cout << "이름      : " << name_ << "\n";
    std::cout << "레벨      : " << level_ << " (EXP " << exp_ << "/" << EXP_TO_LEVEL << ")\n";
    std::cout << "체력      : " << hp_ << "/" << maxHp_ << "\n";
    std::cout << "공격력    : " << atk_ << "\n";
    std::cout << "골드      : " << gold_ << "\n";
    std::cout << "인벤토리  : ";
    if (inventory_.empty()) std::cout << "(비어있음)";
    else {
        for (std::size_t i = 0; i < inventory_.size(); ++i) {
            std::cout << "[" << i << "]" << inventory_[i]->getName();
            if (i + 1 < inventory_.size()) std::cout << ", ";
        }
    }
    std::cout << "\n==============================\n";
}

void Character::levelUp() {
    if (level_ >= MAX_LEVEL) return;
    ++level_;
    // 요구사항: 현재 레벨에 비례해 최대체력/공격력 증가
    maxHp_ += (level_ * 20);
    atk_ += (level_ * 5);
    // 레벨업 시 체력 풀 회복
    hp_ = maxHp_;
    std::cout << "[LEVEL UP] " << name_ << " → 레벨 " << level_
        << "!  (MaxHP: " << maxHp_ << ", ATK: " << atk_ << ")\n";
}

void Character::useItem(int index) {
    if (index < 0 || static_cast<std::size_t>(index) >= inventory_.size()) {
        std::cout << "잘못된 슬롯 번호입니다.\n";
        return;
    }
    // 포인터로 전달(UML 시그니처)
    inventory_[index]->use(this);
    // 사용 후 인벤토리에서 제거(소멸자 호출)
    inventory_.erase(inventory_.begin() + index);
}








bool Character::spendGold(int amount) {
    if (amount <= gold_) { gold_ -= amount; return true; }
    return false;
}

void Character::heal(int amount) {
    hp_ = std::min(maxHp_, hp_ + amount);
}

void Character::increaseAttack(int amount) {
    atk_ += amount;
}

void Character::addItem(std::unique_ptr<Item> item) {
    inventory_.emplace_back(std::move(item));
}



std::vector<std::string> Character::inventoryNames() const {
    std::vector<std::string> names;
    names.reserve(inventory_.size());
    for (const auto& p : inventory_) names.push_back(p->getName());
    return names;
}

void Character::addExperience(int amount) {
    if (level_ >= MAX_LEVEL) return;
    exp_ += amount;
    // 누적이 100을 넘을 수 있으므로 while로 여러 번 레벨업 가능
    while (level_ < MAX_LEVEL && exp_ >= EXP_TO_LEVEL) {
        exp_ -= EXP_TO_LEVEL;
        levelUp();
    }
}


