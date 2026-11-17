#include <SFML/Graphics.hpp>
#include <cmath>
#include "player.hpp"
#include "enemy.hpp"


struct gameData {
    sf::Clock clock;
};

gameData gameStuff;
Player player;
Enemy enemy;


int main() {
    sf::RenderWindow window(sf::VideoMode({1920, 1200}), "Pangolin Game");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    float pradius = player.getRadius();
    float eradius = enemy.getRadius();

    sf::CircleShape PlayerShape(pradius);
    PlayerShape.setOrigin({pradius, pradius});
    sf::CircleShape EnemyShape(eradius);
    EnemyShape.setOrigin({eradius, eradius});
    EnemyShape.setFillColor(sf::Color::Red);


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
        EnemyShape.setPosition(enemy.getPos());
        
        sf::Vector2f difference = player.getPos() - enemy.getPos();
        float distance = std::sqrt(difference.x * difference.x + difference.y * difference.y); 

        if (distance < pradius + eradius) {
            player.takeDamage(20.f);
            PlayerShape.setFillColor(sf::Color::Blue);
        }

        window.clear();
        window.draw(PlayerShape);
        window.draw(EnemyShape);
        window.display();
    }

    return 0;
}
