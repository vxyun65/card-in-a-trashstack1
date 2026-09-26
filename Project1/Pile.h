#pragma once
#include "SearchableObject.h"
#include "TextureManager.h"

// Куча вещей: разбирается быстро, но отнимает много энергии
class Pile : public SearchableObject {
public:
    Pile(int x, int y, TextureManager& textures);
};
