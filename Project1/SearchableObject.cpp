#include "SearchableObject.h"

SearchableObject::SearchableObject(int x, int y,
                                   std::shared_ptr<CombatStrategy> strat,
                                   int hp, int dmg, const sf::Texture& texture,
                                   const std::string& nm)
    : strategy(strat), is_active(true), grid_x(x), grid_y(y) {
  health_points = hp;
  attack_damage = dmg;
  name = nm;
  // Центр клетки
  position_x = x * kTileSize + kTileSize / 2.f;
  position_y = y * kTileSize + kTileSize / 2.f;

  sprite.setTexture(texture, true);
  sf::Vector2u size = texture.getSize();
  if (size.x > 0 && size.y > 0) {
    sprite.setScale(kTileSize / size.x, kTileSize / size.y);
  }
  sprite.setPosition(x * kTileSize, y * kTileSize);
}

void SearchableObject::draw(sf::RenderWindow& window) const {
  if (is_active) window.draw(sprite);
}

void SearchableObject::takeDamage(int damage) { health_points -= damage; }
int SearchableObject::getHealthPoints() const { return health_points; }
int SearchableObject::getAttackDamage() const { return attack_damage; }
bool SearchableObject::isAlive() const { return health_points > 0; }
void SearchableObject::move(float delta_x, float delta_y) {}
int SearchableObject::calculateDamageTo(const Character& target) const {
  return strategy->calculateDamage(*this, target);
}
int SearchableObject::getGridX() const { return grid_x; }
int SearchableObject::getGridY() const { return grid_y; }
bool SearchableObject::getIsActive() const { return is_active; }
void SearchableObject::setIsActive(bool active) { is_active = active; }
