#include "EnergyDrink.h"
#include "Hero.h"

EnergyDrink::EnergyDrink(int x, int y, int amount, const sf::Texture& texture)
    : grid_x(x), grid_y(y), is_opened(false), energy_amount(amount) {
    sprite.setTexture(texture, true);
    sf::Vector2u size = texture.getSize();
    if (size.x > 0 && size.y > 0) {
        sprite.setScale(kTileSize / size.x, kTileSize / size.y);
    }
    sprite.setPosition(x * kTileSize, y * kTileSize);
}

void EnergyDrink::draw(sf::RenderWindow& window) const {
    if (!is_opened) window.draw(sprite);
}

bool EnergyDrink::checkInteraction(const Hero& hero, int hero_grid_x, int hero_grid_y) const {
    return !is_opened && hero_grid_x == grid_x && hero_grid_y == grid_y;
}

void EnergyDrink::applyReward(Hero& hero) {
    hero.restoreEnergy(energy_amount);
    is_opened = true;
}

int EnergyDrink::getEnergyAmount() const { return energy_amount; }
