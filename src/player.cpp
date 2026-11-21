#include "player.hpp"
#include "enemy.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>


void Player::move(sf::Vector2f dir, float dt) {
    float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    velocity += dir * acceleration * dt;
    if (speed > maxSpeed) {
        velocity = (velocity / speed) * maxSpeed;
    }
    if (dir.x == 0) {
        velocity.x *= friction;
    }
    if (dir.y == 0) {
        velocity.y *= friction;
    }
}

void Player::update(float dt) {
    if (iFrameHit > 0) {
        iFrameHit -= dt;
        if (iFrameHit < 0) {
            iFrameHit = 0;
        }
    }
    if (iFrameDash > 0) {
        iFrameDash -= dt;
        if (iFrameDash < 0) {
            iFrameDash = 0;
        }
    }


    position += (velocity * dt);
}
void Player::takeDamage(float damage, float iFrame) {
    if (iFrameHit == 0 && iFrameDash == 0) {
        if (health >= damage) {
            health -= damage;
        }
        else {
            health = 0;
        }
        std::cout << health << "\n";
        iFrameHit += iFrame;
    }
}
void Player::attack(Enemy& enemy, sf::Vector2f mousePos, sf::RenderWindow& window) {
    sf::Vector2f mouseToPlayer = mousePos - position;
    float length = std::hypot(mouseToPlayer.x, mouseToPlayer.y);

    if (length == 0.f) return;

    sf::Vector2f attackDir = mouseToPlayer / length;
    sf::Vector2f attackPos = position + attackDir * (radius + 25.f);

    float angleRad = std::atan2(attackDir.y, attackDir.x);
    float angleDeg = angleRad * 180.f / 3.14159265f;

    sf::Vector2f widthDir = {-std::sin(angleRad), std::cos(angleRad)};
    sf::Vector2f heightDir = {std::cos(angleRad), std::sin(angleRad)};
    sf::Vector2f swordToEnemy = enemy.getPos() - attackPos;

    float projectedWidth = (swordToEnemy.x * widthDir.x) + (swordToEnemy.y * widthDir.y);
    float projectedHeight = (swordToEnemy.x * heightDir.x) + (swordToEnemy.y * heightDir.y);

    float closestWidth = std::clamp(projectedWidth, -10.f, 10.f);
    float closestHeight = std::clamp(projectedHeight, -25.f, 25.f);

    sf::Vector2f closestPoint = attackPos + widthDir * closestWidth + heightDir * closestHeight;

    sf::Vector2f distToPoint = enemy.getPos() - closestPoint;

    float distance = hypot(distToPoint.x, distToPoint.y);

    sf::RectangleShape attackBox({20.f, 50.f});
    attackBox.setOrigin({10.f, 25.f});
    attackBox.setRotation(sf::degrees(angleDeg));
    attackBox.setPosition(attackPos);
    attackBox.setFillColor(sf::Color::Green);

    window.draw(attackBox);
    if (distance <= enemy.getRadius()) {
        enemy.takeDamage(20.f, 0.5f);
    }
}

sf::Vector2f Player::getPos() const {
    return position;
}
float Player::getRadius() const {
    return radius;
}
float Player::getHealth() const {
    return health;
}


