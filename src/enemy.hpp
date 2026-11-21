#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
    private:
        float radius = 20.f;
        float health = 100.f;
        float maxHealth = 100.f;
        sf::Vector2f position{500, 600};
    public:
        void move(sf::Vector2f dir, float dt);
        void update(float dt);
        void takeDamage(float damage, float iFrame);
        sf::Vector2f getPos() const;
        float getRadius() const;
        float getHealth() const;


};
