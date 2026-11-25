#pragma once
#include <SFML/System/Vector2.hpp>

enum class EnemyType {
    Bob,
    Joe
};
enum class AttackType {
    Dash,
    Swing
};

struct AttackStats {
    AttackType type;
    bool canInterrupt;
    float damage;
    float windupTime;
    float attackDuration;
    float cooldownTime;
    float speedMultiplier;
    sf::Vector2f attackSize;
};

struct EnemyStats {
    float maxHP;
    float radius;
    float moveSpeed;
    float retreatChance;
    float walkChance;
    float attackDistance;
    AttackStats attack;
};

inline constexpr AttackStats DashStats {
    AttackType::Dash,
    false,
    10.f,
    1.f,
    0.75f,
    1.5f,
    5.f
};

inline constexpr AttackStats SwingStats {
    AttackType::Swing,
    true,
    20.f,
    2.f,
    1.f,
    2.f,
    1.f,
    {20.f, 50.f},

};

inline constexpr EnemyStats BobStats {
    90.f,
    20.f,
    70.f,
    0.005f,
    0.9f,
    200.f,
    DashStats
};

inline constexpr EnemyStats JoeStats {
    120.f,
    30.f,
    50.f,
    0.05f,
    0.5f,
    40.f,
    SwingStats
};


static inline constexpr const EnemyStats& getStats(EnemyType type) {
    switch (type) {
        case EnemyType::Bob: return BobStats;
        case EnemyType::Joe: return JoeStats;
        default: return BobStats;
    }
}
