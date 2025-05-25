#include "Game.h"
#include <vector>
#include <string>

int main() {
    std::vector<std::string> names = { "You", "Computer" };

    UNO::Game game(names);
    game.start();

    return 0;
}
