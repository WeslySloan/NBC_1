#ifndef TEXTRPG_MONSTER_H
#define TEXTRPG_MONSTER_H

#include <string>

// UML: Monster 인터페이스
//  - getName(): string
//  - getHealth(): int
//  - getAttack(): int
//  - takeDamage(damage: int): void
class Monster {
public:
    virtual ~Monster() = default;

    virtual std::string getName()  const = 0;
    virtual int         getHealth() const = 0;
    virtual int         getAttack() const = 0;
    virtual void        takeDamage(int damage) = 0;
};

#endif

//#ifndef TEXTRPG_MONSTER_H
//#define TEXTRPG_MONSTER_H
//
//#include <string>
//
//// [UML] Monster (추상 기반)
////  - name, hp, atk 공통 멤버
////  - getName(), getHP(), getATK(), takeDamage(), isAlive()
//class Monster {
//public:
//    virtual ~Monster() = default;
//
//    const std::string& getName() const { return name_; }
//    int  getHP()  const { return hp_; }
//    int  getATK() const { return atk_; }
//
//    // 데미지를 받아 HP를 감소(최저 0)
//    void takeDamage(int dmg);
//
//    // 생존 여부
//    bool isAlive() const { return hp_ > 0; }
//
//protected:
//    // 파생 클래스가 이름/스탯을 정해 전달
//    Monster(const std::string& n, int hp, int atk);
//
//    std::string name_;
//    int hp_;
//    int atk_;
//};
//
//#endif