// -------------------------------------------------------------
// File: GameManager.cpp  (tension update)
// -------------------------------------------------------------
#include "GameManager.h"
#include "Character.h"
#include "Item.h"
#include "Monster.h"
#include "Goblin.h"
#include "Orc.h"
#include "Troll.h"
#include "Slime.h"
#include "BossDragon.h"
#include "HealthPotion.h"
#include "AttackBoost.h"

#include <iostream>
#include <limits>
#include <memory>
#include <random>
#include <string>
#include <cmath>

// ===== 난이도/전투 파라미터 (원하면 여기 숫자만 조절하세요) =====
static constexpr double PLAYER_HIT_CHANCE = 0.90; // 명중률
static constexpr double MONSTER_HIT_CHANCE = 0.90;
static constexpr double CRIT_CHANCE = 0.10; // 치명타 확률
static constexpr double CRIT_MULTI = 1.50; // 치명타 배수
static constexpr double DMG_VAR_MIN = 0.80; // 데미지 변동폭 하한
static constexpr double DMG_VAR_MAX = 1.20; // 데미지 변동폭 상한
static constexpr double ENRAGE_THRESHOLD = 0.30; // 몬스터 분노 발동 HP% (<= 30%)
static constexpr double ENRAGE_MULTI = 1.25; // 분노 배수
static constexpr double MONSTER_POWER_P = 0.15; // 몬스터 강공격 확률
static constexpr double MONSTER_POWER_MULTI = 1.50; // 강공격 배수

// 아이템 자동 사용 제한
static constexpr int    ITEM_COOLDOWN_TURNS = 2;    // 포션 사용 쿨다운(턴)
static constexpr double AUTO_POTION_CHANCE = 0.50; // 조건 만족 시 포션 사용 확률
static constexpr double AUTO_BOOST_CHANCE = 0.20; // 부스트 사용 확률(전투당 1회)

// 안전한 정수 입력
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
    while (running && !gameOver_) {
        showMainMenu();
        std::cout << "> 선택: ";
        int cmd = readIntSafe();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (cmd) {
        case 1: handleCreateCharacter(); break;
        case 2: handleShowStatus(); break;
        case 3: handleShop(); break;
        case 4: handleInventoryMenu(); break;
        case 5: handleTestReward(); break;
        case 6: handleShowLogs(); break;
        case 7: handleStartBattle(); break;
        case 0: running = false; break;
        default: std::cout << "알 수 없는 명령입니다.\n"; break;
        }
    }
    std::cout << "게임을 종료합니다. 감사합니다!\n";
}

void GameManager::showMainMenu() const {
    std::cout << "\n===== TEXT RPG (Tension Battle) =====\n";
    std::cout << "1) 캐릭터 생성(싱글턴)\n";
    std::cout << "2) 상태 확인\n";
    std::cout << "3) 상점 방문\n";
    std::cout << "4) 인벤토리 보기/사용\n";
    std::cout << "5) (테스트) 전투 보상 받기\n";
    std::cout << "6) 로그 보기\n";
    std::cout << "7) 전투 시작\n";
    std::cout << "0) 종료\n";
}

