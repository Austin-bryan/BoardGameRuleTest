#pragma once
#include "windows.h"
#include <iostream>

#include "Card.h"

#define F_BLACK FOREGROUND_INTENSITY
#define F_GREEN (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define F_RED (FOREGROUND_RED | FOREGROUND_INTENSITY)
#define F_BLUE (FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define F_ORANGE (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define F_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY)
#define F_CYAN (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY)
#define F_WHITE (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY)

#define B_BLACK 0x0
#define B_GREEN (BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define B_RED (BACKGROUND_RED | BACKGROUND_INTENSITY)
#define B_BLUE (BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define B_ORANGE (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define B_PURPLE (BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define B_CYAN (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY)
#define B_WHITE (BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY)

enum class TextColor { Black, Red, Green, Blue, Orange, Cyan, Purple, White };

const HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

inline short ToForeground(TextColor textColor)
{
    switch (textColor)
    {
    case TextColor::Black:   return F_BLACK;
    case TextColor::Red:     return F_RED;
    case TextColor::Green:   return F_GREEN;
    case TextColor::Blue:    return F_BLUE;
    case TextColor::Orange:  return F_ORANGE;
    case TextColor::Cyan:    return F_CYAN;
    case TextColor::Purple:  return F_PURPLE;
    case TextColor::White:   return F_WHITE;
    }
    return 0;
}
inline short ToBackground(TextColor textColor)
{
    switch (textColor)
    {
    case TextColor::Black:   return B_BLACK;
    case TextColor::Red:     return B_RED;
    case TextColor::Green:   return B_GREEN;
    case TextColor::Blue:    return B_BLUE;
    case TextColor::Orange:  return B_ORANGE;
    case TextColor::Cyan:    return B_CYAN;
    case TextColor::Purple:  return B_PURPLE;
    case TextColor::White:   return B_WHITE;
    }
    return 0;
}

inline void SetConsoleColor(TextColor foreground, TextColor background = TextColor::Black)
{
    SetConsoleTextAttribute(hConsole, ToForeground(foreground) | ToBackground(background));
}
inline void SetConsoleColor(short foreground, short background = B_BLACK)
{
    SetConsoleTextAttribute(hConsole, foreground | background);
}
inline void GetConsoleColors(int index, short& foreground, short& background)
{
    switch(index)
    {
    case 1: foreground  = F_BLUE;   background = B_BLUE;   break;
    case 2: foreground  = F_RED;    background = B_RED;    break;
    case 3: foreground  = F_GREEN;  background = B_GREEN;  break;
    case 4: foreground  = F_PURPLE; background = B_PURPLE; break;
    case 5: foreground  = F_ORANGE; background = B_ORANGE; break;
    case 6: foreground  = F_CYAN;   background = B_CYAN;   break;
    default: foreground = F_WHITE;  background = B_BLACK;  break;
    }
}
inline void GetConsoleColors(ECardSuit cardSuit, short& foreground, short& background)
{
    switch(cardSuit)
    {
    case ECardSuit::Cash:     foreground  = F_WHITE; background = B_GREEN;  break;
    case ECardSuit::Dice:     foreground  = F_BLACK; background = B_WHITE;  break;
    case ECardSuit::Up:       foreground  = F_WHITE; background = B_BLUE;   break;
    case ECardSuit::Down:     foreground  = F_WHITE; background = B_PURPLE; break;
    case ECardSuit::Opponent: foreground  = F_WHITE; background = B_ORANGE; break;
    case ECardSuit::Stop:     foreground  = F_WHITE; background = B_RED;    break;
    }
}
inline void ResetConsoleColor()
{
    SetConsoleColor(F_WHITE, B_BLACK);   
}

class setc
{
public:
    setc(short foreground = F_WHITE, short background = B_BLACK) : foreground{ foreground }, background{ background }
    {
        
    }
    friend std::ostream& operator<<(std::ostream& os, const setc& obj)
    {
        SetConsoleColor(obj.foreground, obj.background);
        return os;
    }
    short foreground, background;
};