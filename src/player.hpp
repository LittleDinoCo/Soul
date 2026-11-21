#pragma once
#include <SFML/Graphics.hpp>
#include "enemy.hpp"

class Player {
    private:
        float radius = 20.f;
        float acceleration = 1000.f;
        float maxSpeed = 300.f;
        float friction = 0.95f;
        float health = 100.f;
        float iFrameHit = 0.5f;
        float iFrameDash = 1.f;
        float maxHealth = 100.f;
        sf::Vector2f velocity{0, 0};
        sf::Vector2f position{906, 600};
    public:
        void move(sf::Vector2f dir, float dt);
        void update(float dt);
        void takeDamage(float damage, float iFrame);
        void attack(Enemy& enemy, sf::Vector2f mousePos, sf::RenderWindow& window);
        sf::Vector2f getPos() const;
        float getRadius() const;
        float getHealth() const;



};
