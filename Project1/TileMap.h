#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

constexpr float kTileSize = 40.f;

class TileMap {
private:
    std::vector<std::vector<int>> grid;
    sf::Vector2u map_size;

public:
    TileMap(unsigned int width, unsigned int height);
    void generateDefault();
    void draw(sf::RenderWindow& window) const;
    bool isWalkable(int grid_x, int grid_y) const;
};
