#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIManager {
private:
    sf::Font font;
    sf::Text title_text;
    sf::Text message_text;
    sf::Text energy_text;
    sf::RectangleShape energy_bar;
    sf::RectangleShape energy_bar_bg;

    void drawTitle(sf::RenderWindow& window, int window_width) const;

public:
    bool loadFont(const std::string& path);
    void setTitle(const std::string& title);
    void updateEnergy(int current, int max);
    void showMessage(const std::string& msg);
    void draw(sf::RenderWindow& window, int window_width, int window_height) const;
    void drawEndScreen(sf::RenderWindow& window, int width, int height, const std::string& text) const;
};
