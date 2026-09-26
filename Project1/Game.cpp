#include "Game.h"
#include "Pile.h"
#include "Closet.h"
#include <iostream>
#include <string>

Game::Game()
    : window(sf::VideoMode(kWindowWidth, kWindowHeight), "Find my SD card", sf::Style::Close),
    tile_map(10, 10),
    hero(tile_map, texture_manager, 2 * kTileSize, 2 * kTileSize),
    state(GameState::kExploration),
    is_searching(false),
    current_target(nullptr),
    rng(std::random_device{}()) {
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);
    tile_map.generateDefault();

    // Фон растягиваем на всё окно, даже если картинка другого размера
    const sf::Texture& background_texture = texture_manager.get("assets/bg.png");
    background.setTexture(background_texture, true);
    sf::Vector2u background_size = background_texture.getSize();
    if (background_size.x > 0 && background_size.y > 0) {
        background.setScale(static_cast<float>(kWindowWidth) / background_size.x,
                            static_cast<float>(kWindowHeight) / background_size.y);
    }

    if (!ui_manager.loadFont("assets/arial.ttf")) {
        std::cout << "[WARN] Font assets/arial.ttf not found.\n";
    }
    ui_manager.setTitle("Help me find my SD card");
    ui_manager.updateEnergy(hero.getHealthPoints(), Hero::kMaxEnergy);
    ui_manager.showMessage("WASD - move, SPACE - search");

    searchable_objects.push_back(std::make_unique<Pile>(5, 3, texture_manager));
    searchable_objects.push_back(std::make_unique<Closet>(7, 5, texture_manager));
    searchable_objects.push_back(std::make_unique<Pile>(3, 7, texture_manager));

    energy_drinks.emplace_back(4, 4, 30, texture_manager.get("assets/hp.png"));
    energy_drinks.emplace_back(8, 2, 50, texture_manager.get("assets/hp.png"));
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window.close();
            }

            if (state != GameState::kExploration) continue;

            // Пошаговое движение
            if (!is_searching) {
                float step = kTileSize;
                bool is_move_key = true;
                switch (event.key.code) {
                case sf::Keyboard::W: case sf::Keyboard::Up:    hero.move(0, -step); break;
                case sf::Keyboard::S: case sf::Keyboard::Down:  hero.move(0, step); break;
                case sf::Keyboard::A: case sf::Keyboard::Left:  hero.move(-step, 0); break;
                case sf::Keyboard::D: case sf::Keyboard::Right: hero.move(step, 0); break;
                default: is_move_key = false; break;
                }
                // Проверяем клетку сразу после шага, чтобы не проскочить объект
                if (is_move_key) updateExploration();
            }
            // Пошаговый обыск
            else if (event.key.code == sf::Keyboard::Space) {
                handleSearchTurn();
            }
        }
    }
}

void Game::handleSearchTurn() {
    bool search_continues = CombatSystem::executeOneTurn(hero, *current_target);
    ui_manager.updateEnergy(hero.getHealthPoints(), Hero::kMaxEnergy);

    if (search_continues) {
        ui_manager.showMessage("Searching the " + current_target->getName() + "... Press SPACE");
        return;
    }

    if (hero.isAlive()) {
        // В последнем необысканном объекте карта лежит гарантированно
        bool is_last_object = countActiveObjects() == 1;
        current_target->setIsActive(false);
        if (is_last_object || rollCardFound()) {
            finishGame(GameState::kVictory);
        }
        else {
            ui_manager.showMessage("Not here... Keep looking.");
        }
    }
    else {
        finishGame(GameState::kDefeat);
    }
    is_searching = false;
    current_target = nullptr;
}

void Game::updateExploration() {
    // Энергия могла закончиться на последнем шаге
    if (!hero.isAlive()) {
        finishGame(GameState::kDefeat);
    }
    else {
        checkCollisions();
    }
    ui_manager.updateEnergy(hero.getHealthPoints(), Hero::kMaxEnergy);
}

void Game::finishGame(GameState result) {
    state = result;
    // Итог показывает финальный экран, старая подсказка больше не нужна
    ui_manager.showMessage("");
}

void Game::checkCollisions() {
    if (is_searching) return;

    int hero_grid_x = static_cast<int>((hero.getPositionX() - kTileSize / 2.f) / kTileSize);
    int hero_grid_y = static_cast<int>((hero.getPositionY() - kTileSize / 2.f) / kTileSize);

    for (auto& object : searchable_objects) {
        if (object->getIsActive() && object->getGridX() == hero_grid_x && object->getGridY() == hero_grid_y) {
            is_searching = true;
            current_target = object.get();
            ui_manager.showMessage("Searching the " + object->getName() + "... Press SPACE");
            return;
        }
    }

    for (auto& drink : energy_drinks) {
        if (drink.checkInteraction(hero, hero_grid_x, hero_grid_y)) {
            drink.applyReward(hero);
            ui_manager.showMessage("Energy drink! +" + std::to_string(drink.getEnergyAmount()) + " energy");
        }
    }
}

int Game::countActiveObjects() const {
    int count = 0;
    for (const auto& object : searchable_objects) {
        if (object->getIsActive()) ++count;
    }
    return count;
}

bool Game::rollCardFound() {
    std::bernoulli_distribution card_chance(kCardChance);
    return card_chance(rng);
}

void Game::render() {
    window.clear(sf::Color(20, 20, 20));

    // 1. Фон комнаты на всё окно
    window.setView(window.getDefaultView());
    window.draw(background);

    // 2. Игровой мир: 400x400 пикселей, центрирован в окне 800x600
    sf::View world_view;
    world_view.setCenter(200.f, 200.f);
    world_view.setSize(400.f, 400.f);
    // Сохраняем квадратные пропорции, чтобы тайлы не сплющивались
    world_view.setViewport(sf::FloatRect(0.25f, 0.1667f, 0.5f, 0.6667f));
    window.setView(world_view);

    tile_map.draw(window);
    for (const auto& drink : energy_drinks) drink.draw(window);
    for (const auto& object : searchable_objects) object->draw(window);
    hero.draw(window);

    // 3. UI: возвращаем стандартный вид, чтобы текст и полоски рисовались на весь экран
    window.setView(window.getDefaultView());
    ui_manager.draw(window, kWindowWidth, kWindowHeight);

    // 4. Экран конца игры
    if (state == GameState::kVictory) {
        ui_manager.drawEndScreen(window, kWindowWidth, kWindowHeight, "Now I can sleep with music");
    }
    else if (state == GameState::kDefeat) {
        ui_manager.drawEndScreen(window, kWindowWidth, kWindowHeight, "Departing to the dream world");
    }

    window.display();
}
