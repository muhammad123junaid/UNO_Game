#include "Game.h"
#include <iostream>
#include <limits>

using namespace UNO;

Game::Game(const std::vector<std::string>& names)
  : currentPlayer(0), direction(1)
{
    deck.shuffle();
    for (auto& n : names) {
        players.emplace_back(n);
        players.back().drawInitialCards(deck, 7);
    }

    do {
        topCard = deck.draw();
    } while (topCard.getValue() == Value::Skip
          || topCard.getValue() == Value::Reverse
          || topCard.getValue() == Value::DrawTwo
          || topCard.getValue() == Value::Wild
          || topCard.getValue() == Value::WildDrawFour);
    std::cout << "Starting card: " << topCard << "\n";
}

void Game::start() {
    while (true) {
        Player& p = players[currentPlayer];
        bool isHuman = (currentPlayer == 0);

        if (isHuman) showStateForHuman();

        handleTurn(p, isHuman);

        if (p.getHand().empty()) {
            std::cout << p.getName() << " wins!\n";
            break;
        }

        nextPlayer();

        if (deck.cardsRemaining() == 0) {
            std::cout << "Deck exhausted. Game ends in a draw.\n";
            break;
        }
    }
}

void Game::nextPlayer() {
    int n = static_cast<int>(players.size());
    currentPlayer = (currentPlayer + direction + n) % n;
}

void Game::showStateForHuman() const {
    std::cout << "\nTop card: " << topCard << "\n";
    auto& hand = players[0].getHand();
    std::cout << "Your hand:\n";
    for (size_t i = 0; i < hand.size(); ++i)
        std::cout << "  [" << i << "] " << hand[i] << "\n";
}

void Game::handleTurn(Player& player, bool isHuman) {
    auto& hand = player.getHand();
    bool played = false;

    for (size_t i = 0; i < hand.size(); ++i) {
        if (hand[i].isPlayableOn(topCard)) {
            if (isHuman) {
                int choice;
                while (true) {
                    std::cout << "Play card [" << i << "] " << hand[i]
                              << "  (or -1 to draw): ";
                    if (!(std::cin >> choice)) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cout << "Invalid input. Please enter a number.\n";
                        continue;
                    }
                    if (choice == -1) break; // draw
                    if (choice >= 0 && choice < static_cast<int>(hand.size())
                        && hand[choice].isPlayableOn(topCard)) {
                        i = choice;
                        break;
                    }
                    std::cout << "Invalid choice. Try again.\n";
                }
                if (choice == -1) break;
            }

            topCard = hand[i];
            player.playCard(static_cast<int>(i));
            std::cout << (isHuman ? "You" : player.getName())
                      << " played " << topCard << "\n";
            applyCardEffect(topCard);
            played = true;
            break;
        }
    }

    if (!played) {
        Card drawn = player.drawCard(deck);
        std::cout << player.getName() << " drew " << drawn << "\n";
        if (drawn.isPlayableOn(topCard)) {
            topCard = drawn;
            player.playCard(static_cast<int>(hand.size()) - 1);
            std::cout << player.getName() << " immediately played " << topCard << "\n";
            applyCardEffect(topCard);
        }
    }
}

void Game::applyCardEffect(const Card& played) {
    switch (played.getValue()) {
        case Value::Skip:
            std::cout << "Next player is skipped!\n";
            nextPlayer();
            break;
        case Value::Reverse:
            direction = -direction;
            std::cout << "Play direction reversed!\n";
            break;
        case Value::DrawTwo:
            nextPlayer();
            std::cout << players[currentPlayer].getName() << " draws 2 cards.\n";
            players[currentPlayer].drawCard(deck);
            players[currentPlayer].drawCard(deck);
            break;
        case Value::Wild: {
            Color c = chooseColor();
            topCard = Card(c, Value::Wild);
            std::cout << "Wild color chosen: " << Card::colorToString(c) << "\n";
            break;
        }
        case Value::WildDrawFour: {
            Color c = chooseColor();
            topCard = Card(c, Value::WildDrawFour);
            nextPlayer();
            std::cout << players[currentPlayer].getName() << " draws 4 cards.\n";
            for (int i = 0; i < 4; ++i)
                players[currentPlayer].drawCard(deck);
            std::cout << "Color chosen: " << Card::colorToString(c) << "\n";
            break;
        }
        default:
            break;
    }
}

Color Game::chooseColor() const {
    std::cout << "Choose a color: 0=Red,1=Green,2=Blue,3=Yellow: ";
    int c;
    while (!(std::cin >> c) || c < 0 || c > 3) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid. Enter 0-3: ";
    }
    return static_cast<Color>(c);
}
