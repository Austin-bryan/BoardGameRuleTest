#pragma once
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>
#include <vector>

#include "Card.h"
#include "CardPlay.h"

class Player;
using namespace std;

class Hand
{
public:
    Hand(Player* player);
    friend std::ostream& operator<<(std::ostream& os, const Hand& hand);

    CardPlay GetPlay() const;
private:
    std::vector<Card> cards;
    Player* owner;
    
    void GetCard(int& cardIndex, std::vector<int>& usedCardsIndexes, const Card*& card) const;
    void GetCards(const Card* cardA, const Card* cardB, const Card* cardC) const;
    void FindValidPlays(std::vector<CardPlay> cardPlays) const;
    CardPlay MakeCustomPlay() const; 
};
