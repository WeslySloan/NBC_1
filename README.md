# 강의 내용 정리
캠프동안 들은 강의 및 공부한 내용을 올린 Repository 입니다.

## 2025-09-18
 - <details open>
<summary> 클래스 관계 정리 </summary>
**클래스 관계 (Class Relationships)**

### 상속 관계 (Inheritance) 

'Is-a' 관계. 한 클래스가 다른 클래스의 속성과 기능을 물려받음.

  * **정의:** `AttackBoost`와 `HealthPotion`은 공통 부모 클래스인 `Item`을 상속받는다. `Item`은 객체로 생성될 수 없는 추상 클래스다.
  * **예시 코드:**
    ```cpp
    class Item {
    public:
        virtual void use(Character* character) = 0;
    };

    class AttackBoost : public Item {
    public:
        void use(Character* character) override;
    };

    class HealthPotion : public Item {
    public:
        void use(Character* character) override;
    };
    ```
  * **분석:** `AttackBoost`는 \*\*`Item`의 일종(is an Item)\*\*이다. 이 구조는 모든 아이템이 `use()` 메서드를 가질 것을 보장한다.

-----

### 포함 관계 (Composition) 

강력한 'Has-a' 관계. 한 클래스가 다른 클래스의 생명주기를 전적으로 관리한다.

  * **정의:** `Character` 클래스는 인벤토리(`inventory_`)에 `Item` 객체들을 `std::unique_ptr`를 통해 직접 소유한다. `Character`가 소멸되면 인벤토리의 아이템들도 함께 소멸된다.
  * **예시 코드:**
    ```cpp
    class Character {
    private:
        std::vector<std::unique_ptr<Item>> inventory_;
    public:
        void addItem(std::unique_ptr<Item> item);
        void useItem(int index);
    };
    ```
  * **분석:** `Character`는 `Item`을 가지고 있다(A `Character` **has a**n `Item`). `std::unique_ptr` 사용이 이 강력한 관계를 명확히 보여준다.

-----

### 의존 관계 (Dependency) 

가장 약한 관계. 한 클래스가 다른 클래스를 일시적으로 사용한다.

  * **정의:** `GameManager`는 `Character` 객체를 멤버 변수로 소유하지 않는다. 대신, 필요할 때 `Character::getInstance()`를 호출하거나 메서드 파라미터로 받아 사용한다. `Item`의 `use()` 메서드도 마찬가지다.
  * **예시 코드:**
    ```cpp
    // GameManager.cpp
    void GameManager::handleInventoryMenu() {
        Character* player = Character::instance(); // 의존 관계
        if (player) {
            displayInventory(player);
        }
    }

    // AttackBoost.cpp
    void AttackBoost::use(Character* character) { // 의존 관계
        if (!character) return;
        character->increaseAttack(attackIncrease);
    }
    ```
  * **분석:** `GameManager`와 `AttackBoost`는 `Character`에 의존하지만, 이 관계는 메서드 호출이 끝나는 즉시 사라진다.

-----

### 연관 관계 (Association) 

두 클래스가 서로를 알고 상호작용하는 일반적인 'Has-a' 관계. 생명주기는 독립적이다.

  * **정의:** `GameManager`는 게임 흐름 관리를 위해 `Character` 클래스의 존재를 인지하고 있다. `Character`는 싱글턴으로 구현되어 있어 어디서든 쉽게 접근 가능하다.
  * **예시 코드:**
    ```cpp
    // GameManager.h
    #include "Character.h" // Character 클래스에 대한 연관
    class GameManager {
    private:
        void handleCreateCharacter();
    };

    // GameManager.cpp
    void GameManager::handleCreateCharacter() {
        Character* player = Character::getInstance(); // 연관 관계
    }
    ```
  * **분석:** `GameManager`는 `Character`를 참조하여 사용한다. 이는 두 클래스가 서로를 알고 상호작용하는 연관 관계를 보여준다.

-----

### 집합 관계 (Aggregation) 🧩

느슨한 **'Has-a'** 관계. 한 클래스가 다른 클래스의 객체들을 포함하지만, 포함된 객체들이 독립적인 생명 주기를 갖는다.

  * **정의:** '선생님' 클래스는 '학생' 객체들을 멤버로 포함할 수 있다. 하지만 선생님이 사라져도 학생들은 계속 존재할 수 있다.
  * **예시 코드:**

<!-- end list -->

```cpp
#include <iostream>
#include <vector>
#include <string>

// 포함될 객체 (부품)
class Student {
public:
    Student(std::string name) : name_(name) {}
    void introduce() const {
        std::cout << "I am a student named " << name_ << std::endl;
    }
private:
    std::string name_;
};

// 포함하는 객체 (전체)
class Teacher {
public:
    Teacher(std::string name) : name_(name) {}
    void addStudent(const Student& student) {
        students_.push_back(student);
    }
    void listStudents() const {
        std::cout << name_ << " teaches:" << std::endl;
        for (const auto& student : students_) {
            student.introduce();
        }
    }
private:
    std::string name_;
    std::vector<Student> students_; // 학생들의 집합
};
```

  * **분석:** `Teacher`는 `Student`를 가지고 있다. 하지만 `Student` 객체들은 `Teacher` 객체와는 별개로 생성되고 존재할 수 있다.



</details>

## 2025-09-17
 - AttackBoost.cpp / HealPotion.cpp 수정

## 2025-09-16
 - AttackBoost.cpp / HealPotion.cpp 수정
 - 소스 및 헤더 UTF-8 인코딩

## 2025-09-15
 - TestApp 수정 
 - TextRPG 셋업 / 헤더 및 소스

## 2025-09-12
 - TestApp 수정 -> 상속/합성/다형성 예시

## 2025-09-10
 - Enemy 이동 가중치 증가 
 - 가중치 강화 상태 반환

## 2025-09-09
 - Boss가 추가 가중치를 적용 받지 못하던 문제 수정
 - Boss 2페이즈 진입시 사운드 추가

## 2025-09-08
 - Enemy, 타입별 고유기 추가
 - EnemyCard 시스템 Enemy 클래스로 이관
 - RecoverStamina시 MAXStamina를 초과하던 문제 수정

## 2025-09-05
 - enemy 이관
 - 공격 가중치 추가 및 AI 재구성

## 2025-09-04
- enemy card
- 적 및 플레이어 제자리 공격 안되는 문제 수정
- card 구현 및 그리드 전투 구성

## 2025-09-01
- TestApp 추가
- 적 및 AI

<details>
<summary> 2025년 8월 TIL</summary>

## 2025-08-11
 - README 작성
## 2025-08-07
 - CharacterResource 이주 및 레벨 디자인
## 2025-08-06
 - 텍스트 슈팅 게임
## 2025-08-05
 - 레벨 디자인
## 2025-08-04
 - 프로젝트 커밋 및 에셋 빌드

</details>