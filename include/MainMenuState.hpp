#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "Game.hpp"
#include "IState.hpp"

class MainMenuState : public IState
{
public:
    MainMenuState(GameDataRef sharedData);
    ~MainMenuState(); 
    /* Interface */
    void Init();
    void HandleInput();
    void Update(float dt);
    void Draw();

    void Pause();
    void Resume();
    /* End of Interface */
private:
    std::vector<sf::Text> texts_;
    sf::Sprite* pBgImage_ = nullptr;
    GameDataRef sharedData_;
    size_t selected_;
    bool inhibitKey_ = false;
    bool isChangingState_ = false;
};