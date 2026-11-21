#include "enemy.hpp"

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
sf::Vector2f Enemy::getPos() const {
    return position;
}
float Enemy::getRadius() const {
    return radius;
}
float Enemy::getHealth() const {
    return health;
}


