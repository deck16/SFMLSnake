#include "AssetManager.hpp"
#include <iostream>
void AssetManager::LoadFontFromFile(const std::string& name, const std::string& fileName)
{
    sf::Font font;
    if (font.loadFromFile(fileName))
    {
        fonts_[name] = font;
    }
    else
    {
        std::cout << "Couldn't load the font!" << std::endl;
    }
}

sf::Font& AssetManager::GetFont(const std::string& name)
{
    return fonts_.at(name);
}
void AssetManager::LoadTextureFromFile(const std::string& name, const std::string& fileName)
{
    sf::Texture texture;
    if (texture.loadFromFile(fileName))
    {
        textures_[name] = texture;
    }
    else
    {
        std::cout << "Couldn't load the texture!" << std::endl;
    }
}

sf::Texture& AssetManager::GetTexture(const std::string& name)
{
    return textures_.at(name);
}