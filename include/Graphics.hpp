#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Graphics
{
public:
    Graphics(sf::RenderWindow& wnd);
    void PutPixel(int x, int y, sf::Color c = sf::Color::White);
    void DrawRect(int x0, int y0, int x1, int y1, sf::Color c);
    void DrawRectDim(int x0, int y0, int width, int height, sf::Color c = sf::Color::White)
    {
        DrawRect(x0, y0, x0+width, y0+height, c);
    }
    void BeginFrame();
    void EndFrame();
public:
    static constexpr int ScreenWidth = 800;
    static constexpr int ScreenHeight = 600;
    sf::RenderWindow& wnd;
};