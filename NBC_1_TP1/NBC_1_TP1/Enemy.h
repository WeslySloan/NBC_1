#ifndef ENEMY_H
#define ENEMY_H

#include "Entity.hpp"

class Enemy : public Entity 
{
private:
    std::string mob_name;
    int drop_money;
    int drop_exp;

public:
    // 생성자
    Enemy(const std::string& name, int lvl, int hp, int stam, int atk, int def, int money, int exp);

    // AI 행동 함수
    void Act(Entity* target);

    // 고유 속성 getter 함수
    std::string GetMob_Name() const;
    int GetDrop_money() const;
    int GetDrop_exp() const;
};

#endif