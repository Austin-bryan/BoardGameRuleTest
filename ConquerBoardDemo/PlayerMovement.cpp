#include "PlayerMovement.h"

#include "LUI.h"

void DiceMovement::Move()
{
    system("cls");
    LUI::Instance()->PrintHeader();
    cout << endl << endl;

    /*
     * 10 -> 0
     * 9 -> 0
     * 8 -> 0
     * 7 -> 0
     * 6 -> 0
     * 5 -> 1
     * 4 -> 2
     * 3 -> 3
     * 2 -> 3
     * 1 -> 3
     * 0 -> 4
     */

    int rollAmount = rand() % 6 + 1;
    int moveDifference = GetMoveDifference(Player::ActivePlayer->Stamina(), rollAmount);
    moveDifference = min(3, moveDifference);

    if (moveDifference == 0)
         cout << "You rolled a " << rollAmount << "!";
    else
    {
        cout << "You rolled a " << rollAmount << " but you lost " << moveDifference << " spaces because of your stamina. ";
        rollAmount -= moveDifference;
        cout << endl << "You will move " << rollAmount << " spaces";
    }

    Player::ActivePlayer->ConsumeStamina();
}
int DiceMovement::GetMoveDifference(int stamina, int roll) const
{
    if (stamina > 5)
        return 0;
    if (stamina == 0)
        return 2;
    return 6 - stamina;
}
