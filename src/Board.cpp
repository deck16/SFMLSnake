#include "Board.hpp"

Board::Board(Graphics& gfx)
    :
    gfx(gfx)
{}

void Board::DrawCell(const Location& loc, sf::Color c)
{
    gfx.DrawRectDim(x0+loc.x*dim, y0+loc.y*dim, dim-1, dim-1, c);
}

void Board::DrawBorders()
{
    const int x0 = (Graphics::ScreenWidth-width*dim)/2;
    const int y0 = (Graphics::ScreenHeight-height*dim)/2;

    //top
    gfx.DrawRect( x0-borderThickness, y0-borderThickness, x0+width*dim, y0, borderColor);
    //bottom
    gfx.DrawRect( x0-borderThickness, y0+height*dim, x0+width*dim, y0+height*dim+borderThickness, borderColor);
    //left
    gfx.DrawRect( x0-borderThickness, y0-borderThickness, x0, y0+height*dim, borderColor);
    //right
    gfx.DrawRect( x0+width*dim, y0-borderThickness, x0+width*dim+borderThickness, y0+height*dim+borderThickness, borderColor);


}