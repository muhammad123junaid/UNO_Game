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

        // Helper to add N copies of a card
        void addCopies(const Card& card, int n);

    public:
        // Build a standard 108‑card UNO deck and seed RNG
        Deck();

        // Shuffle the deck
        void shuffle();

        // Draw one card (throws if empty)
        Card draw();

        // Draw multiple cards (up to count or until empty)
        std::vector<Card> drawMultiple(int count);

        // How many cards remain
        int cardsRemaining() const;

        // Reset to a full, fresh deck (unshuffled)
        void reset();
    };

} // namespace UNO

#endif // DECK_H
