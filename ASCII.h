#ifndef ASCII_H
#define ASCII_H

#include "Card.hpp"
#include <vector>
#include <string>
#include <iostream>

namespace UNO
{

    class ASCIIArt
    {
    public:
        static void renderCardBox(const Card &card, size_t index = static_cast<size_t>(-1));
        static void renderGameState(const Card &topCard, const std::vector<Card> &hand);
        static void printWinBanner();
        static void printLoseBanner();
        static void printStartingCard(const Card &card);
    };

}
#endif
