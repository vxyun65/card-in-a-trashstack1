#include "Hero.h"

Hero::Hero(TileMap& map, TextureManager& textures, float start_x, float start_y)
    : facing(Direction::kDown), tile_map(&map) {
    health_points = kMaxEnergy;
    attack_damage = 10;
    name = "Hero";
    // Привязываем позицию к ЦЕНТРУ клетки, как у объектов и энергетиков
    position_x = start_x + kTileSize / 2.f;
    position_y = start_y + kTileSize / 2.f;

    // Порядок совпадает с enum Direction: вверх, влево, вниз, вправо
    direction_textures = { &textures.get("assets/w.png"), &textures.get("assets/a.png"),
                           &textures.get("assets/s.png"), &textures.get("assets/d.png") };
    setFacing(facing);
}

void Hero::setFacing(Direction direction) {
    facing = direction;
    const sf::Texture& texture = *direction_textures[static_cast<int>(direction)];
    sprite.setTexture(texture, true);

    sf::Vector2u size = texture.getSize();
    if (size.x == 0 || size.y == 0) return;
    sprite.setOrigin(size.x / 2.f, size.y / 2.f);
    sprite.setScale(kTileSize / size.x, kTileSize / size.y);
}

void Hero::draw(sf::RenderWindow& window) {
    sprite.setPosition(position_x, position_y);
    window.draw(sprite);
}

void Hero::restoreEnergy(int amount) {
    health_points += amount;
    if (health_points > kMaxEnergy) health_points = kMaxEnergy;
}

void Hero::takeDamage(int damage) { health_points -= damage; }
int Hero::getHealthPoints() const { return health_points; }
int Hero::getAttackDamage() const { return attack_damage; }
bool Hero::isAlive() const { return health_points > 0; }

void Hero::move(float delta_x, float delta_y) {
    // Поворачиваемся в сторону нажатой клавиши, даже если там стена
    if (delta_y < 0) setFacing(Direction::kUp);
    else if (delta_y > 0) setFacing(Direction::kDown);
    else if (delta_x < 0) setFacing(Direction::kLeft);
    else if (delta_x > 0) setFacing(Direction::kRight);

    float new_x = position_x + delta_x;
    float new_y = position_y + delta_y;

    // Переводим центр клетки обратно в координаты сетки
    int grid_x = static_cast<int>((new_x - kTileSize / 2.f) / kTileSize);
    int grid_y = static_cast<int>((new_y - kTileSize / 2.f) / kTileSize);

    if (tile_map->isWalkable(grid_x, grid_y)) {
        position_x = new_x;
        position_y = new_y;
        // Каждый шаг утомляет героя
        health_points -= kStepEnergyCost;
    }
}
