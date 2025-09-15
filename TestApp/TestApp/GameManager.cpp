#include "GameManager.h"
#include "Character.h"
#include "Item.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>

static int readIntSafe() {
    int v;
    while (!(std::cin >> v)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "잘못된 입력입니다. 다시 입력하세요: ";
    }
    return v;
}

void GameManager::run() {
    bool running = true;
    while (running) {
        showMainMenu();
        std::cout << "> 선택: ";
        int cmd = readIntSafe();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (cmd) {
        case 1: handleCreateCharacter(); break;
        case 2: handleShowStatus(); break;
        case 3: handleShop(); break;
        case 4: handleInventoryMenu(); break;

        case 0: running = false; break;
        default: std::cout << "알 수 없는 명령입니다.\n"; break;
        }
    }
    std::cout << "게임을 종료합니다. 감사합니다!\n";
}

void GameManager::showMainMenu() const {
    std::cout << "\n===== TEXT RPG =====\n";
    std::cout << "1) 캐릭터 생성\n";
    std::cout << "2) 상태 확인\n";
    std::cout << "3) 상점 방문\n";
    std::cout << "4) 인벤토리 보기/사용\n";
    std::cout << "0) 종료\n";
}

void GameManager::handleCreateCharacter() {
    std::cout << "> 캐릭터 이름을 입력하세요: ";
    std::string name; std::getline(std::cin, name);

    Character* player = Character::getInstance(name); // 최초 1회만 생성
    player->getName();
    player->displayStatus();
}

void GameManager::handleShowStatus() const {
    Character* player = Character::instance();
    if (!player) { std::cout << "먼저 캐릭터를 생성하세요.\n"; return; }
    player->displayStatus();
}

void GameManager::handleInventoryMenu() {
    Character* player = Character::instance();
    if (!player) { std::cout << "먼저 캐릭터를 생성하세요.\n"; return; }
    displayInventory(player);
}


void GameManager::displayInventory(Character* player) {
    auto names = player->inventoryNames();
    std::cout << "\n-- 인벤토리 --\n";
    if (names.empty()) { std::cout << "비어있습니다.\n"; return; }

    for (std::size_t i = 0; i < names.size(); ++i) {
        std::cout << "[" << i << "] " << names[i] << "\n";
    }
    std::cout << "사용할 아이템 번호(취소: -1): ";
    int idx = readIntSafe();
    if (idx < 0) return;

    if (idx >= 0 && static_cast<std::size_t>(idx) < names.size()) {
        player->useItem(idx);
        log("아이템 사용: " + names[static_cast<std::size_t>(idx)]);
        player->displayStatus();
    }
    else {
        std::cout << "잘못된 번호입니다.\n";
    }
}

void GameManager::handleShop() {
    Character* player = Character::instance();
    if (!player) { std::cout << "먼저 캐릭터를 생성하세요.\n"; return; }

    bool stay = true;
    while (stay) {
        std::cout << "\n-- 상점 -- (보유 골드: " << player->getGold() << ")\n";
        std::cout << "1) HealthPotion (+50 HP) ? 30G\n";
        std::cout << "2) AttackBoost (+10 ATK) ? 50G\n";
        std::cout << "0) 나가기\n> 선택: ";
        int cmd = readIntSafe();

        if (cmd == 0) { stay = false; break; }
        if (cmd == 1) {
            if (player->spendGold(30)) {
                player->addItem(createHealthPotion());
                log("상점 구매: HealthPotion (-30G)");
                std::cout << "HealthPotion을 구매했습니다.\n";
            }
            else std::cout << "골드가 부족합니다.\n";
        }
        else if (cmd == 2) {
            if (player->spendGold(50)) {
                player->addItem(createAttackBoost());
                log("상점 구매: AttackBoost (-50G)");
                std::cout << "AttackBoost를 구매했습니다.\n";
            }
            else std::cout << "골드가 부족합니다.\n";
        }
        else {
            std::cout << "알 수 없는 명령입니다.\n";
        }
    }
}