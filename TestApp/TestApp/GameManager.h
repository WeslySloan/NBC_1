#ifndef TEXTRPG_GAMEMANAGER_H
#define TEXTRPG_GAMEMANAGER_H

#include <memory>
#include <string>
#include <vector>

class Character;
class Item;
class Monster; // 추후 전투/몬스터 계층 추가 예정

// [UML] GameManager
//  - generateMonster(level: int): Monster*
//  - battle(player: Character*): void
//  - displayInventory(player: Character*): void
class GameManager {
public:
    // 메인 루프(메뉴 표시 → 입력 → 동작 수행)
    void run();

private:
    void displayInventory(Character* player); // 인벤토리 표시/사용



    void showMainMenu() const;       // 메뉴 UI 출력
    void handleCreateCharacter();    // 싱글턴 캐릭터 생성
    void handleShowStatus() const;   // 상태 출력
    void handleShop();               // 상점(구매/지급/로그)
    void handleInventoryMenu();      // 인벤토리 화면(→ displayInventory 호출)

    // [UML 명세] 전투/몬스터(현재 스텁)
    Monster* generateMonster(int level); // 레벨 기반 몬스터 생성(미구현)
    void battle(Character* player);      // 턴 전투 루프(미구현)
    void handleTestReward();         // (임시) 전투 보상 시뮬레이터
    void handleShowLogs() const;     // 누적 로그 출력
    void log(const std::string& text); // 이벤트 문자열 저장

    // 아이템 생성 유틸
    std::unique_ptr<Item> createHealthPotion();
    std::unique_ptr<Item> createAttackBoost();

private:
    std::vector<std::string> logs_;
};

#endif
