#pragma once
#include "Graphics.hpp"
#include "Board.hpp"
#include "Snake.hpp"
#include "FrameTimer.hpp"
#include "Goal.hpp"
#include <random>
#include <queue>
#include "IState.hpp"
#include <memory>

class MainGameState : public IState
{
public:
    MainGameState(std::shared_ptr<class GameData> sharedData);
    /* Interface */
    void Init() override;
    void HandleInput() override;
    void Update(float dt) override;
    void Draw() override;

    void Resume() override;
    void Pause() override;
    /* End of Interface */
private:
    std::shared_ptr<class GameData> sharedData_;
    sf::Keyboard kbd_;
    Graphics gfx_;
    FrameTimer ft_;
    std::mt19937 rng_;
    Board brd_;
    Snake snek_;
    Goal goal_;
    Location dir_ = {1,0};
    Location oldDir_;

    float waitTime_ = 0.0f;
    float snekMovePeriod_ = 0.2f;
    float minMovePeriod_ = 0.08;

    bool gameOver_ = false;

    std::queue <Location> moveQueue_;
};