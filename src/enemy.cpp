#include "enemy.hpp"
#include "player.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>

Enemy::Enemy() {
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
}

void Enemy::draw(sf::RenderWindow& window) {
    if (alive) {
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
        if (damageFlash > 0) {
            shape.setFillColor(sf::Color::White);
        }
        window.draw(shape);
    }
}

void Enemy::update(const Player& target, float dt) {
    if (iFrameHit > 0) {
        iFrameHit -= dt;
        if (iFrameHit < 0) {
            iFrameHit = 0;
        }
    }
    if (damageFlash > 0) {
        damageFlash -= dt;
        if (damageFlash < 0) {
            damageFlash = 0;
        }
    }
    if (attackDuration > 0) {
        attackDuration -= dt;
        if (attackDuration < 0) {
            attackDuration = 0;
        }
    }
    if (attackCooldown > 0) {
        attackCooldown -= dt;
        if (attackCooldown < 0) {
            attackCooldown = 0;
        }
    }
    sf::Vector2f enemyToTarget = target.getPos() - position;
    float length = std::sqrt((enemyToTarget.x * enemyToTarget.x) + (enemyToTarget.y * enemyToTarget.y));

    if (length < 200 + radius + target.getRadius() && attackCooldown == 0) {
        attack();
    }
    else if (attackDuration == 0) {
        move(target.getPos(), dt);
    }
    position += (velocity * dt);
}
void Enemy::move(sf::Vector2f targetPos, float dt) {
    sf::Vector2f enemyToTarget = targetPos - position;
    float length = std::sqrt((enemyToTarget.x * enemyToTarget.x) + (enemyToTarget.y * enemyToTarget.y));
    sf::Vector2f targetDir = enemyToTarget / length;
    velocity = targetDir * 50.f;;
}
void Enemy::attack() {
    velocity *= 5.f;
    attackCooldown = 1;
    attackDuration = 0.5f;
}
void Enemy::takeDamage(float damage, float iFrame) {
   if (iFrameHit == 0) {
        if (health >= damage) {
            damageFlash = 0.2f;
            health -= damage;
        }
        else {
            health = 0;
        }
        if (health == 0) {
            alive = false;
        }
        iFrameHit += iFrame;
    }

}
void Enemy::knockback(float distance, sf::Vector2f direction) {
    if (iFrameHit == 0) {
        attackDuration = 0;
        position += distance * direction;
    }
}
sf::Vector2f Enemy::getPos() const {
    return position;
}
float Enemy::getRadius() const {
    return radius;
}
float Enemy::getHealth() const {
    return health;
}
int Enemy::getType() const {
    return 1;
}
bool Enemy::getAlive() const {
    return alive;
}


