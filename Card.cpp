#include "Card.h"

using namespace UNO;

Card::Card() : color(Color::Red), value(Value::Zero) {} 
Card::Card(Color c, Value v) : color(c), value(v) {}

Color Card::getColor() const { return color; }
Value Card::getValue() const { return value; }

std::string Card::colorToString(Color c) {
    switch (c) {
        case Color::Red: return "Red";
        case Color::Green: return "Green";
        case Color::Blue: return "Blue";
        case Color::Yellow: return "Yellow";
        case Color::Wild: return "Wild";
    }
    return "Unknown";
}

std::string Card::valueToString(Value v) {
    switch (v) {
        case Value::Zero: return "0";
        case Value::One: return "1";
        case Value::Two: return "2";
        case Value::Three: return "3";
        case Value::Four: return "4";
        case Value::Five: return "5";
        case Value::Six: return "6";
        case Value::Seven: return "7";
        case Value::Eight: return "8";
        case Value::Nine: return "9";
        case Value::Skip: return "Skip";
        case Value::Reverse: return "Reverse";
        case Value::DrawTwo: return "+2";
        case Value::Wild: return "Wild";
        case Value::WildDrawFour: return "Wild +4";
    }
    return "Unknown";
}

std::string Card::toString() const {
    if (value == Value::Wild || value == Value::WildDrawFour) {
        return valueToString(value);
    }
    return colorToString(color) + " " + valueToString(value);
}

void Card::displayCard() const {
    std::cout << "[ " << toString() << " ]" << std::endl;
}

bool Card::isPlayableOn(const Card& topCard) const {
    return color == topCard.color || value == topCard.value || color == Color::Wild;
}

bool Card::operator==(const Card& o) const {
    return color == o.color && value == o.value;
}

bool Card::operator!=(const Card& o) const {
    return !(*this == o);
}

std::ostream& operator<<(std::ostream& os, const Card& card) {
    os << card.toString();
    return os;
}
