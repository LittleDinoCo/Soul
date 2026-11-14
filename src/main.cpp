#include <SFML/Window/VideoMode.hpp>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
    std::cout << "Hello World!\n";
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "Pangolin Game");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        // Poll for events
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        // Draw things here
        window.display();
    }

    return 0;
}
