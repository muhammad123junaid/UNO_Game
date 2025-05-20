#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>

namespace UNO {

    class Deck {
    private:
        std::vector<Card> cards;
        std::mt19937 rng;

        void addCopies(const Card& card, int n);

    public:
        Deck();

        void shuffle();

        Card draw();

        std::vector<Card> drawMultiple(int count);

        int cardsRemaining() const;

        void reset();
    };

} 

#endif 
