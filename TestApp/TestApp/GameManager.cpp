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


// 안전한 정수 입력: 잘못된 입력을 클리어하고 재입력 요청
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
        case 5: handleTestReward(); break; // 전투 미구현 구간을 보상 시뮬로 대체
        case 6: handleShowLogs(); break;
        case 0: running = false; break;
        default: std::cout << "알 수 없는 명령입니다.\n"; break;
        }
    }
    std::cout << "게임을 종료합니다. 감사합니다!\n";
}

void GameManager::showMainMenu() const {
    std::cout << "\n===== TEXT RPG (UML-aligned Skeleton) =====\n";
    std::cout << "1) 캐릭터 생성\n";
    std::cout << "2) 상태 확인\n";
    std::cout << "3) 상점 방문\n";
    std::cout << "4) 인벤토리 보기/사용\n";
    std::cout << "5) (임시) 전투 보상 받기\n";
    std::cout << "6) 로그 보기\n";
    std::cout << "0) 종료\n";
}

void GameManager::handleCreateCharacter() {
    std::cout << "> 캐릭터 이름을 입력하세요: ";
    std::string name; std::getline(std::cin, name);

    Character* player = Character::getInstance(name); // 최초 1회만 생성
    player->displayStatus();
    log("캐릭터 '" + player->getName() + "' 생성(싱글턴) 완료!");
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

Monster* GameManager::generateMonster(int /*level*/) {
    // TODO: Monster 추상 클래스/구현체 도입 후 레벨 기반 랜덤 생성
    std::cout << "(generateMonster) 아직 미구현입니다.\n";
    return nullptr;
}

void GameManager::battle(Character* /*player*/) {
    // TODO: 턴 기반 전투 루프 구현(아이템 자동 사용 전략 포함 가능)
    std::cout << "(battle) 아직 미구현입니다.\n";
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

void GameManager::handleTestReward() {
    Character* player = Character::instance();
    if (!player) { std::cout << "먼저 캐릭터를 생성하세요.\n"; return; }

    // 요구사항: EXP +50, Gold 10~20, 30% 확률 아이템 드랍
    std::random_device rd; std::mt19937 rng(rd());
    std::uniform_int_distribution<int> goldDist(10, 20);
    std::uniform_int_distribution<int> itemPick(0, 1);
    std::uniform_real_distribution<double> p(0.0, 1.0);

    int gold = goldDist(rng);
    player->addExperience(50);
    player->addGold(gold);

    log("전투 승리 보상: EXP +50, Gold +" + std::to_string(gold));
    std::cout << "전투 보상을 받았습니다! (EXP +50, Gold +" << gold << ")\n";

    if (p(rng) < 0.3) {
        if (itemPick(rng) == 0) {
            player->addItem(createHealthPotion());
            log("드랍 아이템: HealthPotion");
            std::cout << "아이템 획득: HealthPotion\n";
        }
        else {
            player->addItem(createAttackBoost());
            log("드랍 아이템: AttackBoost");
            std::cout << "아이템 획득: AttackBoost\n";
        }
    }
}

void GameManager::handleShowLogs() const {
    if (logs_.empty()) { std::cout << "아직 로그가 없습니다.\n"; return; }
    std::cout << "\n-- 게임 로그 --\n";
    for (const auto& line : logs_) std::cout << line << "\n";
}

void GameManager::log(const std::string& text) {
    logs_.push_back(text);
}

std::unique_ptr<Item> GameManager::createHealthPotion() {
    return std::make_unique<HealthPotion>(50);
}
std::unique_ptr<Item> GameManager::createAttackBoost() {
    return std::make_unique<AttackBoost>(10);
}
