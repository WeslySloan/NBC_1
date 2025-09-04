#include "Player.hpp"
#include <iostream>
#include <conio.h>
#include <windows.h>

Player::Player(const std::string& name, int lvl, int hp, int stam, int atk, int def, int spd)
    : Entity(name, lvl, hp, stam, atk, def) {
}

Player::~Player() {
    for (Card* card : cards) {
        delete card;
    }
    cards.clear();
}

void Player::ShowCards() const {
    std::cout << "--- 내 패 ---\n";
    for (size_t i = 0; i < cards.size(); ++i) {
        std::cout << i + 1 << ". " << cards[i]->C_GetName()
            << " (코스트: " << cards[i]->C_GetCost() << ", 생성: " << cards[i]->C_GetGen() << ")\n";
    }
    std::cout << "-------------------\n";
}

void Player::UseStamina(int amount) {
    stamina -= amount;
    if (stamina < 0) {
        stamina = 0;
    }
}

void Player::HealStamina(int amount) {
    stamina += amount;
    if (stamina > max_stamina) {
        stamina = max_stamina;
    }
}

void Player::AddCard(Card* newCard) {
    cards.push_back(newCard);
}

size_t Player::GetCardCount() const {
    return cards.size();
}

Card* Player::GetCard(int index) {
    if (index >= 0 && index < cards.size()) {
        return cards[index];
    }
    return nullptr;
}

// 방어 보너스 관련 함수들
void Player::AddGuardBonus(int amount) {
    guardBonus = amount;
}

void Player::ResetGuardBonus() {
    guardBonus = 0;
}

// 현재 방어력(기본 + 보너스) 반환 함수
int Player::GetCurrentDEF() const {
    return defense + guardBonus;
}

void Player::PrintStatus() const {
    std::cout << "--- " << name << "의 상태 ---\n";
    std::cout << "HP: " << hp << " / " << max_hp << "\n";
    std::cout << "Stamina: " << stamina << " / " << max_stamina << "\n";
    std::cout << "ATK: " << attack << ", DEF: " << GetCurrentDEF() << "\n";
    std::cout << "-----------------------\n";
}