#pragma once
#include "Board.hpp"
#include "Location.hpp"

class Goal
{
public:
    Goal(Board& brd, sf::Color c = sf::Color::Red);
    void Draw();
    void Spawn(const Location& _loc);
    Location GetLoc() const;
private:
    Board& brd;
    sf::Color col;
    Location loc = {5,5};
};