#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>
#include <string>
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
     sf::View view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));
    window.setView(view);

    sf::Font font;
    if (!font.openFromFile("fonts/AdwaitaSans-Regular.ttf")) {
        return -1; // Handle missing font file
    }
    float pradius = player.getRadius();
    float eradius = enemy.getRadius();
    sf::Text eHealth(font, std::to_string(std::lround(enemy.getHealth())), 30);
    sf::Text pHealth(font, std::to_string(std::lround(player.getHealth())), 30);

   

    
    

    while (window.isOpen()) {
        float dt = gameStuff.clock.restart().asSeconds();
        window.clear();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* resized = event->getIf<sf::Event::Resized>()) {
                float aspectRatio =
                static_cast<float>(resized->size.x) / resized->size.y;

                float targetRatio = 16.f / 9.f;

                sf::View view(sf::FloatRect({0.f, 0.f}, {1920.f, 1080.f}));

                if (aspectRatio > targetRatio) {
                    float width = 1080.f * aspectRatio;
                    view.setSize({width, 1080.f});
                }
                else {
                    float height = 1920.f / aspectRatio;
                    view.setSize({1920.f, height});
                }

                window.setView(view);
            }
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    player.attack(enemy, window, 0.5f);
 
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::Q) {
                    player.heal();
 
                }
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->code == sf::Keyboard::Key::E) {
                    player.imbue();
 
                }
            }
        }

        sf::Vector2f direction{0.f, 0.f};
        if (player.getAttackDuration() > 0) player.attack(enemy, window, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) direction.y = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) direction.y = 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) direction.x = -1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) direction.x = 1;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) player.siphon(enemy, window);
        else player.cancelSiphon();


        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (length != 0) direction /= length;

        player.move(direction, dt);
        player.update(dt);
        enemy.update(player, dt);

        eHealth.setPosition({enemy.getPos().x, enemy.getPos().y - 50});
        eHealth.setString(std::to_string(std::lround(enemy.getHealth())));
        pHealth.setPosition({player.getPos().x, player.getPos().y - 50});
        pHealth.setString(std::to_string(std::lround(player.getHealth())));

        
        sf::Vector2f difference = player.getPos() - enemy.getPos();
        float distance = std::sqrt(difference.x * difference.x + difference.y * difference.y); 

        if (distance < pradius + eradius && enemy.getAlive()) {
            player.takeDamage(20.f, 0.5f);
        }
        
                

        
        player.draw(window);
        enemy.draw(window);
        if (enemy.getAlive()) {
            window.draw(eHealth);
        }
        if (player.getAlive()) {
            window.draw(pHealth);
        }
        window.display();
    }

    return 0;
}
