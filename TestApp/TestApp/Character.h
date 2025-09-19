#ifndef TEXTRPG_CHARACTER_H
#define TEXTRPG_CHARACTER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Item;

class Character {
public:
    static constexpr int EXP_TO_LEVEL = 100;
    static constexpr int MAX_LEVEL = 10;

    static Character* getInstance(const std::string& name = "");
    static Character* instance() { return instance_; }

    Character(const Character&) = delete;  // 싱글턴 복사 금지
    Character& operator=(const Character&) = delete;  // (컴파일 타임 차단)

    const std::string& getName() const { return name_; }
    int  getLevel() const { return level_; }
    int  getHP()    const { return hp_; }
    int  getMaxHP() const { return maxHp_; }
    int  getATK()   const { return atk_; }
    int  getEXP()   const { return exp_; }
    int  getGold()  const { return gold_; }

    void displayStatus() const;

    void addExperience(int amount);
    void levelUp();

    void addGold(int amount) { gold_ += amount; }
    bool spendGold(int amount);

    bool isAlive() const { return hp_ > 0; }
    int  attackDamage() const { return atk_; }

    void addItem(std::unique_ptr<Item> item);
    void useItem(int index);
    std::vector<std::string> inventoryNames() const;

    void heal(int amount);            // HP 회복(최대치 초과 금지)
    void increaseAttack(int amount);  // ATK 증가
    void takeDamage(int amount);      // HP 감소(최저 0)  ← 전투용 신규

private:
    explicit Character(const std::string& name);

private:
    static Character* instance_; // 데모용으로 delete 생략

    std::string name_;
    int level_{ 1 };
    int hp_{ 200 };
    int maxHp_{ 200 };
    int atk_{ 30 };
    int exp_{ 0 };
    int gold_{ 0 };

    std::vector<std::unique_ptr<Item>> inventory_;
};

#endif
