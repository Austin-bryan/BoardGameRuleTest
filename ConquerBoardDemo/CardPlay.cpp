#include "CardPlay.h"
#include "ConsoleColor.h"

#define ECS ECardSuit

std::map<std::vector<ECardSuit>, CardPlay> CardPlay::Plays =
{
    { { ECS::Up }, { "Roll Booster", "Add 0, 1 or 2 to your roll.", []{ } } },
    { { ECS::Down }, { "Roll Reducer", "Add 0, -1 or -2 to your roll.", []{ } } },
    { { ECS::Dice }, { "Advantage", "Roll two dice, and pick the larger number.", []{ } } },
    { { ECS::Stop }, { "Skip Turn", "Voluntarily skip a turn.", []{ } } },
    { { ECS::Cash }, { "Cash Infusion", "Earn $100 for immediate use.", []{ } } },
    { { ECS::Up, ECS::Up }, { "Double Boost", "Add 0 to 4 to your roll.", []{ } } },
    { { ECS::Up, ECS::Down }, { "Mixed Boost", "Add -2 to 2 to your roll.", []{ } } },
    { { ECS::Up, ECS::Opponent }, { "Boost Opponent", "Add 0 to 2 to opponent's next roll.", []{ } } },
    { { ECS::Up, ECS::Dice }, { "Enhanced Roll", "Roll a D12.", []{ } } },
    { { ECS::Up, ECS::Cash }, { "Profit Increase", "Increase money earned for 2 turns.", []{ } } },
    { { ECS::Down, ECS::Opponent }, { "Reduce Opponent", "Add -2 to 0 to opponent's next roll.", []{ } } },
    { { ECS::Down, ECS::Dice }, { "Dice Restriction", "Roll a D4.", []{ } } },
    { { ECS::Down, ECS::Stop }, { "Stun Be Gone", "Immune to stuns for 3 turns.", []{ } } },
    { { ECS::Down, ECS::Cash }, { "Fee Relief", "Decrease amount of fees paid for 2 turns.", []{ } } },
    { { ECS::Opponent, ECS::Opponent }, { "Opponent Swap", "Swap positions with two opponents.", []{ } } },
    { { ECS::Opponent, ECS::Dice }, { "Disadvantage Opponent", "Force opponent to roll with disadvantage.", []{ } } },
    { { ECS::Opponent, ECS::Stop }, { "Stun Opponent", "Stun 1 opponent for 1 turn.", []{ } } },
    { { ECS::Opponent, ECS::Cash }, { "Debt Collector", "Collect $100 from opponent.", []{ } } },
    { { ECS::Dice, ECS::Dice }, { "Double Roll", "Roll two dice.", []{ } } },
    { { ECS::Dice, ECS::Stop }, { "Re-Roll", "Roll with the option to re-roll.", []{ } } },
    { { ECS::Dice, ECS::Cash }, { "Fortune Roll", "Gain money based on how high you roll.", []{ } } },
    { { ECS::Stop, ECS::Stop }, { "Double Skip", "Skip two turns.", []{ } } },
    { { ECS::Stop, ECS::Cash }, { "Fee Vacation", "Pay no fees for 1 turn.", []{ } } },
    { { ECS::Cash, ECS::Cash }, { "Big Earnings", "Earn $400.", []{ } } },
    { { ECS::Up, ECS::Up, ECS::Up }, { "Triple Boost", "Add 0 to 6 to your roll.", []{ } } },
    { { ECS::Up, ECS::Up, ECS::Down }, { "Mixed Boost", "Add -2 to 4 to your roll.", []{ } } },
    { { ECS::Up, ECS::Up, ECS::Opponent }, { "Mixed Boost Opponent", "Add 0 to 4 to opponent's next roll.", []{ } } },
    { { ECS::Up, ECS::Up, ECS::Dice }, { "Ultimate Roll", "Roll a D20.", []{ } } },
    { { ECS::Up, ECS::Up, ECS::Cash }, { "Economic Boom", "Increase money earned for 4 turns.", []{ } } },
    { { ECS::Up, ECS::Down, ECS::Opponent }, { "Mixed Opponent", "Add -2 to 2 to your opponent's next roll.", []{ } } },
    { { ECS::Up, ECS::Down, ECS::Dice }, { "Dual Roll", "Roll a D4 and D12.", []{ } } },
    { { ECS::Up, ECS::Down, ECS::Cash }, { "Financial Mix", "Increase amount earned, while decreasing fees, for 2 turns.", []{ } } },
    { { ECS::Up, ECS::Opponent, ECS::Opponent }, { "Multi Boost-Opponent", "Add 0 to 2 to two opponents' next rolls.", []{ } } },
    { { ECS::Up, ECS::Opponent, ECS::Dice }, { "Enhanced Opponent Roll", "Make your opponent roll a D12.", []{ } } },
    { { ECS::Up, ECS::Opponent, ECS::Cash }, { "Fee Surge", "Significantly increases fees for your opponent.", []{ } } },
    { { ECS::Up, ECS::Dice, ECS::Dice }, { "Dice Mastery", "Roll a D12 with advantage.", []{ } } },
    { { ECS::Up, ECS::Dice, ECS::Cash }, { "Risk Averse Investor", "Earn money based on the number rolled by a D12, in a low risk manner.", []{ } } },
    { { ECS::Up, ECS::Stop, ECS::Stop }, { "Buff Extension", "Allowing buffs to continue for 2 more turns.", []{ } } },
    { { ECS::Up, ECS::Stop, ECS::Cash }, { "Fee Immunity", "Any increase in fees will have no effect on you for 3 turns.", []{ } } },
    { { ECS::Up, ECS::Cash, ECS::Cash }, { "Toll Windfall", "Significantly increases money earned from tolls for 2 turns.", []{ } } },
    { { ECS::Up, ECS::Down, ECS::Down }, { "Mixed Reduction", "Add -4 to 2 to your roll.", []{ } } },
    { { ECS::Down, ECS::Down, ECS::Opponent }, { "Double Opponent Reduction", "Add -4 to 0 to opponent's next roll.", []{ } } },
    { { ECS::Down, ECS::Down, ECS::Dice }, { "Coin Toss", "Flip a coin, instead of rolling a die.", []{ } } },
    { { ECS::Down, ECS::Down, ECS::Stop }, { "Stun Immunity", "Immune to stuns for 6 turns.", []{ } } },
    { { ECS::Down, ECS::Down, ECS::Cash }, { "Fee Relief II", "Decrease amount paid in fees for 4 turns.", []{ } } },
    { { ECS::Down, ECS::Opponent, ECS::Opponent }, { "Reduce Opponents", "Add -2 to 0 to two opponent's rolls.", []{ } } },
    { { ECS::Down, ECS::Opponent, ECS::Dice }, { "Dice Control", "Make opponent roll a D4.", []{ } } },
    { { ECS::Down, ECS::Opponent, ECS::Stop }, { "Handicap Halt", "Stop opponent from being able to play handicaps for 2 turns.", []{ } } },
    { { ECS::Down, ECS::Opponent, ECS::Cash }, { "Revenue Reduction", "Decrease money earned from opponent's revenue streams.", []{ } } },
    { { ECS::Down, ECS::Dice, ECS::Dice }, { "Advanced D4", "Roll D4 with advantage.", []{ } } },
    { { ECS::Down, ECS::Dice, ECS::Cash }, { "Risk Loving Investor", "Earn money based on the number rolled by a D4, in a high risk manner.", []{ } } },
    { { ECS::Down, ECS::Stop, ECS::Stop }, { "Handicap Immunity", "Immune to all handicaps for 2 turns.", []{ } } },
    { { ECS::Down, ECS::Stop, ECS::Cash }, { "Fee Break", "Pay no fees for 1 turn, then reduced fees for 3 turns.", []{ } } },
    { { ECS::Down, ECS::Cash, ECS::Cash }, { "Fee Slash", "Significantly decreases fees for 2 turns.", []{ } } },
    { { ECS::Opponent, ECS::Opponent, ECS::Dice }, { "Double Disadvantage", "Make two opponents roll with disadvantage.", []{ } } },
    { { ECS::Opponent, ECS::Opponent, ECS::Stop }, { "Double Stun", "Stun 2 opponents for 1 turn each.", []{ } } },
    { { ECS::Opponent, ECS::Opponent, ECS::Cash }, { "Double Fees", "Increase fees paid to you, by two opponents, for 2 turns.", []{ } } },
    { { ECS::Opponent, ECS::Dice, ECS::Dice }, { "Forced Advantage", "Make opponent roll with advantage.", []{ } } },
    { { ECS::Opponent, ECS::Dice, ECS::Stop }, { "Re-roll Rights", "You can make opponent re-roll their next roll.", []{ } } },
    { { ECS::Opponent, ECS::Dice, ECS::Cash }, { "Pickpocket", "Opponent pays you based on how high you roll.", []{ } } },
    { { ECS::Opponent, ECS::Stop, ECS::Stop }, { "Extended Stun", "Stun one opponent for 2 turns.", []{ } } },
    { { ECS::Opponent, ECS::Stop, ECS::Cash }, { "Profit Prevention", "Prevent opponent from earning profit for 2 turns.", []{ } } },
    { { ECS::Opponent, ECS::Cash, ECS::Cash }, { "Windfall", "Collect $300 from opponent.", []{ } } },
    { { ECS::Dice, ECS::Dice, ECS::Dice }, { "Triple Roll", "Roll 3 dice.", []{ } } },
    { { ECS::Dice, ECS::Dice, ECS::Stop }, { "Advantage Re-Roll", "Roll with advantage with the option to re-roll.", []{ } } },
    { { ECS::Dice, ECS::Dice, ECS::Cash }, { "Double Cash", "Gain money based on how high you roll, while rolling two dice.", []{ } } },
    { { ECS::Dice, ECS::Stop, ECS::Stop }, { "Double Re-Roll", "Roll with two optional re-rolls.", []{ } } },
    { { ECS::Dice, ECS::Stop, ECS::Cash }, { "Wealthy Re-Roll", "Gain money based on how high you roll, with the option to re-roll.", []{ } } },
    { { ECS::Dice, ECS::Cash, ECS::Cash }, { "Roll for Riches", "Gain significant money based on how high you roll.", []{ } } },
    { { ECS::Stop, ECS::Stop, ECS::Stop }, { "Triple Skip", "Skip 3 turns.", []{ } } },
    { { ECS::Stop, ECS::Stop, ECS::Cash }, { "Fee-Free Period", "Pay no fees for 2 turns.", []{ } } },
    { { ECS::Stop, ECS::Cash, ECS::Cash }, { "Immunity to Loss", "Immune to all forms of money loss for 1 turn.", []{ } } },
    { { ECS::Cash, ECS::Cash, ECS::Cash }, { "Jackpot", "Earn $1000.", []{ } } },
};

CardPlay::CardPlay(std::string title, std::string description, std::function<void()> func):
    title{ std::move(title) }, description{ std::move(description) }, play{ std::move(func) }
{
        
}
void CardPlay::Execute() const
{ play(); }
std::string CardPlay::Title() const
{ return title; }
std::string CardPlay::Description() const
{ return description; }

bool CardPlay::operator==(const CardPlay& rhs) const
{
    return title == rhs.title;
}
bool CardPlay::operator!=(const CardPlay& rhs) const { return !(*this == rhs); }
std::ostream& operator<<(std::ostream& os, const CardPlay& cardPlay)
{
    os << setc(F_ORANGE) << cardPlay.Title() << ": " << setc() << cardPlay.Description();
    return os;
}