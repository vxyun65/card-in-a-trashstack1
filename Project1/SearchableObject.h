#pragma once
#include "Character.h"
#include "CombatStrategy.h"
#include "TileMap.h"
#include <memory>
#include <SFML/Graphics.hpp>

// Предмет в комнате, который нужно обыскать. health_points - сколько вещей
// осталось перебрать, attack_damage - сколько энергии отнимает обыск
class SearchableObject : public Character {
protected:
    std::shared_ptr<CombatStrategy> strategy;
    bool is_active;
    sf::Sprite sprite;
    int grid_x;
    int grid_y;

public:
    SearchableObject(int x, int y, std::shared_ptr<CombatStrategy> strat, int hp, int dmg,
                     const sf::Texture& texture, const std::string& name);
    virtual ~SearchableObject() = default;

    void draw(sf::RenderWindow& window) const;
    void takeDamage(int damage) override;
    int getHealthPoints() const override;
    int getAttackDamage() const override;
    bool isAlive() const override;
    void move(float delta_x, float delta_y) override;
    int calculateDamageTo(const Character& target) const;
    int getGridX() const;
    int getGridY() const;
    bool getIsActive() const;
    void setIsActive(bool active);
};
