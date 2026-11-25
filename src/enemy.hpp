#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "timer.hpp"
#include "enemyTypes.hpp"
class Player;

class Enemy {
    private:
        //From enemyTypes.hpp
        float maxHP;
        float moveSpeed;
        float radius;
        float retreatChance;
        float walkChance;
        float attackDistance;
        float attackDamage;
        float windupTime;
        float attackDuration;
        float cooldownTime;
        float speedMultiplier;
        bool canInterrupt;
        AttackType type;
        sf::Vector2f attackSize;


        //The Rest
        float health = 100.f;
        Timer iFrameHitTimer;
        Timer damageFlashTimer;
        Timer attackCooldownTimer;
        Timer attackDurationTimer;
        bool alive =  true;
        sf::Vector2f velocity{0, 0};
        sf::Vector2f position{500, 600};
        sf::CircleShape shape;
    public:
        Enemy();
        void move(sf::Vector2f targetDir, float dt);
        void update(sf::Vector2f targetPosition, float targetRadius, float dt);
        void chooseIntent(sf::Vector2f targetPosition, float targetRadius, float dt);
        void attack();
        void wait();
        void retreat();
        void takeDamage(float damage, float iFrame);
        void knockback(float distance, sf::Vector2f direction);
        void draw(sf::RenderWindow& window);
        sf::Vector2f getPos() const;
        float getRadius() const;
        float getHealth() const;
        float getDamage() const;
        int getType() const;
        bool getAlive() const;


};
