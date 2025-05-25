#ifndef CARD_H
#define CARD_H

#include <string>
#include <iostream>

namespace UNO {

    enum class Color { Red, Green, Blue, Yellow, Wild };
    enum class Value { Zero, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
                       Skip, Reverse, DrawTwo, Wild, WildDrawFour };

    class Card {
    private:
        Color color;
        Value value;

    public:
        Card();                       // Added default constructor
        Card(Color c, Value v);

        Color getColor() const;
        Value getValue() const;

        static std::string colorToString(Color c);
        static std::string valueToString(Value v);

        std::string toString() const;
        void displayCard() const;
        bool isPlayableOn(const Card& topCard) const;

        bool operator==(const Card& o) const;
        bool operator!=(const Card& o) const;

        friend std::ostream& operator<<(std::ostream& os, const Card& card);
    };

    inline std::ostream& operator<<(std::ostream& os, const Card& card) {
        os << card.toString();
        return os;
    }

} // namespace UNO

#endif // CARD_H
