#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Enemy.h"
#include "Entity.h"

using namespace std;

// Player 클래스 (테스트용)
class Player : public Entity 
{
private:
    int Money;
    int EXP;
public:
    Player(const string& name, int lvl, int hp, int stam, int atk, int def)
        : Entity(name, lvl, hp, stam, atk, def), Money(0), EXP(0) {}

    void AddMoney(int amount) 
    {
        Money += amount;
        cout << "돈 " << amount << "을 얻었습니다! (현재 소지금: " << Money << ")\n";
    }

    void AddEXP(int amount) 
    {
        EXP += amount;
        cout << "경험치 " << amount << "를 얻었습니다! (현재 경험치: " << EXP << ")\n";
    }
};

int main() 
{
    srand(static_cast<unsigned int>(time(0)));

    Player player("이누야샤", 1, 100, 50, 25, 15);
    Enemy enemy("요괴", 1, 80, 40, 20, 10, 50, 30);

    player.PrintStatus();
    enemy.PrintStatus();

    cout << "전투가 시작되었습니다!\n";

    while (player.GetCurrentHP() > 0 && enemy.GetCurrentHP() > 0) 
    {
        cout << "\n--- 이누야샤의 턴 ---\n";

        int playerDamage = player.GetAttack();
        cout << player.GetName() << "이(가) " << enemy.GetMob_Name() << "을(를) 공격합니다!\n";
        enemy.TakeDamage(playerDamage);

        if (enemy.GetCurrentHP() <= 0) 
        {
            cout << "\n" << enemy.GetMob_Name() << "을(를) 물리쳤습니다!\n";
            player.AddMoney(enemy.GetDrop_money());
            player.AddEXP(enemy.GetDrop_exp());
            break;
        }

        cout << "\n--- " << enemy.GetMob_Name() << "의 턴 ---\n";

        enemy.Act(&player);

        if (player.GetCurrentHP() <= 0) 
        {
            cout << "\n" << player.GetName() << "이(가) 쓰러졌습니다...\n";
            break;
        }
    }

    cout << "\n전투 종료.\n";
    player.PrintStatus();
    enemy.PrintStatus();

    return 0;
}