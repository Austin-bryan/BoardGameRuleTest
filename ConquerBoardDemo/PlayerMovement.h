#pragma once
#include "ConsoleColor.h"

class PlayerMovement
{
public:
    virtual ~PlayerMovement() = default;
    virtual void Move() = 0;
};

class DiceMovement : public PlayerMovement
{
public:
    void Move() override;
private:
    int GetMoveDifference(int stamina, int roll) const;
};

class SelectionMovement : public PlayerMovement
{
    
};