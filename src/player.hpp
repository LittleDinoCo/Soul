#pragma once
#include <SFML/Graphics.hpp>

class Player {
    private:
        float radius = 20.f;
        float acceleration = 1000.f;
        float maxSpeed = 300.f;
        float friction = 0.95f;
        float health = 100.f;
        float maxHealth = 100.f;
        sf::Vector2f velocity{0, 0};
        sf::Vector2f position{906, 600};
    public:
        void move(sf::Vector2f dir, float dt);
        void update(float dt);
        void takeDamage(float damage);
        sf::Vector2f getPos() const;
        float getRadius() const;


};
