#include "Game.hpp"
#include <iostream>

Game::Game(sf::RenderWindow& wnd)
    :
    wnd(wnd),
    gfx(wnd),
    rng(std::random_device()()),
    brd(gfx),
    snek(brd, {1,1}),
    goal(brd)
{}

void Game::Go()
{
    gfx.BeginFrame();
    UpdateModel();
    ComposeFrame();
    gfx.EndFrame();
}

void Game::UpdateModel()
{
    const float dt = ft.Mark();
    waitTime += dt;

    if (kbd.isKeyPressed(sf::Keyboard::W))
    {
        dir = {0, -1};
    }
    if (kbd.isKeyPressed(sf::Keyboard::D))
    {
        dir = {1, 0};
    }
    if (kbd.isKeyPressed(sf::Keyboard::A))
    {
        dir = {-1, 0};
    }
    if (kbd.isKeyPressed(sf::Keyboard::S))
    {
        dir = {0, 1};
    }

    if ( waitTime > snekMovePeriod)
    {
        if  (kbd.isKeyPressed(sf::Keyboard::Space))
        {
            snek.Grow();
        }

        snek.MoveBy(dir);
        waitTime = 0;

        if (snek.IsOutsideBoard() || snek.IsInTile())
        {
            gameOver = true;
        }

        snek.CheckAndEatGoal(rng, goal);
    }
}

void Game::ComposeFrame()
{
    if (!gameOver)
    {
        goal.Draw();
        snek.Draw();
    }
}
