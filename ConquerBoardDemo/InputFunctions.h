#pragma once
#include <functional>
#include <iostream>
#include "ConsoleColor.h"
using namespace std;

inline int GetInt(const string& message, const string& error, const function<bool(int)>& inputIsInvalid)
{
    cout << message << " ";

    int input;
    cin >> input;

    while (inputIsInvalid(input))
    {
        cout << setc(F_RED) << "Error: " << error << ". Try again: " << setc();
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> input;
    }

    return input;
}
inline void WaitForUserInput(const string& message = "Press any key to continue")
{
    cout << message << "... ";
    char buffer;
    cin >> buffer;
}