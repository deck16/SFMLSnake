#pragma once

#include "StateStack.hpp"
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"
#include <memory>
#include <string>
#include "Graphics.hpp"
#include "FrameTimer.hpp"
struct GameData
{
    sf::RenderWindow wnd;
    AssetManager assetManager;
    StateStack statesManager;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
public:
    Game(int width, int height, std::string title);
private:
    float dt_ = 0;
    GameDataRef sharedData_ = std::make_shared<GameData>();    
    void Run();
    FrameTimer ft_;
};