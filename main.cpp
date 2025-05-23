#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Card.h"
#include "Deck.h"
#include "Player.h"

using namespace UNO;

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    Deck deck;
    deck.shuffle();

    Player player("You");
    Player computer("Computer");

    // Deal initial hands (7 each), but check deck first
    if (deck.cardsRemaining() < 14) {
        std::cerr << "Not enough cards to deal initial hands!\n";
        return 1;
    }
    player.drawInitialCards(deck, 7);
    computer.drawInitialCards(deck, 7);

    // Draw starting card
    if (deck.cardsRemaining() == 0) {
        std::cerr << "Deck is empty before starting!\n";
        return 1;
    }
    Card topCard = deck.draw();
    std::cout << "Starting card: " << topCard << "\n";

    bool playerTurn = true;

    while (true) {
        Player& current = playerTurn ? player : computer;
        std::cout << "\n" << current.getName() << "'s Turn:\n";

        // Show hand if it's the human
        if (playerTurn) {
            std::cout << "Your hand:\n";
            auto& hand = current.getHand();
            for (size_t i = 0; i < hand.size(); ++i)
                std::cout << "  [" << i << "] " << hand[i] << "\n";
        }

        bool played = false;
        auto& hand = current.getHand();

        // Try to play a card from hand
        for (size_t i = 0; i < hand.size(); ++i) {
            if (hand[i].isPlayableOn(topCard)) {
                if (playerTurn) {
                    std::cout << "Playable card at index " << i << ": " << hand[i] << "\n"
                              << "Enter index to play (-1 to draw): ";
                    int choice;
                    std::cin >> choice;
                    if (choice >= 0 && choice < (int)hand.size()
                        && hand[choice].isPlayableOn(topCard)) {
                        topCard = hand[choice];
                        current.playCard(choice);
                        std::cout << "You played: " << topCard << "\n";
                        played = true;
                    } else {
                        std::cout << "Drawing instead...\n";
                    }
                } else {
                    // Simple AI: play first valid
                    topCard = hand[i];
                    current.playCard(i);
                    std::cout << "Computer played: " << topCard << "\n";
                    played = true;
                }
                break;
            }
        }

        // If nobody played, draw a card (if available)
        if (!played) {
            if (deck.cardsRemaining() == 0) {
                std::cout << "Deck is empty—no more draws possible.\nGame ends in a draw.\n";
                break;
            }
            Card drawn = current.drawCard(deck);
            std::cout << current.getName() << " drew: " << drawn << "\n";
            // If the drawn card is playable, auto‐play it
            if (drawn.isPlayableOn(topCard)) {
                topCard = drawn;
                current.playCard(current.getHand().size() - 1);
                std::cout << current.getName()
                          << " immediately played drawn card: " << topCard << "\n";
            }
        }

        // Check for win
        if (current.getHand().empty()) {
            std::cout << current.getName() << " wins!\n";
            break;
        }

        playerTurn = !playerTurn;
    }

    return 0;
}
