#include "Board.hpp"

Board::Board(Graphics& gfx)
    :
    gfx(gfx)
{}

void Board::DrawCell(const Location& loc, sf::Color c)
{
    gfx.DrawRectDim(loc.x*dim, loc.y*dim, dim-1, dim-1, c);
}