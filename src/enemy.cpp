#include "enemy.hpp"

void Enemy::takeDamage(float damage, float iFrame) {
    if (health >= damage) {
        health -= damage;
    }
    else {
        health = 0;
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


