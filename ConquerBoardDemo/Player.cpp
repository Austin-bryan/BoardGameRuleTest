#include <iostream>
#include "Player.h"
#include <windows.h>

#include "ConsoleColor.h"
#include "Hand.h"

int Player::PlayerIndex = 0;
std::vector<Player> Player::Players;
Player* Player::ActivePlayer;

Player::Player() : hand{ make_unique<Hand>(this) }, playerIndex{ ++PlayerIndex }
{
    cout << "Enter player name: ";
    cin >> name;

    GetConsoleColors(playerIndex, foreground, background);
}
CardPlay Player::GetPlay() const
{
    return hand->GetPlay();
}
std::ostream& operator<<(std::ostream& os, const Player& player)
{
    os << endl << endl << setc(F_WHITE, player.background) << " " << player.name << ", its your turn! " << setc() << endl;

    cout << *player.hand;
    return os;
}
