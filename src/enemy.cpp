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
        if (damageFlashTime.read() > 0) {
            shape.setFillColor(sf::Color::White);
        }
        window.draw(shape);
    }
}

void Enemy::update(const Player& target, float dt) {
    iFrameHit.tick(dt);
    damageFlashTime.tick(dt);
    attackDuration.tick(dt);
    attackCooldown.tick(dt);



    sf::Vector2f enemyToTarget = target.getPos() - position;
    float length = std::sqrt((enemyToTarget.x * enemyToTarget.x) + (enemyToTarget.y * enemyToTarget.y));

    if (length < 200 + radius + target.getRadius() && attackCooldown.read() == 0) {
        attack();
    }
    else if (attackDuration.read() == 0) {
        move(target.getPos(), dt);
    }
    position += (velocity * dt);
}
void Enemy::move(sf::Vector2f targetPos, float dt) {
    sf::Vector2f enemyToTarget = targetPos - position;
    float length = std::sqrt((enemyToTarget.x * enemyToTarget.x) + (enemyToTarget.y * enemyToTarget.y));
    sf::Vector2f targetDir = enemyToTarget / length;
    velocity = targetDir * 50.f;
}
void Enemy::attack() {
    velocity *= 5.f;
    attackCooldown.start(1.f);
    attackDuration.start(0.5f);
}
void Enemy::takeDamage(float damage, float iFrame) {
   if (iFrameHit.read() == 0) {
        if (health >= damage) {
            damageFlashTime.start(0.2f);
            health -= damage;
        }
        else {
            health = 0;
        }
        if (health == 0) {
            alive = false;
        }
        iFrameHit.start(iFrame);
    }

}
void Enemy::knockback(float distance, sf::Vector2f direction) {
    if (iFrameHit.read() == 0) {
        attackDuration.stop();
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


