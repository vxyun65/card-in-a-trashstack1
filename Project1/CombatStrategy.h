#pragma once
class Character;

class CombatStrategy {
 public:
  virtual ~CombatStrategy() = default;
  virtual int calculateDamage(const Character& attacker,
                              const Character& defender) const = 0;
};

class NormalStrategy : public CombatStrategy {
 public:
  int calculateDamage(const Character& attacker,
                      const Character& defender) const override;
};

class AggressiveStrategy : public CombatStrategy {
 public:
  int calculateDamage(const Character& attacker,
                      const Character& defender) const override;
};

class DefensiveStrategy : public CombatStrategy {
 public:
  int calculateDamage(const Character& attacker,
                      const Character& defender) const override;
};