void GameManager::handleCreateCharacter() {
    std::cout << "> 캐릭터 이름을 입력하세요: ";
    std::string name; std::getline(std::cin, name);

    Character* player = Character::getInstance(name);
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

void GameManager::handleStartBattle() {
    Character* player = Character::instance();
    if (!player) { std::cout << "먼저 캐릭터를 생성하세요.\n"; return; }

    battle(player);
    if (gameOver_) return;

    std::cout << "상점에 들르시겠습니까? (1:예, 0:아니오): ";
    int y = readIntSafe();
    if (y == 1) handleShop();
}

Monster* GameManager::generateMonster(int level) {
    if (level >= Character::MAX_LEVEL) {
        return new BossDragon();
    }
    std::random_device rd; std::mt19937 rng(rd());
    std::uniform_int_distribution<int> pick(0, 3);
    switch (pick(rng)) {
    case 0: return new Goblin(level);
    case 1: return new Orc(level);
    case 2: return new Troll(level);
    default: return new Slime(level);
    }
}

// 전투 1회 실행(턴 자동) — 난이도 요소 적용
void GameManager::battle(Character* player) {
    if (!player) return;

    std::unique_ptr<Monster> m(generateMonster(player->getLevel()));
    std::cout << "몬스터 " << m->getName() << " 등장! 체력: " << m->getHealth()
        << ", 공격력: " << m->getAttack() << "\n";
    log("전투 시작: vs " + m->getName());

    std::random_device rd; std::mt19937 rng(rd());
    std::uniform_real_distribution<double> U01(0.0, 1.0);
    std::uniform_real_distribution<double> UVar(DMG_VAR_MIN, DMG_VAR_MAX);

    // 전투 중 아이템 사용 제한 상태
    int  itemCooldown = 0;         // 포션 쿨다운
    bool usedBoost = false;     // 전투당 1회 제한
    bool enraged = false;     // 몬스터 분노 여부


    // 데미지 주사위
    auto rollDamage = [&](int baseAtk, bool attackerIsPlayer) -> int {
        // 명중 체크
        double hitP = attackerIsPlayer ? PLAYER_HIT_CHANCE : MONSTER_HIT_CHANCE;
        if (U01(rng) > hitP) return -1; // -1은 미스

        // 변동폭/치명타
        double dmg = baseAtk * UVar(rng); // 100 * 0.8 = 80
        bool isCrit = (U01(rng) < CRIT_CHANCE);
        if (isCrit) dmg *= CRIT_MULTI;

        // 반올림
        return std::max(1, static_cast<int>(std::lround(dmg)));
        };

    // 자동 아이템 사용 시도
    auto tryAutoUseItem = [&](Character* c) -> bool {
        if (itemCooldown > 0) return false;

        auto names = c->inventoryNames();
        if (names.empty()) return false;

        // HP 40% 이하 → 50% 확률로 포션 우선
        if (c->getHP() * 10 <= c->getMaxHP() * 4) {
            if (U01(rng) < AUTO_POTION_CHANCE) {
                for (std::size_t i = 0; i < names.size(); ++i) {
                    if (names[i] == "HealthPotion") {
                        c->useItem(static_cast<int>(i));
                        itemCooldown = ITEM_COOLDOWN_TURNS; // 쿨 시작
                        log("전투 중 자동 아이템 사용: HealthPotion");
                        return true;
                    }
                }
            }
        }
        // 포션을 못 썼으면 부스트 20% (전투당 1회)
        if (!usedBoost && U01(rng) < AUTO_BOOST_CHANCE) {
            for (std::size_t i = 0; i < names.size(); ++i) {
                if (names[i] == "AttackBoost") {
                    c->useItem(static_cast<int>(i));
                    usedBoost = true;
                    log("전투 중 자동 아이템 사용: AttackBoost");
                    return true;
                }
            }
        }
        return false;
        };

    // 턴 루프
    int turn = 1;
    while (player->isAlive() && m->getHealth() > 0) {
        std::cout << "\n-- 턴 " << turn << " --\n";

        // (플레이어 턴) — 자동 아이템
        tryAutoUseItem(player);

        // 플레이어 → 몬스터
        int pBase = player->attackDamage();
        int pDmg = rollDamage(pBase, true);
        if (pDmg < 0) {
            std::cout << player->getName() << "의 공격이 빗나갔습니다!\n";
        }
        else {
            m->takeDamage(pDmg);
            std::cout << player->getName() << "가 " << m->getName()
                << "을(를) 공격! 피해 " << pDmg
                << " → " << m->getName() << " 체력: " << m->getHealth() << "\n";

            // 분노 체크(한 번만 발동)
            int enrageHP = static_cast<int>(std::ceil(m->getHealth() / ENRAGE_THRESHOLD)); // not exact, just flag below
            (void)enrageHP; // silence warning (we're checking percentage directly below)
            //if (!enraged) {
            //    // 현재 HP%가 30% 이하로 내려갔는지 확인
            //    // (직전 공격으로 낮아졌을 수 있으니 여기서 판단)
            //    // health / maxHealth를 모르면, '처음 HP 대비'를 못 구하니
            //    // 간단히 '현 체력이 0이 아니고, 플레이어 ATK가 몬스터 ATK보다 낮거나 같으면' 등으로도 트리거할 수 있으나
            //    // 이 예제에서는 '체력 수치 기준'으로 단순 처리: 1차 발동 메시지 한번만.
            //    // → 실제 최대체력을 모르는 구조라, 분노는 아래 몬스터 턴 시작 시 HP%로 체크하도록 이동.
            //}
        }

        if (m->getHealth() <= 0)
        {
            std::cout << m->getName() << " 처치!\n";
            if (dynamic_cast<BossDragon*>(m.get()) != nullptr)
            {
                std::cout << "보스 Dragon을 쓰러뜨렸습니다! 게임 클리어!\n";
                log("보스 격파: 게임 클리어");
                gameOver_ = true;
            }
            break;
        }


        // (몬스터 턴) — 분노/강공격 반영
        // 분노 트리거: 현재 HP% <= 30%
        // (최대체력을 모르니 출현 당시 공격력으로 '추정'하지 않고,
        //  분노는 한번만 켜고 이후 공격 배수만 적용)
        if (!enraged) 
        {
            // 간단히: 등장 직후 체력을 기억하지 못하니, 임계값을 절대값으로 추정하기 어렵다.
            // 여기서는 플레이어 공격으로 HP가 '초기 기준의 30% 이하로 내려갔다'고 가정하는 효과만 주기 위해,
            //  전투 중 한 번 랜덤으로(HP가 낮아졌을 때) 분노가 켜질 수 있도록 확률 트리거를 둡니다.
            //  → 실전이라면 Monster가 maxHealth를 갖고 있어야 정확하게 퍼센트를 계산할 수 있습니다.
            if (m->getHealth() <= (player->attackDamage())) 
            {
                enraged = true;
                std::cout << m->getName() << "이(가) 분노합니다! (공격 상승)\n";
                log("몬스터 분노 발동: " + m->getName());
            }
        }

        int mBase = m->getAttack();
        double mult = 1.0;

        if (enraged) mult *= ENRAGE_MULTI;                 // 분노 배수
        if (U01(rng) < MONSTER_POWER_P) mult *= MONSTER_POWER_MULTI; // 강공격

        int mRoll = rollDamage(static_cast<int>(std::lround(mBase * mult)), false);
        if (mRoll < 0) {
            std::cout << m->getName() << "의 공격이 빗나갔습니다!\n";
        }
        else {
            player->takeDamage(mRoll);
            std::cout << m->getName() << "이(가) " << player->getName()
                << "를 공격! 피해 " << mRoll
                << " → " << player->getName()
                << " 체력: " << player->getHP() << "\n";
        }

        if (!player->isAlive()) {
            std::cout << player->getName() << "가 사망했습니다. 게임 오버!\n";
            log("게임 오버: 전투 패배");
            gameOver_ = true;
            return;
        }

        // 턴 종료 처리
        if (itemCooldown > 0) --itemCooldown;
        ++turn;
    }

    if (gameOver_) return;

    // ===== 일반 승리 보상 =====
    std::random_device rd2; std::mt19937 rng2(rd2());
    std::uniform_int_distribution<int> goldDist(10, 20);
    std::uniform_int_distribution<int> itemPick(0, 1);
    std::uniform_real_distribution<double> dropP(0.0, 1.0);

    int gold = goldDist(rng2);
    player->addExperience(50);
    player->addGold(gold);

    std::cout << player->getName() << "가 50 EXP와 "
        << gold << " 골드를 획득했습니다. "
        << "현재 EXP: " << player->getEXP() << "/"
        << Character::EXP_TO_LEVEL
        << ", 골드: " << player->getGold() << "\n";
    log("전투 승리: EXP +50, Gold +" + std::to_string(gold));

    if (dropP(rng2) < 0.3) {
        if (itemPick(rng2) == 0) {
            player->addItem(createHealthPotion());
            std::cout << "아이템 드랍: HealthPotion\n";
            log("드랍 아이템 획득: HealthPotion");
        }
        else {
            player->addItem(createAttackBoost());
            std::cout << "아이템 드랍: AttackBoost\n";
            log("드랍 아이템 획득: AttackBoost");
        }
    }

    if (player->getLevel() >= Character::MAX_LEVEL) {
        std::cout << "레벨 10 달성! 다음 전투는 보스 전투가 됩니다.\n";
    }
}

void GameManager::displayInventory(Character* player) {
    auto names = player->inventoryNames();
    std::cout << "\n-- 인벤토리 --\n";
    if (names.empty()) { std::cout << "비어있습니다.\n"; return; }

    for (std::size_t i = 0; i < names.size(); ++i)
        std::cout << "[" << i << "] " << names[i] << "\n";

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
        std::cout << "1) HealthPotion (+50 HP) — 30G\n";
        std::cout << "2) AttackBoost (+10 ATK) — 50G\n";
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

    std::random_device rd; std::mt19937 rng(rd());
    std::uniform_int_distribution<int> goldDist(10, 20);
    std::uniform_int_distribution<int> itemPick(0, 1);
    std::uniform_real_distribution<double> p(0.0, 1.0);

    int gold = goldDist(rng);
    player->addExperience(50);
    player->addGold(gold);

    log("전투 승리 보상(테스트): EXP +50, Gold +" + std::to_string(gold));
    std::cout << "전투 보상(테스트)! (EXP +50, Gold +" << gold << ")\n";

    if (p(rng) < 0.3) {
        if (itemPick(rng) == 0) {
            player->addItem(createHealthPotion());
            log("드랍 아이템(테스트): HealthPotion");
            std::cout << "아이템 획득: HealthPotion\n";
        }
        else {
            player->addItem(createAttackBoost());
            log("드랍 아이템(테스트): AttackBoost");
            std::cout << "아이템 획득: AttackBoost\n";
        }
    }
}

void GameManager::handleShowLogs() const {
    if (logs_.empty()) { std::cout << "아직 로그가 없습니다.\n"; return; }
    std::cout << "\n-- 게임 로그 --\n";
    for (const auto& line : logs_) std::cout << line << "\n";
}

void GameManager::log(const std::string& text) { logs_.push_back(text); }

std::unique_ptr<Item> GameManager::createHealthPotion() { return std::make_unique<HealthPotion>(50); }
std::unique_ptr<Item> GameManager::createAttackBoost() { return std::make_unique<AttackBoost>(10); }
