#include "Entity\Enemy.h"

std::shared_ptr<Card> Enemy::GetRandomCard() {
    int totalWeight = 0;
    for (const auto& card : deck) {
        // map에 없는 카드 이름에 접근하면 에러가 날 수 있으므로, find를 이용해 확인하는 것이 더 안전함.
        if (cardWeights.find(card->C_GetName()) != cardWeights.end()) {
            totalWeight += cardWeights[card->C_GetName()];
        }
        else {
            // 가중치가 설정되지 않은 카드는 기본 가중치 1을 부여
            totalWeight += 1;
        }
    }

    if (totalWeight == 0) {
        return deck.front(); // 가중치가 없으면 첫 번째 카드 반환
    }

    int randomValue = rand() % totalWeight;
    int currentWeight = 0;

    for (const auto& card : deck) {
        if (cardWeights.find(card->C_GetName()) != cardWeights.end()) {
            currentWeight += cardWeights[card->C_GetName()];
        }
        else {
            currentWeight += 1;
        }

        if (randomValue < currentWeight) {
            return card;
        }
    }

    return deck.front(); // 안전장치
}