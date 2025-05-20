#include "Deck.h"
#include <algorithm>
#include <chrono>

namespace UNO {

    Deck::Deck()
        : rng(static_cast<unsigned>(
            std::chrono::high_resolution_clock::now().time_since_epoch().count()
          ))
    {
        reset();
    }

    void Deck::addCopies(const Card& card, int n) {
        for (int i = 0; i < n; ++i)
            cards.push_back(card);
    }

    void Deck::reset() {
        cards.clear();

        for (auto c : {Color::Red, Color::Green, Color::Blue, Color::Yellow})
            addCopies(Card(c, Value::Zero), 1);

        for (auto c : {Color::Red, Color::Green, Color::Blue, Color::Yellow}) {
            for (auto v : { Value::One, Value::Two, Value::Three, Value::Four,
                            Value::Five, Value::Six, Value::Seven, Value::Eight, Value::Nine,
                            Value::Skip, Value::Reverse, Value::DrawTwo }) {
                addCopies(Card(c, v), 2);
            }
        }

        addCopies(Card(Color::Wild, Value::Wild), 4);
        addCopies(Card(Color::Wild, Value::WildDrawFour), 4);
    }

    void Deck::shuffle() {
        std::shuffle(cards.begin(), cards.end(), rng);
    }

    Card Deck::draw() {
        if (cards.empty())
            throw std::out_of_range("Cannot draw from an empty deck");
        Card top = cards.back();
        cards.pop_back();
        return top;
    }

    std::vector<Card> Deck::drawMultiple(int count) {
        std::vector<Card> hand;
        hand.reserve(count);
        for (int i = 0; i < count && !cards.empty(); ++i) {
            hand.push_back(draw());
        }
        return hand;
    }

    int Deck::cardsRemaining() const {
        return static_cast<int>(cards.size());
    }

} 
