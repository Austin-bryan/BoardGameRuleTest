#pragma once
#include <string>
#include <memory>
#include "Hand.h"

class Hand;
using namespace std;

class Player
{
    friend class LUI;
public:
    static Player* ActivePlayer;
    static std::vector<Player> Players;

    Player();
    ~Player() = default;
    Player(const Player& other)
        : name(other.name), playerIndex(other.playerIndex), foreground{ other.foreground }, background{ other.background }
    {
        hand = std::make_unique<Hand>(*other.hand);
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player);
    friend bool operator ==(const Player& lhs, const Player& rhs) { return lhs.name == rhs.name; }
    friend bool operator !=(const Player& lhs, const Player& rhs) { return !(lhs == rhs); }

    CardPlay GetPlay() const;
    int Money()      const { return money; }
    int Stamina()    const { return stamina; }
    int Foreground() const { return foreground; }
    int Background() const { return background; }

    void Spend(int amount) { if (amount < money && amount > 0) money -= amount; }
    void Earn(int amount) { money += amount; }
    void ConsumeStamina()
    {
        stamina--;
        stamina = max(3, stamina);
    }
private:
    static int PlayerIndex;
    std::string name;
    std::unique_ptr<Hand> hand;

    const int MAX_STAMINA = 10;
    int money = 10000;
    int stamina = MAX_STAMINA;
    
    int playerIndex = 0;
    short foreground, background;
};

