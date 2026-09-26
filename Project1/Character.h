#pragma once
#include <string>

class Character {
 protected:
  int health_points;
  int attack_damage;
  std::string name;
  float position_x;
  float position_y;

 public:
  float getPositionX() const { return position_x; }
  float getPositionY() const { return position_y; }
  virtual ~Character() = default;

  virtual void takeDamage(int damage) = 0;
  virtual int getHealthPoints() const = 0;
  virtual int getAttackDamage() const = 0;
  virtual bool isAlive() const = 0;
  virtual void move(float delta_x, float delta_y) = 0;
  virtual const std::string& getName() const { return name; }
};