#include "Character.h"
#include "Item.h"
#include <algorithm>

Character* Character::instance_ = nullptr;

Character* Character::getInstance(const std::string& name) {
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

void Character::takeDamage(int amount) {
    if (amount < 0) amount = 0;
    hp_ = std::max(0, hp_ - amount);
}

void Character::addItem(std::unique_ptr<Item> item) {
    inventory_.emplace_back(std::move(item));
}

void Character::useItem(int index) {
    if (index < 0 || static_cast<std::size_t>(index) >= inventory_.size()) {
        std::cout << "잘못된 슬롯 번호입니다.\n";
        return;
    }
    inventory_[index]->use(this);
    inventory_.erase(inventory_.begin() + index);
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
    while (level_ < MAX_LEVEL && exp_ >= EXP_TO_LEVEL) {
        exp_ -= EXP_TO_LEVEL;
        levelUp();
    }
}

void Character::levelUp() {
    if (level_ >= MAX_LEVEL) return;
    ++level_;
    maxHp_ += (level_ * 20);
    atk_ += (level_ * 5);
    hp_ = maxHp_;
    std::cout << "[LEVEL UP] " << name_ << " → 레벨 " << level_
        << "!  (MaxHP: " << maxHp_ << ", ATK: " << atk_ << ")\n";
}
