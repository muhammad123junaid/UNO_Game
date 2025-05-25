#include "Player.h"
#include <iostream>

using namespace UNO;

Player::Player(const std::string& name) : name(name) {}

void Player::drawInitialCards(Deck& deck, int count) {
    for (int i = 0; i < count; ++i) {
        hand.push_back(deck.draw());
    }
}

Card Player::drawCard(Deck& deck) {
    Card card = deck.draw();
    hand.push_back(card);
    return card;
}

Card Player::playCard(int index) {
    if (index >= 0 && index < static_cast<int>(hand.size())) {
        Card playedCard = hand[index];
        hand.erase(hand.begin() + index);
        return playedCard;
    }
    return Card();  // Default card if invalid index
}

std::string Player::getName() const {
    return name;
}

std::vector<Card>& Player::getHand() {
    return hand;
}

const std::vector<Card>& Player::getHand() const {
    return hand;
}

bool Player::hasPlayableCard(const Card& topCard) const {
    for (const auto& card : hand) {
        if (card.isPlayableOn(topCard)) {
            return true;
        }
    }
    return false;
}
