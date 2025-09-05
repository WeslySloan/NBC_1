#pragma once
#include "Entity\Entity.h"
#include <iostream>
#include <vector>
#include <memory>
#include <map> // 가중치를 저장하기 위해 추가
#include "Card\Card.h"

class Enemy : public Entity {
private:
	int drop_money;
	int drop_exp;
	std::vector<std::shared_ptr<Card>> deck;
	std::map<std::string, int> cardWeights; // 카드별 가중치를 저장할 맵 추가

public:
	Enemy(std::string n, int lv, int h, int s, int a, int d, int dm, int de)
		: Entity(n, lv, h, s, a, d), drop_money(dm), drop_exp(de) {
	}
	int getExp() { return drop_exp; }
	int getmoney() { return drop_money; }

	void AddCard(const std::shared_ptr<Card>& c) { deck.push_back(c); }
	std::vector<std::shared_ptr<Card>>& GetCards() { return deck; }
	void AddCardWeight(const std::string& cardName, int weight) { cardWeights[cardName] = weight; } // 가중치를 추가하는 함수

	void RecoverStamina(int amount) {
		SetStamina(GetStamina() + amount);
	}

	~Enemy() {};


	//----------------임시----------------

	// 기존 GetRandomCard() 함수를 가중치를 고려하도록 수정
	//std::shared_ptr<Card> GetRandomCard() {
	//	int idx = rand() % deck.size();
	//	return deck[idx];
	//}
	std::shared_ptr<Card> GetRandomCard();

};