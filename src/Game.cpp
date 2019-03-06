#include "Game.hpp"
#include <iostream>

#include "_Game.hpp"
Game::Game(std::shared_ptr<GameData> sharedData)
    :
    sharedData_(sharedData),
    gfx_(sharedData_->wnd),
    rng_(std::random_device()()),
    brd_(gfx_),
    snek_(brd_, {1,1}),
    goal_(brd_)
{}

void Game::Init()
{
    std::cout << "Main Game State Initialized!" << std::endl;
}

void Game::HandleInput()
{
    oldDir_ = dir_;
    if (kbd_.isKeyPressed(sf::Keyboard::W) || kbd_.isKeyPressed(sf::Keyboard::Up))
    {
        dir_ = {0, -1};
    }
    if (kbd_.isKeyPressed(sf::Keyboard::D) || kbd_.isKeyPressed(sf::Keyboard::Right))
    {
        dir_ = {1, 0};
    }
    if (kbd_.isKeyPressed(sf::Keyboard::A) || kbd_.isKeyPressed(sf::Keyboard::Left))
    {
        dir_ = {-1, 0};
    }
    if (kbd_.isKeyPressed(sf::Keyboard::S) || kbd_.isKeyPressed(sf::Keyboard::Down))
    {
        dir_ = {0, 1};
    }
}

void Game::Update(float dt) 
{
    waitTime_ += dt;

    //direction changed
    if (dir_ != oldDir_)
    {
        if (oldDir_ + dir_ == Location{0,0})
        {
            dir_ = oldDir_;
        }
        else
        {
            moveQueue_.push(dir_);
        }
    }

    if ( waitTime_ > snekMovePeriod_)
    {
        if (!moveQueue_.empty())
        {
            dir_ = moveQueue_.front();
            moveQueue_.pop();
        }
        snek_.MoveBy(dir_);
                
        waitTime_ = 0;

        if (snek_.IsOutsideBoard() || snek_.IsInTile())
        {
            gameOver_ = true;
        }

        if (snek_.CheckAndEatGoal(rng_, goal_))
        {
            if (snekMovePeriod_ < minMovePeriod_)
            {
                snekMovePeriod_ -= 0.005f;
            }
            else
            {
                snekMovePeriod_ = minMovePeriod_;
            } 
        }
    }
}

void Game::Draw()
{
    brd_.DrawBorders();
    if (!gameOver_)
    {
        goal_.Draw();
        snek_.Draw();
    }
}

void Game::Resume()
{
    std::cout << "Main Game State Resumed!" << std::endl;
}

void Game::Pause()
{
    std::cout << "Main Game State Paused!" << std::endl;
}

