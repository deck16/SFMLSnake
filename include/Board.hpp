#pragma once
#include "Graphics.hpp"
#include "Location.hpp"

class Board
{
public:
    Board(Graphics& gfx);
    void DrawCell(const Location& loc, sf::Color c);
public:
    static constexpr int dim = 40;
    static constexpr int width = 20;
    static constexpr int height = 15;
    Graphics& gfx;
};