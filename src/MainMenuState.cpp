#include "MainMenuState.hpp"
#include "MainGameState.hpp"
#include "common.hpp"
MainMenuState::MainMenuState(GameDataRef sharedData)
    :
    sharedData_(sharedData)
{}

void MainMenuState::Init()
{
    std::cout << "Main Menu State Initialized!" << std::endl;
    sharedData_->assetManager.LoadFontFromFile("menuFont", P_MENU_FONT);
    sharedData_->assetManager.LoadTextureFromFile("menuBackground", P_MENU_BACKGROUND);
    sf::Font& font = sharedData_->assetManager.GetFont("menuFont");
    sf::Texture& texture = sharedData_->assetManager.GetTexture("menuBackground");

    pBgImage_ = new sf::Sprite(texture);
    texts_.emplace_back("Play now!", font, 30);
    texts_.emplace_back("Settings and Options!", font, 30);
    texts_.emplace_back("Run From This Game!", font, 30);
    texts_.emplace_back("Make a Fart Noise!", font, 30);

    sf::Vector2f topLeft = {100.0f, 100.0f};
    for (size_t i=0; i<texts_.size(); i++)
    {
        texts_[i].setPosition(topLeft.x, topLeft.y + i*100);
    }
    selected_ = 0;
}

void MainMenuState::HandleInput()
{
    sf::Event event;
    while (sharedData_->wnd.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed && !inhibitKey_)
        {
            if (event.key.code == sf::Keyboard::Down)
            {
                selected_ = (selected_ + 1) % texts_.size();
            }
            if (event.key.code == sf::Keyboard::Up)
            {
                selected_ = (selected_ - 1) % texts_.size();
            } 
            if ((event.key.code == sf::Keyboard::Escape) || (event.key.code == sf::Keyboard::Return && selected_ == 0))
            {
                isChangingState_ = true;
            }
            inhibitKey_ = true;
        }
        if (event.type == sf::Event::KeyReleased)
        {
            inhibitKey_ = false;
            if (isChangingState_)
            {
                sharedData_->statesManager.RemoveState();
            }
        }
    }
}

void MainMenuState::Update(float dt)
{
    dt++;
    for (size_t i=0; i < texts_.size(); i++)
    {
        if (selected_ == i)
        {
            texts_[i].setFillColor(sf::Color::Red);
            texts_[i].setCharacterSize(40);
        }
        else
        {
            texts_[i].setFillColor(sf::Color::White);
            texts_[i].setCharacterSize(30);
        }
    }
}

void MainMenuState::Draw()
{
    
    sharedData_->wnd.draw(*pBgImage_);
    for (auto& t : texts_)
    {
        sharedData_->wnd.draw(t);
    }
}

void MainMenuState::Pause()
{
    std::cout << "Main Game State Resumed!" << std::endl;
}

void MainMenuState::Resume()
{
    std::cout << "Main Game State Paused!" << std::endl;
}

MainMenuState::~MainMenuState()
{
    delete pBgImage_;
    pBgImage_ = nullptr;
}