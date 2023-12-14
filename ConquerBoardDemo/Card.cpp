#include <cstdlib>
#include "Card.h"
#include "LUI.h"

void PrintSuit(ECardSuit suit)
{
    short foreground, background;
    GetConsoleColors(suit, foreground, background);
    cout << setc(foreground, background) << " " << to_string(suit) << " " << setc();
}

Card::Card(int cardSuit): cardSuit{ (ECardSuit)cardSuit }
{ }
Card::Card(ECardSuit cardSuit): cardSuit{ cardSuit }
{ }
ECardSuit Card::CardSuit() const
{ return cardSuit; }

Card Card::GetCard()
{
    return Card((ECardSuit)(rand() % 6));
}
std::ostream& operator<<(std::ostream& os, const Card& card)
{
    PrintSuit(card.Suit());
    return os;
}
ECardSuit Card::Suit() const
{ return cardSuit; }

int Card::Len() const
{ return (int)to_string(cardSuit).length(); }
