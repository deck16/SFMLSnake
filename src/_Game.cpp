#include "_Game.hpp"
#include "Game.hpp"
#include "Graphics.hpp"

_Game::_Game(int width, int height, std::string title)
{
    sharedData_->wnd.create(sf::VideoMode(width, height), title);
    sharedData_->statesManager
    .AddState(std::move(std::make_unique<Game>(sharedData_)));
    Run();
}

void _Game::Run()
{
    while(sharedData_->wnd.isOpen())
    {
        sf::Event event;
        while(sharedData_->wnd.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                sharedData_->wnd.close();
            }
        }
        dt_ = ft_.Mark();
        sharedData_->wnd.clear();
        sharedData_->statesManager.ProcessStateChanges();
        sharedData_->statesManager.GetActiveState()->HandleInput();
        sharedData_->statesManager.GetActiveState()->Update(dt_);
        sharedData_->statesManager.GetActiveState()->Draw();
        sharedData_->wnd.display();
    }

}