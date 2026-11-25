#include "enemy.hpp"
#include "player.hpp"
#include "enemyTypes.hpp"
#include "maths.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>


Enemy::Enemy() {
    EnemyStats stats = getStats(EnemyType::Bob);
    maxHP = stats.maxHP;
    moveSpeed = stats.moveSpeed;
    radius = stats.radius;
    retreatChance = stats.retreatChance;
    walkChance = stats.walkChance;
    attackDistance = stats.attackDistance;
    attackDamage = stats.attack.damage;
    windupTime = stats.attack.windupTime;
    attackDuration = stats.attack.attackDuration;
    cooldownTime = stats.attack.cooldownTime;
    speedMultiplier = stats.attack.speedMultiplier;
    type = stats.attack.type;
    attackSize = stats.attack.attackSize;
    canInterrupt = stats.attack.canInterrupt;
    health = maxHP;
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
}

void Enemy::draw(sf::RenderWindow& window) {
    if (alive) {
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Red);
        if (damageFlashTimer.read() > 0) {
            shape.setFillColor(sf::Color::White);
        }
        window.draw(shape);
    }
}

void Enemy::update(sf::Vector2f targetPosition, float targetRadius, float dt) {
    iFrameHitTimer.tick(dt);
    damageFlashTimer.tick(dt);
    attackDurationTimer.tick(dt);
    attackCooldownTimer.tick(dt);

    chooseIntent(targetPosition, targetRadius, dt);

    position += (velocity * dt);
}

void Enemy::chooseIntent(sf::Vector2f targetPosition, float targetRadius, float dt) {

    
    sf::Vector2f enemyToTarget = targetPosition - position;
    float length = std::hypot(enemyToTarget.x, enemyToTarget.y);
    sf::Vector2f targetDir = enemyToTarget / length;
    if (attackDurationTimer.read() == 0) {

        if (attackCooldownTimer.read() > 0) {
            velocity = targetDir * moveSpeed * 0.5f;
            return;
        }
        //If too far away
        if (length > attackDistance) {
            move(targetDir, dt);
            return;
        }
            
        if (attackCooldownTimer.read() == 0) {
            //Random chance to retreat
            if (rollChance(retreatChance)) {
                move(targetDir, dt);
                retreat();
                return;
            }
            if (rollChance(walkChance)) {
                move(targetDir, dt);
                return;
            }

            //If not retreating
            move(targetDir, dt);
            attack();
        
        }
    }
   

}
void Enemy::retreat() {
    velocity = -velocity * speedMultiplier;
    attackCooldownTimer.start(cooldownTime + attackDuration);
    attackDurationTimer.start(attackDuration);
}

void Enemy::wait() {
    velocity = {0, 0};
}
void Enemy::move(sf::Vector2f targetDir, float dt) {
    velocity = targetDir * moveSpeed;
}
void Enemy::attack() {
    velocity *= speedMultiplier;
    attackCooldownTimer.start(cooldownTime + attackDuration);
    attackDurationTimer.start(attackDuration);
}
void Enemy::takeDamage(float damage, float iFrame) {
   if (iFrameHitTimer.read() == 0) {
        if (health >= damage) {
            damageFlashTimer.start(0.2f);
            health -= damage;
        }
        else {
            health = 0;
        }
        if (health == 0) {
            alive = false;
        }
        iFrameHitTimer.start(iFrame);
    }

}
void Enemy::knockback(float distance, sf::Vector2f direction) {
    if (iFrameHitTimer.read() == 0 && canInterrupt) {
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
float Enemy::getDamage() const {
    return attackDamage;
}
int Enemy::getType() const {
    return 1;
}
bool Enemy::getAlive() const {
    return alive;
}


