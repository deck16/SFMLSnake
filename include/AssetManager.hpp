#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class AssetManager
{
public:
    void LoadFontFromFile(const std::string& name, const std::string& fileName);
    sf::Font& GetFont(const std::string& name);
    void LoadTextureFromFile(const std::string& name, const std::string& fileName);
    sf::Texture& GetTexture(const std::string& name);
private:
    std::map<std::string, sf::Font> fonts_;
    std::map<std::string, sf::Texture> textures_;
};