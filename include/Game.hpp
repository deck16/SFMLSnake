#pragma once
#include "Graphics.hpp"
#include "Board.hpp"
#include "Snake.hpp"
#include "FrameTimer.hpp"
#include "Goal.hpp"
#include <random>
#include <queue>

class Game
{
public:
    Game(sf::RenderWindow& wnd);
    void Go();
private:
    void UpdateModel();
    void ComposeFrame();
private:
    sf::RenderWindow& wnd;
    sf::Keyboard kbd;
    Graphics gfx;
    FrameTimer ft;
    std::mt19937 rng;
    Board brd;
    Snake snek;
    Goal goal;
    Location dir = {1,0};

    float waitTime = 0.0f;
    float snekMovePeriod = 0.2f;
    float minMovePeriod = 0.08;

    bool gameOver = false;

    std::queue <Location> moveQueue;
};