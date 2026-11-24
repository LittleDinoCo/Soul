#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/System/Vector2.hpp>

class Enemy;

class Player {
    private:
        const float topSpeed = 300.f;
        float radius = 20.f;
        float acceleration = 1000.f;
        float maxSpeed = 300.f;
        float friction = 0.95f;
        float health = 100.f;
        float iFrameHit = 0.f;
        float iFrameDash = 0.f;
        float damageFlash = 0.f;
        float maxHealth = 100.f;
        float attackDuration = 0.f;
        float isSiphoning = 0.f; 
        bool alive = true;
        bool siphoned = false;
        sf::Vector2f velocity{0, 0};
        sf::Vector2f position{906, 600};
        sf::Vector2f attackDir;
        int souls[3] = {0, 0, 0};
        sf::CircleShape shape;
    public:
        Player();
        void move(sf::Vector2f dir, float dt);
        void update(float dt);
        void takeDamage(float damage, float iFrame);
        void attack(Enemy& enemy, sf::RenderWindow& window, float attackDur);
        void siphon(Enemy& enemy, sf::RenderWindow& window);
        void draw(sf::RenderWindow& window);
        bool attackHitsEnemy(const Enemy& enemy, sf::Vector2f attackPos, float angleRad);
        sf::Vector2f getPos() const;
        float getAttackDuration() const;
        float getRadius() const;
        float getHealth() const;
        bool getAlive() const;



};
