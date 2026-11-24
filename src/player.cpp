#include "player.hpp"
#include "enemy.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>

Player::Player() {
    shape.setRadius(radius);
    shape.setOrigin({radius, radius});
}

void Player::draw(sf::RenderWindow& window) {
    if (alive) {
        shape.setPosition(position);
        shape.setFillColor(sf::Color::Green);
        if (damageFlashTime.read() > 0) {
            shape.setFillColor(sf::Color::White);
        }
        window.draw(shape);
    }
}

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
    iFrameHit.tick(dt);
    iFrameDash.tick(dt);
    damageFlashTime.tick(dt);
    attackDuration.tick(dt);
    siphonTime.tick(dt);


    position += (velocity * dt);
}
void Player::takeDamage(float damage, float iFrame) {
    if (iFrameHit.read() == 0 && iFrameDash.read() == 0) {
        if (health >= damage) {
            health -= damage;
            damageFlashTime.start(0.2f);
        }
        else {
            health = 0;
        }
        if (health == 0) {
            alive = false;
        }
        cancelSiphon();
        iFrameHit.start(iFrame);
    }
}
bool Player::attackHitsEnemy(const Enemy& enemy, sf::Vector2f attackPos, float angleRad) {
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

    if (distance <= enemy.getRadius()) {
        return true;
    }

    return false;
}

void Player::attack(Enemy& enemy, sf::RenderWindow& window, float attackDur) {
    if (attackDuration.read() > 0) {
                sf::Vector2f attackPos = position + attackDir * (radius + 25.f);

        float angleRad = std::atan2(attackDir.y, attackDir.x);
        float angleDeg = angleRad * 180.f / 3.14159265f;

        sf::RectangleShape attackBox({20.f, 50.f});
        attackBox.setOrigin({10.f, 25.f});
        attackBox.setRotation(sf::degrees(angleDeg));
        attackBox.setPosition(attackPos);
        attackBox.setFillColor(sf::Color::Blue);
        window.draw(attackBox);
        if (attackHitsEnemy(enemy, attackPos, angleRad)) {
            enemy.knockback(40.f, attackDir);
            enemy.takeDamage(20.f, 0.5f);
        }
        return;
    }
    sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
    sf::Vector2f mouseToPlayer = mousePos - position;
    float length = std::hypot(mouseToPlayer.x, mouseToPlayer.y);

    if (length == 0.f) return;
    attackDir = mouseToPlayer / length;

    attackDuration.start(attackDur);
}

void Player::siphon(Enemy& enemy, sf::RenderWindow& window) {
    //Stops it if key released
        //Debug Only
    sf::CircleShape siphonRadius(100 + radius + enemy.getRadius());
    siphonRadius.setOrigin({siphonRadius.getRadius(), siphonRadius.getRadius()});
    siphonRadius.setPosition(enemy.getPos());
    siphonRadius.setFillColor(sf::Color::Magenta);
    window.draw(siphonRadius);

    //Actual Stuff
    sf::Vector2f distance = enemy.getPos() - position;
    float length = std::sqrt((distance.x * distance.x) + (distance.y * distance.y)); 
    if (enemy.getRadius() + radius + 100 >= length && enemy.getHealth() <= 30 ) {
        if (siphoning == true && siphonTime.read() == 0.f) {
            int possible = 2;
            for (int soul = 0; soul < std::size(souls); soul ++) {
                if (souls[soul] == 0) {
                    possible = soul;
                    break;
                }
            }

            souls[possible] = enemy.getType();
            std::cout << souls[0] << " " << souls[1] << " " << souls[2] << "\n";
            enemy.takeDamage(1000000.f, 0.f);
            cancelSiphon();
            return;

        }
    
    }
    else {
        cancelSiphon();
        return;
    }
    if (!siphoning) {
        siphonTime.start(3.f);
        maxSpeed = topSpeed / 2;
        siphoning = true;
    }

}
void Player::cancelSiphon() {
    siphonTime.stop();
    siphoning = false;
    maxSpeed = topSpeed;
}
sf::Vector2f Player::getPos() const {
    return position;
}
float Player::getAttackDuration() const {
    return attackDuration.read();
}
float Player::getRadius() const {
    return radius;
}
float Player::getHealth() const {
    return health;
}
bool Player::getAlive() const {
    return alive;
}


