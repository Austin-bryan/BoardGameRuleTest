#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>

#include "Card.h"

class CardPlay
{
public:
    static std::map<std::vector<ECardSuit>, CardPlay> Plays;
    CardPlay(std::string title, std::string description, std::function<void()> func);
    CardPlay() = default;

    void Execute() const;
    std::string Title() const;
    std::string Description() const;

    bool operator==(const CardPlay& rhs) const;
    bool operator!=(const CardPlay& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const CardPlay& cardPlay);
private:
    std::string title;
    std::string description;
    std::function<void()> play;
};

inline bool CompareCardPlaysByTitle(const CardPlay& lhs, const CardPlay& rhs)
{
    return lhs.Title() < rhs.Title();
}