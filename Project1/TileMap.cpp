#include "TileMap.h"

TileMap::TileMap(unsigned int width, unsigned int height) : map_size(width, height) {
    grid.resize(height, std::vector<int>(width, 0));
}

void TileMap::generateDefault() {
    for (unsigned int y = 0; y < map_size.y; ++y) {
        for (unsigned int x = 0; x < map_size.x; ++x) {
            // Границы карты - стены, остальное - пол
            if (x == 0 || x == map_size.x - 1 || y == 0 || y == map_size.y - 1) {
                grid[y][x] = 1;
            }
            else {
                grid[y][x] = 0;
            }
        }
    }
}

bool TileMap::isWalkable(int grid_x, int grid_y) const {
    if (grid_x < 0 || grid_x >= static_cast<int>(map_size.x) ||
        grid_y < 0 || grid_y >= static_cast<int>(map_size.y)) {
        return false;
    }
    return grid[grid_y][grid_x] == 0;
}

void TileMap::draw(sf::RenderWindow& window) const {
    sf::RectangleShape tile(sf::Vector2f(kTileSize, kTileSize));
    // Отрицательная толщина - обводка внутрь клетки, получается сетка
    tile.setOutlineThickness(-1.f);
    for (unsigned int y = 0; y < map_size.y; ++y) {
        for (unsigned int x = 0; x < map_size.x; ++x) {
            tile.setPosition(x * kTileSize, y * kTileSize);
            // Клетки полупрозрачные, чтобы сквозь них был виден фон комнаты
            if (grid[y][x] == 1) {
                tile.setFillColor(sf::Color(15, 15, 20, 210));
                tile.setOutlineColor(sf::Color(0, 0, 0, 120));
            }
            else {
                tile.setFillColor(sf::Color(30, 30, 40, 90));
                tile.setOutlineColor(sf::Color(255, 255, 255, 30));
            }
            window.draw(tile);
        }
    }
}
