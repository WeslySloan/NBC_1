#ifndef TEXTRPG_GAMEMANAGER_H
#define TEXTRPG_GAMEMANAGER_H

#include <memory>
#include <string>
#include <vector>

class Character;
class Item;
class Monster;

class GameManager {
public:
    void run();

private:
    void showMainMenu() const;
    void handleCreateCharacter();
    void handleShowStatus() const;
    void handleShop();
    void handleInventoryMenu();

    // 전투 시작(메뉴용 편의 함수)
    void handleStartBattle();

    // [UML 명세] 전투/몬스터
    Monster* generateMonster(int level); // new로 생성, battle() 종료 시 delete
    void battle(Character* player);      // 한 번의 전투 수행(턴 자동)
    void displayInventory(Character* player);

    // 보상/로그
    void handleTestReward(); // (남겨둠) 테스트용
    void handleShowLogs() const;
    void log(const std::string& text);

    // 아이템 생성
    std::unique_ptr<Item> createHealthPotion();
    std::unique_ptr<Item> createAttackBoost();

private:
    std::vector<std::string> logs_;
    bool gameOver_{ false }; // 사망 시 true → 메인 루프 종료
};

#endif