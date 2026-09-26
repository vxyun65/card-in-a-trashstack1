#pragma once
#include "SearchableObject.h"
#include "TextureManager.h"

// Шкаф: энергии тратит мало, но обыскивать его долго
class Closet : public SearchableObject {
 public:
  Closet(int x, int y, TextureManager& textures);
};
