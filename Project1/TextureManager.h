#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

// Хранит все текстуры игры: каждая загружается один раз и живёт, пока жив
// менеджер, поэтому спрайты можно спокойно копировать
class TextureManager {
private:
    std::map<std::string, sf::Texture> textures;

public:
    const sf::Texture& get(const std::string& path);
};
