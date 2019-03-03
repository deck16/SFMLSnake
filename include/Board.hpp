#pragma once
#include "Graphics.hpp"
#include "Location.hpp"

class Board
{
public:
    Board(Graphics& gfx);
    void DrawCell(const Location& loc, sf::Color c);
    void DrawBorders();
public:
    static constexpr int dim = 20;
    static constexpr int width = 20;
    static constexpr int height = 15;
    static constexpr int borderThickness = 50;
private:
    const sf::Color borderColor = sf::Color::Blue;
    const int x0 = (Graphics::ScreenWidth-width*dim)/2;
    const int y0 = (Graphics::ScreenHeight-height*dim)/2;
    Graphics& gfx;
};