#include "UIManager.h"

#include <cmath>
#include <iostream>

namespace {

constexpr float kBarWidth = 200.f;
constexpr float kBarHeight = 14.f;

// Ставит центр текста в точку (x, y) с учётом отступов шрифта
void centerText(sf::Text& text, float x, float y) {
  sf::FloatRect bounds = text.getLocalBounds();
  text.setOrigin(std::floor(bounds.left + bounds.width / 2.f),
                 std::floor(bounds.top + bounds.height / 2.f));
  text.setPosition(std::floor(x), std::floor(y));
}

// Белый текст с чёрной обводкой читается на любом фоне
void setupText(sf::Text& text, const sf::Font& font, unsigned int size) {
  text.setFont(font);
  text.setCharacterSize(size);
  text.setFillColor(sf::Color::White);
  text.setOutlineColor(sf::Color::Black);
  text.setOutlineThickness(2.f);
}

}  // namespace

bool UIManager::loadFont(const std::string& path) {
  if (!font.loadFromFile(path)) {
    std::cout << "[ERROR] Cannot load font: " << path << "\n";
    return false;
  }
  setupText(title_text, font, 28);
  setupText(message_text, font, 18);
  setupText(energy_text, font, 16);
  return true;
}

void UIManager::setTitle(const std::string& title) {
  title_text.setString(title);
}

void UIManager::updateEnergy(int current, int max) {
  energy_bar_bg.setSize(sf::Vector2f(kBarWidth, kBarHeight));
  energy_bar_bg.setFillColor(sf::Color(50, 50, 50, 200));
  energy_bar_bg.setOutlineColor(sf::Color::Black);
  energy_bar_bg.setOutlineThickness(1.f);

  // Энергия может уйти в минус на последнем шаге - полоска не должна
  float ratio = static_cast<float>(current) / max;
  if (ratio < 0.f) ratio = 0.f;
  if (ratio > 1.f) ratio = 1.f;
  energy_bar.setSize(sf::Vector2f(kBarWidth * ratio, kBarHeight));
  energy_bar.setFillColor(
      ratio > 0.5f ? sf::Color::Green
                   : (ratio > 0.25f ? sf::Color::Yellow : sf::Color::Red));

  int shown_energy = current < 0 ? 0 : current;
  energy_text.setString("Energy: " + std::to_string(shown_energy) + "/" +
                        std::to_string(max));
}

void UIManager::showMessage(const std::string& msg) {
  message_text.setString(msg);
}

void UIManager::drawTitle(sf::RenderWindow& window, int window_width) const {
  sf::Text title = title_text;
  centerText(title, window_width / 2.f, 28.f);
  window.draw(title);
}

void UIManager::draw(sf::RenderWindow& window, int window_width,
                     int window_height) const {
  drawTitle(window, window_width);

  // Энергия - под заголовком, над игровым полем
  sf::Text energy = energy_text;
  centerText(energy, window_width / 2.f, 62.f);
  window.draw(energy);

  float bar_x = window_width / 2.f - kBarWidth / 2.f;
  sf::RectangleShape bar_bg = energy_bar_bg;
  sf::RectangleShape bar = energy_bar;
  bar_bg.setPosition(bar_x, 76.f);
  bar.setPosition(bar_x, 76.f);
  window.draw(bar_bg);
  window.draw(bar);

  // Сообщения - под игровым полем
  sf::Text message = message_text;
  centerText(message, window_width / 2.f, window_height - 55.f);
  window.draw(message);
}

void UIManager::drawEndScreen(sf::RenderWindow& window, int width, int height,
                              const std::string& text) const {
  sf::RectangleShape shade(
      sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
  shade.setFillColor(sf::Color(0, 0, 0, 170));
  window.draw(shade);

  sf::Text overlay_text;
  setupText(overlay_text, font, 34);
  overlay_text.setString(text);
  centerText(overlay_text, width / 2.f, height / 2.f);
  window.draw(overlay_text);

  sf::Text hint_text;
  setupText(hint_text, font, 18);
  hint_text.setString("Press ESC to exit");
  centerText(hint_text, width / 2.f, height / 2.f + 45.f);
  window.draw(hint_text);

  // Заголовок остаётся поверх затемнения
  drawTitle(window, width);
}
