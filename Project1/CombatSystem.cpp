#include "CombatSystem.h"

bool CombatSystem::executeOneTurn(Hero& hero, SearchableObject& object) {
  // Герой разбирает часть вещей
  int hero_damage = hero.getAttackDamage();
  object.takeDamage(hero_damage);

  if (!object.isAlive()) return false;  // Объект обыскан

  // Обыск отнимает энергию
  int object_damage = object.calculateDamageTo(hero);
  hero.takeDamage(object_damage);

  return hero.isAlive();  // false = энергия кончилась
}
