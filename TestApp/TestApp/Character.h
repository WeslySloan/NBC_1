#pragma once
#ifndef TEXTRPG_CHARACTER_H
#define TEXTRPG_CHARACTER_H

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Item;

// [UML] Character (싱글턴)
//  - static instance: Character*
//  - static getInstance(name: string = ""): Character*
//  - displayStatus(): void
//  - levelUp(): void
//  - useItem(index: int): void
//
// 싱글턴을 쓰는 이유:
//  - 게임에서 플레이어 캐릭터는 1개라는 규칙을 '타입 차원'에서 강제.
//  - 어디서든 동일 인스턴스 접근이 쉬워 관리가 단순.
// 복사 금지(delete)를 하는 이유/동작:
//  - 싱글턴은 복제되면 안 되므로 복사 생성자/대입 연산자를 =delete 처리.
//  - 이러면 컴파일 단계에서 복사 시도를 막아 실수로 두 번째 인스턴스가
//    생기는 일을 원천 차단합니다.
class Character {
public:
    static constexpr int EXP_TO_LEVEL = 100; // 레벨업 필요 EXP(고정)
    static constexpr int MAX_LEVEL = 10;  // 최대 레벨

    // 싱글턴 인스턴스 획득(최초 1회만 name 사용하여 생성)
    static Character* getInstance(const std::string& name = "");
    // 현재 인스턴스 포인터(없으면 nullptr)
    static Character* instance() { return instance_; }

    // 복사 금지
    Character(const Character&) = delete;
    Character& operator=(const Character&) = delete;

    // --- 조회 ---
    const std::string& getName() const { return name_; }
    int  getLevel() const { return level_; }
    int  getHP()    const { return hp_; }
    int  getMaxHP() const { return maxHp_; }
    int  getATK()   const { return atk_; }
    int  getEXP()   const { return exp_; }
    int  getGold()  const { return gold_; }

    // --- 표시 ---
    // 현재 상태를 보기 좋게 콘솔에 출력
    void displayStatus() const;

    // --- 성장/자원 ---
    // EXP를 늘립니다(누적이 100 이상이면 자동으로 levelUp() 반복 호출)
    void addExperience(int amount);
    // [UML: public] 명시적 레벨업 메서드
    //  - 레벨 +1
    //  - 최대체력 += (현재 레벨 × 20)
    //  - 공격력   += (현재 레벨 × 5)
    //  - HP를 최대치로 완전 회복
    void levelUp();
    // 골드 조작(부족하면 spendGold는 false)
    void addGold(int amount) { gold_ += amount; }
    bool spendGold(int amount);

    // --- 전투 보조 ---
    bool isAlive() const { return hp_ > 0; }
    int  attackDamage() const { return atk_; }

    // --- 인벤토리 ---
    // 아이템 소유권을 캐릭터가 획득(메모리 자동 관리)
    void addItem(std::unique_ptr<Item> item);
    // 인벤토리 index번 아이템 사용(성공 시 제거)
    void useItem(int index);
    // 인벤토리 이름 목록 반환(출력/선택 메뉴용)
    std::vector<std::string> inventoryNames() const;

    // --- 능력치 변화(아이템에서 호출) ---
    void heal(int amount);            // HP 회복(최대치 초과 금지)
    void increaseAttack(int amount);  // ATK 증가

private:
    explicit Character(const std::string& name); // 싱글턴: 외부 new 금지

private:
    static Character* instance_; // 현재 살아있는 싱글턴 포인터

    // 상태 값
    std::string name_;
    int level_{ 1 };
    int hp_{ 200 };
    int maxHp_{ 200 };
    int atk_{ 30 };
    int exp_{ 0 };
    int gold_{ 0 };

    // 인벤토리(소유권 보유)
    std::vector<std::unique_ptr<Item>> inventory_;
};

#endif
