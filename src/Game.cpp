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
    Location oldDir = dir;
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

    //direction changed
    if (dir != oldDir)
    {
        if (oldDir + dir == Location{0,0})
        {
            dir = oldDir;
        }
        else
        {
            moveQueue.push(dir);
        }
    }

    if ( waitTime > snekMovePeriod)
    {
        if (!moveQueue.empty())
        {
            dir = moveQueue.front();
            moveQueue.pop();
        }
        snek.MoveBy(dir);
                
        waitTime = 0;

        if (snek.IsOutsideBoard() || snek.IsInTile())
        {
            gameOver = true;
        }

        if (snek.CheckAndEatGoal(rng, goal))
            snekMovePeriod -= 0.005f;
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
