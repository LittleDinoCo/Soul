#include "enemy.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

Enemy::Enemy() {
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
    shape.setFillColor(sf::Color::Red);
}

void Enemy::draw(sf::RenderWindow& window) {
    shape.setPosition(position);
    window.draw(shape);
}

void Enemy::update(float dt) {
    if (iFrameHit > 0) {
        iFrameHit -= dt;
        if (iFrameHit < 0) {
            iFrameHit = 0;
        }
    }
}
void Enemy::takeDamage(float damage, float iFrame) {
   if (iFrameHit == 0) {
        if (health >= damage) {
            health -= damage;
        }
        else {
            health = 0;
        }
        iFrameHit += iFrame;
    }

}
void Enemy::knockback(float distance, sf::Vector2f direction) {
    if (iFrameHit == 0) {
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


