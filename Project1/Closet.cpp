#include "Closet.h"
#include "CombatStrategy.h"

Closet::Closet(int x, int y, TextureManager& textures)
    : SearchableObject(x, y, std::make_shared<DefensiveStrategy>(), 60, 4,
                       textures.get("assets/closet.png"), "closet") {
}
