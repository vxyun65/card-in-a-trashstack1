#pragma once
#include "Hero.h"
#include "SearchableObject.h"

class CombatSystem {
public:
    // Один ход обыска. Возвращает true, если обыск продолжается,
    // false - если объект обыскан или у героя кончилась энергия
    static bool executeOneTurn(Hero& hero, SearchableObject& object);
};
