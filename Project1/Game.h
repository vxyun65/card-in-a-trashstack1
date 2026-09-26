#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <random>
#include <vector>
#include "TextureManager.h"
#include "TileMap.h"
#include "Hero.h"
#include "SearchableObject.h"
#include "EnergyDrink.h"
#include "CombatSystem.h"
#include "UIManager.h"

enum class GameState { kExploration, kVictory, kDefeat };

class Game {
private:
    static constexpr int kWindowWidth = 800;
    static constexpr int kWindowHeight = 600;
    // Шанс найти SD-карту в обысканном объекте (в последнем она есть всегда)
    static constexpr double kCardChance = 0.25;

    sf::RenderWindow window;
    // Объявлен раньше героя и объектов: текстуры должны жить дольше спрайтов
    TextureManager texture_manager;
    TileMap tile_map;
    Hero hero;
    std::vector<std::unique_ptr<SearchableObject>> searchable_objects;
    std::vector<EnergyDrink> energy_drinks;
    UIManager ui_manager;
    sf::Sprite background;
    GameState state;
    bool is_searching;
    SearchableObject* current_target;
    std::mt19937 rng;

    void processEvents();
    void handleSearchTurn();
    void updateExploration();
    void render();
    void checkCollisions();
    void finishGame(GameState result);
    int countActiveObjects() const;
    bool rollCardFound();

public:
    Game();
    void run();
};
