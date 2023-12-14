#include "Hand.h"

#include "ConsoleColor.h"
#include "InputFunctions.h"
#include "LUI.h"
#include "Player.h"

std::vector<std::vector<ECardSuit>> GeneratePermutations(const Card* cardA, const Card* cardB, const Card* cardC)
{
    std::vector<std::vector<ECardSuit>> permutations;
    std::vector<ECardSuit> suits = { cardA->CardSuit() };

    if (cardB != nullptr)
        suits.push_back(cardB->CardSuit());
    if (cardC != nullptr)
        suits.push_back(cardC->CardSuit());
    
    std::sort(suits.begin(), suits.end());
    
    do permutations.push_back(suits);
    while (std::next_permutation(suits.begin(), suits.end()));

    return permutations;
}
bool IsPermutationInCardPlays(const std::vector<std::vector<ECardSuit>>& permutations, std::vector<ECardSuit>& validPermutation)
{
    for (const auto& permutation : permutations) 
        if (CardPlay::Plays.find(permutation) != CardPlay::Plays.end())
        {
            validPermutation = permutation;
            return true;
        }
    return false;
}


Hand::Hand(Player* player): owner { player }
{
    for (int i = 0; i < HAND_SIZE; i++)
        cards.emplace_back(rand() % 6);
}

CardPlay Hand::GetPlay() const
{
    LUI::Instance()->PrintHeader();
    std::cout << endl << endl << setc(F_WHITE, B_ORANGE) << " Suggested card plays: " << setc() << endl;

    std::vector<CardPlay> suggestedPlays;
    FindValidPlays(suggestedPlays);

    int selection = GetInt("", "Input must be between 0 and " + to_string(suggestedPlays.size()), [&](int input) { return input < 0 || input > suggestedPlays.size(); });

    if (selection == 0)
        return MakeCustomPlay();
    return suggestedPlays[selection - 1];
}
CardPlay Hand::MakeCustomPlay() const
{
    LUI::Instance()->PrintHeader();
    cout << endl;
    
    cout << endl;
    for (int i = 0; i < cards.size(); i++)
        cout << i << ": " << cards[i] << endl;
    cout << "Enter up to 3 numbers, or enter -1 when finished." << endl;

    const Card *cardA = nullptr, *cardB = nullptr, *cardC = nullptr;
    GetCards(cardA, cardB, cardC);

    std::vector<ECardSuit> validPermutation;
    auto permutations = GeneratePermutations(cardA, cardB, cardC);
    bool isValidPlay = IsPermutationInCardPlays(permutations, validPermutation);

    LUI::Instance()->PrintHeader();

    cout << validPermutation.size() << ", " << (isValidPlay ? "true" : "false") << endl;
    cout << endl << setc(F_ORANGE) << "Selected: " << setc();

    for (int i = 0; i < permutations[0].size(); i++)
    {
        PrintSuit(permutations[0][i]);
        cout << (i == permutations[0].size() - 1 ? "" : ", ");
    }

    if (isValidPlay)
         cout << endl << setc(F_WHITE, B_ORANGE) << CardPlay::Plays[validPermutation];
    else cout << " is not a valid play.";

    int finishPlayOption = GetInt("\n\nWould you like to pick a different hand?\n1. Yes, back to Custom Menu Menu\n2. Yes, back to Suggestions Menu\n3. No", "Choice must be 1 - 3", [](int input) { return input || input > 3; });
    if (finishPlayOption == 1)
        return MakeCustomPlay();
    if (finishPlayOption == 2)
    {
        LUI::Instance()->PrintHeader();
        cout << endl;
    
        return GetPlay();
    }
    else return CardPlay::Plays[validPermutation];
}
void Hand::GetCard(int& cardIndex, std::vector<int>& usedCardsIndexes, const Card*& card) const
{
    cin >> cardIndex;
    int count = 0;
    do
    {
        if (count > 1)
            cout << "Error: This cardIndex as already been used. Pick another cardIndex: ";
        while (cardIndex < -1 || cardIndex > HAND_SIZE)
        {
            cout << setc(F_RED) << "Error: Input cannot be -1 and or greater than " << HAND_SIZE << ". Try again: " << setc();
            cin >> cardIndex;
        }
        count++;
    } while (std::find(usedCardsIndexes.begin(), usedCardsIndexes.end(), cardIndex) != usedCardsIndexes.end());

    if (cardIndex == -1)
        return;
    usedCardsIndexes.push_back(cardIndex);
    card = &cards[cardIndex];
}
void Hand::GetCards(const Card* cardA, const Card* cardB, const Card* cardC) const
{
    std::vector<int> usedCards;
    int cardIndexA;

    GetCard(cardIndexA, usedCards, cardA);
    if (cardIndexA != -1)
    {
        int cardIndexC, cardIndexB;
        GetCard(cardIndexB, usedCards, cardB);
        if (cardIndexB != -1)
            GetCard(cardIndexC, usedCards, cardC);
    }
}
void Hand::FindValidPlays(std::vector<CardPlay> cardPlays) const
{
    for (auto i : cards)
        for (auto j : cards)
            for (auto k : cards)
            {
                std::vector<ECardSuit> playCombination = { i.Suit(), j.Suit(), k.Suit() };

                auto it = CardPlay::Plays.find(playCombination);
                if (it != CardPlay::Plays.end() &&
                    std::find(cardPlays.begin(), cardPlays.end(), it->second) == cardPlays.end() &&
                    cardPlays.size() < 5)
                    cardPlays.push_back(it->second);
            }
    sort(cardPlays.begin(), cardPlays.end(), CompareCardPlaysByTitle);

    cout << "0: " << setc(F_ORANGE) << "Custom Play" << setc() << endl;
    for (int i = 0; i < cardPlays.size(); i++)
        std::cout << i + 1 << ": " << setc(F_ORANGE) << cardPlays[i].Title() << setc() << ": " << cardPlays[i].Description() << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Hand& hand)
{
    os << setc(hand.owner->Foreground()) << "Your Hand: " << setc();

    for (int i = 0; i < HAND_SIZE; i++)
        os << hand.cards[i] << (i < HAND_SIZE - 1 ? ", " : "\n");
    return os;
}
