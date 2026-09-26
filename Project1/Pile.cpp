#include "Pile.h"

#include "CombatStrategy.h"

Pile::Pile(int x, int y, TextureManager& textures)
    : SearchableObject(x, y, std::make_shared<AggressiveStrategy>(), 30, 8,
                       textures.get("assets/pile.png"), "pile of stuff") {}
