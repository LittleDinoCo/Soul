
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
struct gameData {
    sf::Clock clock;
};
gameData gameStuff;


class PlayerData {
    private:
        float radius = 20.f;
        float acceleration = 1000.f;
        float maxSpeed = 300.f;
        float friction = 0.95f;
        sf::Vector2f velocity{0, 0};
        sf::Vector2f position{906, 600};

    public:
        void move(sf::Vector2f dir, float dt) {
            float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
            velocity += dir * acceleration * dt;
            if (speed > maxSpeed) {
                velocity = (velocity / speed) * maxSpeed;
            }
            if (dir.x == 0) {
                velocity.x *= friction;
            }
            if (dir.y == 0) {
                velocity.y *= friction;
            }
        }
        void update(float dt) {
            position += (velocity * dt);
        }
        sf::Vector2f getPos() const {
            return position;
        }
        float getRadius() const {
            return radius;
        }
};
PlayerData player;

int main() {
    std::cout << "Hello World!\n";
    sf::RenderWindow window(sf::VideoMode({1920, 1200}), "Pangolin Game");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);


    std::vector<sf::Color> colors {
        sf::Color(0, 0, 0),
        sf::Color(255, 255, 255),
        sf::Color(255, 0, 150),
    };
    
    float radius = player.getRadius();
    
    sf::CircleShape Player(radius);
    Player.setOrigin({radius, radius});
    

    int colorNum = 0;

    while (window.isOpen()) {
        float dt = gameStuff.clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->code == sf::Keyboard::Key::E) {
                if (colorNum < colors.size() - 1) {
                    colorNum += 1;
                }
                else {
                    colorNum = 0;
                }
            }
        }

        }
        sf::Vector2f direction{0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            direction.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            direction.y = 1;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            direction.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            direction.x = 1;
        }

        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) {
            direction /= length;
        }



        player.move(direction ,dt);

        player.update(dt);

        sf::Vector2f position = player.getPos();

        Player.setPosition(position);


        window.clear();

        window.draw(Player);

        window.display();
    }

    return 0;
}

