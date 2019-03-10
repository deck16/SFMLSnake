#include "MainGameState.hpp"
#include "MainMenuState.hpp"
#include <iostream>

#include "Game.hpp"
MainGameState::MainGameState(std::shared_ptr<GameData> sharedData)
    :
    sharedData_(sharedData),
    gfx_(sharedData_->wnd),
    rng_(std::random_device()()),
    brd_(gfx_),
    snek_(brd_, {1,1}),
    goal_(brd_)
{}

void MainGameState::Init()
{
    std::cout << "Main Game State Initialized!" << std::endl;
}

void MainGameState::HandleInput()
{
    oldDir_ = dir_;

    sf::Event event;
    while(sharedData_->wnd.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            sharedData_->wnd.close();
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
            {
                dir_ = {0, -1};
            }
            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
            {
                dir_ = {1, 0};
            }
            if (event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
            {
                dir_ = {-1, 0};
            }
            if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
            {
                dir_ = {0, 1};
            }
            if (event.key.code == sf::Keyboard::Escape)
            {
                isChangingState_ = true;
                inhibitKey_ = true;
            }
        } 
        if (event.type == sf::Event::KeyReleased && isChangingState_)
        {
            inhibitKey_ = false;
            isChangingState_ = false;
            sharedData_->statesManager.AddState(std::move(std::make_unique<MainMenuState>(sharedData_)));
        }
    }
}

void MainGameState::Update(float dt) 
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
            if (snekMovePeriod_ > minMovePeriod_)
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

void MainGameState::Draw()
{
    brd_.DrawBorders();
    if (!gameOver_)
    {
        goal_.Draw();
        snek_.Draw();
    }
}

void MainGameState::Resume()
{
    std::cout << "Main Game State Resumed!" << std::endl;
}

void MainGameState::Pause()
{
    std::cout << "Main Game State Paused!" << std::endl;
}