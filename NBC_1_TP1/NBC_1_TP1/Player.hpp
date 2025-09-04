#pragma once
#include "Entity.hpp"
#include "Card.hpp"
#include <vector>
#include <conio.h>
#include <windows.h>
#include <string>

// Entity 클래스에 TakeDamage 함수가 virtual로 선언되어 있어야 합니다.
// 그렇지 않으면 제대로 작동하지 않을 수 있습니다.
class Entity {
    // ... (기존 Entity 멤버 변수)
public:
    // ...
    virtual void TakeDamage(int damage) {
        int finalDamage = damage - defense;
        if (finalDamage < 1) {
            finalDamage = 1;
        }
        hp -= finalDamage;
    }
};

class Player : public Entity {
private:
    std::vector<Card*> cards;
    int guardBonus = 0; // 방어 카드 효과를 위한 임시 방어력 보너스
public:
    Player(const std::string& name, int lvl, int hp, int stam, int atk, int def, int spd);
    ~Player();

    // 카드 관련 함수
    void ShowCards() const;
    size_t GetCardCount() const;
    Card* GetCard(int index);
    void AddCard(Card* newCard);

    // 스태미나 관련 함수
    void UseStamina(int amount);
    void HealStamina(int amount);

    // 방어 보너스 관련 함수
    void AddGuardBonus(int amount);
    void ResetGuardBonus();

    // 최종 방어력 반환 함수 (기존 방어력 + 보너스)
    int GetCurrentDEF() const;

    void PrintStatus() const;
};