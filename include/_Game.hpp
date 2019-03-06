#pragma once

#include "StateStack.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "Graphics.hpp"
#include "FrameTimer.hpp"
struct GameData
{
    sf::RenderWindow wnd;
    StateStack statesManager;
};

typedef std::shared_ptr<GameData> GameDataRef;

class _Game
{
public:
    _Game(int width, int height, std::string title);
private:
    float dt_ = 0;
    GameDataRef sharedData_ = std::make_shared<GameData>();    
    void Run();
    FrameTimer ft_;
};