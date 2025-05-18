#include "Card.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace UNO;

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Card c1(static_cast<Color>(std::rand() % 5), static_cast<Value>(std::rand() % 15));
    Card c2(static_cast<Color>(std::rand() % 5), static_cast<Value>(std::rand() % 15));

    std::cout << "Card 1: " << c1 << std::endl;
    std::cout << "Card 2: " << c2 << std::endl;

    std::cout << "Is c2 playable on c1? " << (c2.isPlayableOn(c1) ? "Yes" : "No") << std::endl;

    return 0;
}
