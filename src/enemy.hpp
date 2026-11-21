#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

class Enemy {
    private:
        float radius = 20.f;
        float health = 100.f;
        float maxHealth = 100.f;
        float iFrameHit = 0.5f;
        bool alive =  true;
        sf::Vector2f position{500, 600};
        sf::CircleShape shape;
    public:
        Enemy();
        void move(sf::Vector2f dir, float dt);
        void update(float dt);
        void takeDamage(float damage, float iFrame);
        void knockback(float distance, sf::Vector2f direction);
        void draw(sf::RenderWindow& window);
        sf::Vector2f getPos() const;
        float getRadius() const;
        float getHealth() const;
        bool getAlive() const;


};
