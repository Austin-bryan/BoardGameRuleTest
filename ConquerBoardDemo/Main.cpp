#include <iostream>
#include <vector>
#include <windows.h>

#include "LUI.h"
#include "Player.h"
#include "PlayerMovement.h"
#include "ConsoleColor.h"
#include "InputFunctions.h"
using namespace std;

void Foo()
{
    // system("chcp 65001");
    cout << "□, ↑, ↓, ○, ⯃, $" << endl;
}

int main()
{
    cout.imbue(std::locale(""));
    srand(time(0));
    ResetConsoleColor();

    // cout << "---- Pregame settings menu ----";
    // cout << "Enter dice or no dice"

    int playerCount = GetInt("How many players?", "Player count must be greater than two", [&](int input) { return input < 2; });

    vector<Player> players;
    players.reserve(playerCount);
    
    for (int i = 0; i < playerCount; i++)
        players.emplace_back();
    int currentPlayer = 0;

    system("cls");
    LUI lui = { players, make_shared<DiceMovement>() };

    while (true)
    {
        system("cls");
        Player::ActivePlayer = &players[currentPlayer];
        lui.PrintHeader();

        cout << players[currentPlayer];
        lui.ShowTurnMenu(players[currentPlayer]);

        cout << endl;
        WaitForUserInput("Press any key to end your turn");

        currentPlayer++;
        currentPlayer %= players.size();
    }

    return 0;
}
