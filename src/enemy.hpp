#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "timer.hpp"
class Player;

class Enemy {
    private:
        float radius = 20.f;
        float health = 100.f;
        float maxHealth = 100.f;
        Timer iFrameHit;
        Timer damageFlashTime;
        Timer attackCooldown;
        Timer attackDuration;
        bool alive =  true;
        sf::Vector2f velocity{0, 0};
        sf::Vector2f position{500, 600};
        sf::CircleShape shape;
    public:
        Enemy();
        void move(sf::Vector2f targetPos, float dt);
        void update(const Player& target, float dt);
        void attack();
        void takeDamage(float damage, float iFrame);
        void knockback(float distance, sf::Vector2f direction);
        void draw(sf::RenderWindow& window);
        sf::Vector2f getPos() const;
        float getRadius() const;
        float getHealth() const;
        int getType() const;
        bool getAlive() const;


};
