#pragma once
#include <SFML/Graphics.hpp>
#include <array>

#include "Character.h"
#include "TextureManager.h"
#include "TileMap.h"

enum class Direction { kUp, kLeft, kDown, kRight };

class Hero : public Character {
 private:
  sf::Sprite sprite;
  std::array<const sf::Texture*, 4> direction_textures;
  Direction facing;
  TileMap* tile_map;

  void setFacing(Direction direction);

 public:
  static constexpr int kMaxEnergy = 100;
  static constexpr int kStepEnergyCost = 1;

  Hero(TileMap& map, TextureManager& textures, float start_x, float start_y);
  void draw(sf::RenderWindow& window);
  void restoreEnergy(int amount);

  void takeDamage(int damage) override;
  int getHealthPoints() const override;
  int getAttackDamage() const override;
  bool isAlive() const override;
  void move(float delta_x, float delta_y) override;
};
