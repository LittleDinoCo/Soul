#include "player.hpp"
#include <cmath>

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
    position += (velocity * dt);
}
void Player::takeDamage(float damage) {
    if (health >= damage) {
        health -= damage;
    }
    else {
        health = 0;
    }
}
sf::Vector2f Player::getPos() const {
    return position;
}
float Player::getRadius() const {
    return radius;
}

