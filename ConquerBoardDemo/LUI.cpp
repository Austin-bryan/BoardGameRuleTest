#include "LUI.h"
#include "ConsoleColor.h"
#include "PlayerMovement.h"
#include "InputFunctions.h"

std::string FormatWithCommas(int number)
{
    std::string numberWithCommas = std::to_string(number);

    int numDigits = numberWithCommas.length();
    int numCommas = (numDigits - 1) / 3;

    for (int i = 1; i <= numCommas; ++i) {
        int commaPosition = numDigits - i * 3;
        numberWithCommas.insert(commaPosition, ",");
    }

    return numberWithCommas;
}

shared_ptr<LUI> LUI::instance;

// Last sesh: THere is an apparent copy being made that prevents the changes in amount of money from showing when player spends moeny
LUI::LUI(std::vector<Player>& players, std::shared_ptr<PlayerMovement>&& playerMovement) : players{ players }, playerMovement{ std::move(playerMovement) }
{
    instance = make_shared<LUI>(*this);
}

void LUI::ShowTurnMenu(Player& player) const
{
    const int MAX_SELECTION = 6;
    int menuSelection = GetInt("\nWhat do you want to do?\n1. Make a move (ends turn)\n2. Spend Money\n3. Earn Money\n4. Give money to another player\n5. Play hand\n6. Make a trade offer\n",
        "Input must be between 1 and " + to_string(MAX_SELECTION),
        [&](int input) { return input < 1 || input > MAX_SELECTION; });
    
    switch (menuSelection)
    {
    case 1: playerMovement->Move(); break;
    case 2: SpendMoney(player); break;
    case 3: EarnMoney(); break;
    case 4: GiveMoney(); break;
    case 5: PlayHand(); break;
    default: break;
    }
}
void LUI::PrintHeader() const
{
    system("cls");
    for (auto& player : players)
        PrintPlayer(player);
    cout << endl;
    for (const auto& player : players)
        PrintMoney(player);
    cout << endl;
    for (const auto& player : players)
        PrintStamina(player);
}
void LUI::PrintPlayer(const Player& player) const
{
    cout << setc(F_WHITE, player.background) << space << player.name << space << setc() << " ";
}
void LUI::PrintMoney(const Player& player) const
{
    string money = FormatWithCommas(player.Money());
    
    cout << GetSubInfoColors(player) << "$" << money;
    PadBuffer(player, money.length() + 1);
    cout << " ";
}
void LUI::PrintStamina(const Player& player) const
{
    cout << GetSubInfoColors(player) << "Stamina: " << player.stamina;
    PadBuffer(player, string("stamina: ").length() + to_string(player.stamina).length());
    cout << " ";
}
void LUI::PadBuffer(const Player& player, int length) const
{
    int titleLength = space.length() * 2 + player.name.length();
    for (int i = 0; i < titleLength - length; i++)
        cout << " ";
    cout << setc();
}
void LUI::SpendMoney(Player& player) const
{
    PrintHeader();
    cout << endl << endl; 

    int amount = GetInt("How much are you going to spend?", "Money amount must be greater than 1 or less than $" + to_string(player.money),
        [&](int input){ return input < 1 || input > player.Money(); });

    player.Spend(amount);
    PrintHeader();

    cout << endl << endl << "You have $" << player.Money() << " remaining. " << endl << endl;
    WaitForUserInput("Press any key to return to turn menu");

    PrintHeader();
    cout << player;
    ShowTurnMenu(player);
}
void LUI::EarnMoney() const
{
    PrintHeader();
    int amount = GetInt("\n\nEnter the amount of money you earned:", "Number must be positive", [](int input){ return input < 0; });
    Player::ActivePlayer->Earn(amount);

    cout << endl << "You now have $" << Player::ActivePlayer->Money() << endl;
    WaitForUserInput();

    PrintHeader();
    cout << *Player::ActivePlayer;
    ShowTurnMenu(*Player::ActivePlayer);
}
void LUI::GiveMoney() const
{
    PrintHeader();
    int amount = GetInt("\n\nEnter the amount of money you gave to another player:", "Number must be positive and less than the amount of money you have",
        [](int input) { return input < 0 || input > Player::ActivePlayer->Money(); });

    Player* other;

    if (players.size() == 2)
        other = players[0] == *Player::ActivePlayer ? &players[1] : &players[0];
    else
    {
        int buffer = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i] == *Player::ActivePlayer)
                 buffer++;
            else cout << i + 1 - buffer << ": " << players[i].name << endl;
        }
        int playerChoice = GetInt("", "Number must be between 1 and " + to_string(players.size()), [&](int input) { return input < 0 || input > players.size(); });
        other = &players[playerChoice];
    }

    Player::ActivePlayer->Spend(amount);
    other->Earn(amount);

    PrintHeader();

    cout << endl << endl << Player::ActivePlayer->name << " now has $" << Player::ActivePlayer->Money();
    cout << endl << other->name << " now has $" << other->Money();

    cout << endl << endl;

    WaitForUserInput();

    PrintHeader();
    cout << *Player::ActivePlayer;
    ShowTurnMenu(*Player::ActivePlayer);
}
void LUI::PlayHand() const
{
    auto cardPlay = Player::ActivePlayer->GetPlay();

    PrintHeader();
    cout << endl << endl;

    cout << "You have selected " << cardPlay.Title();
}
setc LUI::GetSubInfoColors(const Player& player) const
{
    // cout << (Player::ActivePlayer == nullptr);
    // return setc(player.foreground);
    return *Player::ActivePlayer == player ? setc(F_WHITE, player.background) : setc(player.foreground);
}

shared_ptr<LUI> LUI::Instance()
{ return instance; }
