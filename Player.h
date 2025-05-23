#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"
#include "Deck.h"

namespace UNO {

class Player {
private:
    std::string name;
    std::vector<Card> hand;

public:
    Player(const std::string& name);

    void drawInitialCards(Deck& deck, int count);
    Card drawCard(Deck& deck);  // Updated to return Card
    void playCard(int index);
    std::string getName() const;

    // New getter functions
    std::vector<Card>& getHand();
    const std::vector<Card>& getHand() const;

    bool hasPlayableCard(const Card& topCard) const;
};

} // namespace UNO

#endif
