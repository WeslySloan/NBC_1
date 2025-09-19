#ifndef TEXTRPG_ITEM_H
#define TEXTRPG_ITEM_H

#include <string>

class Character; // 전방 선언(헤더 간 순환 의존 방지)

// [UML] Item(추상 클래스)
//  - name: string  → 공통 멤버로 보유
//  - getName(): string
//  - use(character: Character*): void
class Item {
public:
    // 부모가 name을 보관합니다. 파생 클래스는 이름을 넘겨 호출합니다.
    explicit Item(const std::string& n) : name(n) {}
    virtual ~Item() = default;

    // 공통 이름 반환(파생 클래스가 별도로 오버라이드할 필요 없음)
    virtual std::string getName() const { return name; }

    // 아이템 사용: 캐릭터의 스탯에 즉시 반영됩니다.
    // - 실제 효과는 파생 클래스에서 구현합니다.
    virtual void use(Character* character) = 0;

protected:
    std::string name; // UML 명세에 따른 공통 멤버
};

#endif
