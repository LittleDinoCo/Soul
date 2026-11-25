#pragma once
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cmath>
#include <vector>

struct Collide {
    static bool circleOnCircle(sf::Vector2f circle1Position, sf::Vector2f circle2Position, float circle1Radius, float circle2Radius) {
        sf::Vector2f distanceVector = circle1Position - circle2Position;
        float distanceSquared = (distanceVector.x * distanceVector.x + distanceVector.y * distanceVector.y);
        float radiusSum = circle1Radius + circle2Radius;
        return distanceSquared <= radiusSum * radiusSum;
    }

    static bool squareOnCircle(sf::Vector2f circlePosition, float circleRadius, sf::Vector2f squarePosition, sf::Vector2f squareSize, float squareAngleRad) {
        sf::Vector2f widthDir = {-std::sin(squareAngleRad), std::cos(squareAngleRad)};
        sf::Vector2f heightDir = {std::cos(squareAngleRad), std::sin(squareAngleRad)};
        sf::Vector2f squareToCircle = circlePosition - squarePosition;

        float projectedWidth = (squareToCircle.x * widthDir.x) + (squareToCircle.y * widthDir.y);
        float projectedHeight = (squareToCircle.x * heightDir.x) + (squareToCircle.y * heightDir.y);

        float closestWidth = std::clamp(projectedWidth, (-squareSize.x / 2.f), (squareSize.x / 2.f));
        float closestHeight = std::clamp(projectedHeight, (-squareSize.y / 2.f), (squareSize.y / 2.f));

        sf::Vector2f closestPoint = squarePosition + widthDir * closestWidth + heightDir * closestHeight;

        sf::Vector2f distToPoint = circlePosition - closestPoint;

        float distance = std::hypot(distToPoint.x, distToPoint.y);

        return distance <= circleRadius;
    }

    static bool squareOnSquare(float squareAAngleRad, float squareBAngleRad, sf::Vector2f squareAPosition, sf::Vector2f squareBPosition, sf::Vector2f sizeA, sf::Vector2f sizeB) {

        sf::Vector2f widthDirA = {-std::sin(squareAAngleRad), std::cos(squareAAngleRad)};
        sf::Vector2f heightDirA = {std::cos(squareAAngleRad), std::sin(squareAAngleRad)};

        sf::Vector2f widthDirB = {-std::sin(squareBAngleRad), std::cos(squareBAngleRad)};
        sf::Vector2f heightDirB = {std::cos(squareBAngleRad), std::sin(squareBAngleRad)};
        std::vector<sf::Vector2f> allAxis = {widthDirA, widthDirB, heightDirA, heightDirB};
        sf::Vector2f halfSizeA = sizeA / 2.f; 
        sf::Vector2f halfSizeB = sizeB / 2.f; 
        for (const sf::Vector2f& axisVec : allAxis) {
            float projectedA = (squareAPosition.x * axisVec.x) + (squareAPosition.y * axisVec.y);
            float projectedB = (squareBPosition.x * axisVec.x) + (squareBPosition.y * axisVec.y);

            float radiusA = halfSizeA.x * std::abs(widthDirA.x * axisVec.x + widthDirA.y * axisVec.y) + 
                halfSizeA.y * std::abs(heightDirA.x * axisVec.x + heightDirA.y * axisVec.y);
            float radiusB = halfSizeB.x * std::abs(widthDirB.x * axisVec.x + widthDirB.y * axisVec.y) + 
                halfSizeB.y * std::abs(heightDirB.x * axisVec.x + heightDirB.y * axisVec.y);

            float centerDist = std::abs(projectedA - projectedB); 

            if (centerDist > radiusA + radiusB) {
                return false;
            }
        }

    return true;
        

    }

};
