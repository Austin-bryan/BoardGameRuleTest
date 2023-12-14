#pragma once
#include <vector>

#include "ConsoleColor.h"
#include "Player.h"

class PlayerMovement;
class Player;

std::string FormatWithCommas(int number);

class LUI
{
public:
    static shared_ptr<LUI> Instance();

    LUI(std::vector<Player>& players, std::shared_ptr<PlayerMovement>&& playerMovement);

    void PrintHeader() const;
    void ShowTurnMenu(Player& player) const;
private:
    static shared_ptr<LUI> instance;
    const string space = "     ";

    void PrintPlayer(const Player& player) const;
    void PrintMoney(const Player& player) const;
    void PrintStamina(const Player& player) const;
    void PadBuffer(const Player& player, int length) const;
    void SpendMoney(Player& player) const;
    void EarnMoney() const;
    void GiveMoney() const;
    void PlayHand() const;
    setc GetSubInfoColors(const Player& player) const;

    std::vector<Player>& players;
    std::shared_ptr<PlayerMovement> playerMovement;
};
