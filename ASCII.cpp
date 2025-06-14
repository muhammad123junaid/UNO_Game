#include "ASCII.hpp"
#include <algorithm>

namespace UNO
{

    static std::string getColorCode(Color color)
    {
        switch (color)
        {
        case Color::Red:
            return "\033[31m"; // Red
        case Color::Green:
            return "\033[32m"; // Green
        case Color::Blue:
            return "\033[34m"; // Blue
        case Color::Yellow:
            return "\033[33m"; // Yellow
        case Color::Wild:
            return "\033[35m"; // Magenta
        default:
            return "\033[0m"; // Reset
        }
    }
    static std::string resetColor()
    {
        return "\033[0m";
    }

    void ASCIIArt::renderCardBox(const Card &card, size_t index)
    {
        std::string colorName = Card::colorToString(card.getColor());
        std::string valueStr = Card::valueToString(card.getValue());

        size_t innerWidth = std::max({colorName.size(), valueStr.size()}) + 4;

        std::string border;
        if (index != static_cast<size_t>(-1))
        {
            std::string idxStr = "[" + std::to_string(index) + "]";
            size_t totalDashes = innerWidth;
            size_t leftDashes = (totalDashes - idxStr.size()) / 2;
            size_t rightDashes = totalDashes - idxStr.size() - leftDashes;

            border = "+" + std::string(leftDashes, '-') + idxStr + std::string(rightDashes, '-') + "+";
        }
        else
        {
            border = "+" + std::string(innerWidth, '-') + "+";
        }

        std::string emptyLine = "|" + std::string(innerWidth, ' ') + "|";
        std::string topColorLine = "|  " + colorName + std::string(innerWidth - 2 - colorName.size(), ' ') + "|";
        size_t padLeft = (innerWidth - valueStr.size()) / 2;
        size_t padRight = innerWidth - valueStr.size() - padLeft;
        std::string valueLine = "|" + std::string(padLeft, ' ') + valueStr + std::string(padRight, ' ') + "|";
        std::string bottomColorLine = "|" + std::string(innerWidth - 2 - colorName.size(), ' ') + colorName + "  |";

        std::cout << getColorCode(card.getColor());
        std::cout << border << "\n";
        std::cout << topColorLine << "\n";
        std::cout << emptyLine << "\n";
        std::cout << valueLine << "\n";
        std::cout << emptyLine << "\n";
        std::cout << bottomColorLine << "\n";
        std::cout << border << resetColor() << "\n";
    }

    void ASCIIArt::renderGameState(const Card &topCard, const std::vector<Card> &hand)
    {
        std::cout << "\nTop Card:" << std::endl;
        renderCardBox(topCard);

        std::cout << "Your Hand:" << std::endl;

        std::vector<std::vector<std::string>> cardLines;

        for (size_t i = 0; i < hand.size(); ++i)
        {
            const Card &card = hand[i];
            std::string colorName = Card::colorToString(card.getColor());
            std::string valueStr = Card::valueToString(card.getValue());

            size_t innerWidth = std::max({colorName.size(), valueStr.size()}) + 4;

            std::string idxStr = "[" + std::to_string(i) + "]";
            size_t totalDashes = innerWidth;
            size_t leftDashes = (totalDashes - idxStr.size()) / 2;
            size_t rightDashes = (totalDashes - idxStr.size()) - leftDashes;
            std::string border = "+" + std::string(leftDashes, '-') + idxStr + std::string(rightDashes, '-') + "+";

            std::string emptyLine = "|" + std::string(innerWidth, ' ') + "|";
            std::string topColorLine = "|  " + colorName + std::string(innerWidth - 2 - colorName.size(), ' ') + "|";
            size_t padLeft = (innerWidth - valueStr.size()) / 2;
            size_t padRight = innerWidth - valueStr.size() - padLeft;
            std::string valueLine = "|" + std::string(padLeft, ' ') + valueStr + std::string(padRight, ' ') + "|";
            std::string bottomColorLine = "|" + std::string(innerWidth - 2 - colorName.size(), ' ') + colorName + "  |";

            std::vector<std::string> lines = {
                getColorCode(card.getColor()) + border + resetColor(),
                getColorCode(card.getColor()) + topColorLine + resetColor(),
                getColorCode(card.getColor()) + emptyLine + resetColor(),
                getColorCode(card.getColor()) + valueLine + resetColor(),
                getColorCode(card.getColor()) + emptyLine + resetColor(),
                getColorCode(card.getColor()) + bottomColorLine + resetColor(),
                getColorCode(card.getColor()) + border + resetColor()};

            cardLines.push_back(lines);
        }

        for (size_t line = 0; line < 7; ++line)
        {
            for (const auto &card : cardLines)
            {
                std::cout << card[line] << "  ";
            }
            std::cout << "\n";
        }
    }

    void ASCIIArt::printStartingCard(const Card &card)
    {
        std::string color = "\033[1;35m";
        std::string reset = "\033[0m";
        std::cout << color << R"(
    
   _____   _                    _     _                      _____                      _       
  / ____| | |                  | |   (_)                    / ____|                    | |    _ 
 | (___   | |_    __ _   _ __  | |_   _   _ __     __ _    | |        __ _   _ __    __| |   (_)
  \___ \  | __|  / _` | | '__| | __| | | | '_ \   / _` |   | |       / _` | | '__|  / _` |      
  ____) | | |_  | (_| | | |    | |_  | | | | | | | (_| |   | |____  | (_| | | |    | (_| |    _ 
 |_____/   \__|  \__,_| |_|     \__| |_| |_| |_|  \__, |    \_____|  \__,_| |_|     \__,_|   (_)
                                                   __/ |                                        
                                                  |___/                                         

    )" << reset;
        std::cout << std::endl;
        renderCardBox(card);
    }
    void ASCIIArt::printWinBanner()
    {
        std::string color = "\033[1;35m";
        std::string reset = "\033[0m";
        std::cout << color << R"(
 __     __                   __          __  _                   _ 
 \ \   / /                   \ \        / / (_)                 | |
  \ \_/ /    ___    _   _     \ \  /\  / /   _   _ __    ___    | |
   \   /    / _ \  | | | |     \ \/  \/ /   | | | '_ \  / __|   | |
    | |    | (_) | | |_| |      \  /\  /    | | | | | | \__ \   |_|
    |_|     \___/   \__,_|       \/  \/     |_| |_| |_| |___/   (_)
                                                                   
                                                                   

)" << reset << std::endl;
    }

    void ASCIIArt::printLoseBanner()
    {
        std::string color = "\033[1;35m";
        std::string reset = "\033[0m";
        std::cout <<color<< R"(

   _____                                       _                    __          __  _                   _ 
  / ____|                                     | |                   \ \        / / (_)                 | |
 | |        ___    _ __ ___    _ __    _   _  | |_    ___   _ __     \ \  /\  / /   _   _ __    ___    | |
 | |       / _ \  | '_ ` _ \  | '_ \  | | | | | __|  / _ \ | '__|     \ \/  \/ /   | | | '_ \  / __|   | |
 | |____  | (_) | | | | | | | | |_) | | |_| | | |_  |  __/ | |         \  /\  /    | | | | | | \__ \   |_|
  \_____|  \___/  |_| |_| |_| | .__/   \__,_|  \__|  \___| |_|          \/  \/     |_| |_| |_| |___/   (_)
                              | |                                                                         
                              |_|                                                                         

                                                                                                                  

)" <<reset<< std::endl;
    }
}
