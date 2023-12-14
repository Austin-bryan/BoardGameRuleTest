#pragma once

#include <string>

enum class ECardSuit { Dice, Stop, Opponent, Up, Down, Cash };
const int HAND_SIZE = 6;

inline std::string to_string(ECardSuit suit)
{
    switch (suit)
    {
    case ECardSuit::Dice:     return "Dice";
    case ECardSuit::Opponent: return "Opponent";
    case ECardSuit::Stop:     return "Stop";
    case ECardSuit::Cash:     return "Cash";
    case ECardSuit::Up:       return "Up";
    case ECardSuit::Down:     return "Down";
    }
    return "";
}
void PrintSuit(ECardSuit suit);

class Card
{
public:
    explicit Card(int cardSuit);
    explicit Card(ECardSuit cardSuit);
    ECardSuit CardSuit() const;

    static Card GetCard();
    friend std::ostream& operator<<(std::ostream& os, const Card& card);
    ECardSuit Suit() const;
    int Len() const;

private:
    ECardSuit cardSuit;
};
