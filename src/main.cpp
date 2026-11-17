#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <cmath>

struct gameData {
    sf::Clock clock;
};

gameData gameStuff;
Player player;

int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1200}), "Pangolin Game");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    float radius = player.getRadius();

    sf::CircleShape PlayerShape(radius);
    PlayerShape.setOrigin({radius, radius});

    while (window.isOpen()) {
        float dt = gameStuff.clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        sf::Vector2f direction{0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) direction.y = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) direction.y = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) direction.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direction.x = 1;

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) direction /= length;

        player.move(direction, dt);
        player.update(dt);

        PlayerShape.setPosition(player.getPos());

        window.clear();
        window.draw(PlayerShape);
        window.display();
    }

    return 0;
}
