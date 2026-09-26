#include "TextureManager.h"

const sf::Texture& TextureManager::get(const std::string& path) {
  auto found = textures.find(path);
  if (found != textures.end()) return found->second;

  sf::Texture& texture = textures[path];
  // Если файла нет, SFML сам пишет ошибку, а спрайт останется пустым
  texture.loadFromFile(path);
  return texture;
}
