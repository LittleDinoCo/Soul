#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>
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
        float damageFlash = 0.f;
        float maxHealth = 100.f;
        float attackDuration = 0.5f;
        bool alive = true;
        sf::Vector2f velocity{0, 0};
        sf::Vector2f position{906, 600};
        sf::Vector2f attackDir;
        sf::CircleShape shape;
    public:
        Player();
        void move(sf::Vector2f dir, float dt);
        void update(float dt);
        void takeDamage(float damage, float iFrame);
        void attack(Enemy& enemy, sf::RenderWindow& window, float attackDur);
        void draw(sf::RenderWindow& window);
        bool attackHitsEnemy(Enemy& enemy, sf::Vector2f attackPos, float angleRad);
        sf::Vector2f getPos() const;
        float getAttackDuration() const;
        float getRadius() const;
        float getHealth() const;
        bool getAlive() const;



};
