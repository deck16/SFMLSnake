#include "Goal.hpp"

Goal::Goal(Board& brd, sf::Color c)
    :
    brd(brd),
    col(c)
{}

void Goal::Draw()
{
    brd.DrawCell(loc, col);
}
    
void Goal::Spawn(const Location& _loc)
{
    loc = _loc;
}

Location Goal::GetLoc() const
{
    return loc;
}