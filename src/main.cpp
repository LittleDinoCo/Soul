#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
struct gameData {
    sf::Clock clock;
};
gameData gameStuff;


class PangolinData {
    private:
        float radius = 20.f;
        float mass = 300.f;
        float restitution = 1.8f;
        //Accel from input while not in ball form
        float platformerAccel = 200.f;
        //Accel from input while in ball form
        float rollAccel = 100.f;
        sf::Vector2f velocity{0, 0};
        sf::Vector2f position{906, 600};

    public:
        void move(int dir, int form, float dt) {
            if (form == 0) {
                velocity.x += dir * platformerAccel * dt;
            }
            else {
                velocity.x += dir * rollAccel * dt;
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
PangolinData Pangolin;







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
    
    float radius = Pangolin.getRadius();
    
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            std::cout << "Yay\n";
            Pangolin.move(-1, 2, dt);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            std::cout << "Yay\n";
            Pangolin.move(1, 2, dt);
        }

        Pangolin.update(dt);

        sf::Vector2f position = Pangolin.getPos();

        Player.setPosition(position);


        window.clear();

        window.draw(Player);

        window.display();
    }

    return 0;
}
