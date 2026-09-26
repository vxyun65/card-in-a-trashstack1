#pragma once
#include <SFML/Graphics.hpp>
class Hero;

class EnergyDrink {
private:
    sf::Sprite sprite;
    int grid_x;
    int grid_y;
    bool is_opened;
    int energy_amount;

public:
    EnergyDrink(int x, int y, int amount, const sf::Texture& texture);
    void draw(sf::RenderWindow& window) const;
    bool checkInteraction(const Hero& hero, int hero_grid_x, int hero_grid_y) const;
    void applyReward(Hero& hero);
    int getEnergyAmount() const;
};
