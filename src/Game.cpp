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
    if (kbd.isKeyPressed(sf::Keyboard::W) || kbd.isKeyPressed(sf::Keyboard::Up))
    {
        dir = {0, -1};
    }
    if (kbd.isKeyPressed(sf::Keyboard::D) || kbd.isKeyPressed(sf::Keyboard::Right))
    {
        dir = {1, 0};
    }
    if (kbd.isKeyPressed(sf::Keyboard::A) || kbd.isKeyPressed(sf::Keyboard::Left))
    {
        dir = {-1, 0};
    }
    if (kbd.isKeyPressed(sf::Keyboard::S) || kbd.isKeyPressed(sf::Keyboard::Down))
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
        {
            if (snekMovePeriod < minMovePeriod)
            {
                snekMovePeriod -= 0.005f;
            }
            else
            {
                snekMovePeriod = minMovePeriod;
            } 
        }
    }
}

void Game::ComposeFrame()
{
    brd.DrawBorders();
    if (!gameOver)
    {
        goal.Draw();
        snek.Draw();
    }
}
