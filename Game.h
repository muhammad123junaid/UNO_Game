#ifndef GAME_H
#define GAME_H

#include <vector>
#include <string>
#include "Deck.h"
#include "Player.h"

namespace UNO {

class Game {
private:
    Deck deck;
    std::vector<Player> players;
    Card topCard;
    int currentPlayer;    // index in players[]
    int direction;        // +1 = clockwise, -1 = counter-clockwise

public:
    // names: list of player names (first one treated as human)
    Game(const std::vector<std::string>& names);

    // Starts the game loop; returns when someone wins or deck empties
    void start();

private:
    // Advance currentPlayer by direction (wraps around)
    void nextPlayer();

    // Display the current top card and (for human) their hand
    void showStateForHuman() const;

    // Handle one player's turn (isHuman==true for player 0)
    void handleTurn(Player& player, bool isHuman);

    // Enforce special-card effects (Skip, Reverse, +2, Wild, +4)
    void applyCardEffect(const Card& played);

    // Prompt human to choose a color for Wild cards (returns a Color enum)
    Color chooseColor() const;
};

} // namespace UNO

#endif // GAME_H
