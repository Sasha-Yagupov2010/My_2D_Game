#include "PlayerBoost.h"


PlayerBoost::PlayerBoost() : rng(std::random_device{}()) {}

// === МЕТОДЫ ДЛЯ ИГРОКА ===

// Активация эффекта
void PlayerBoost::activateSpeed() {
    superSpeed = true;
    speedEndTime = std::chrono::steady_clock::now() +
        std::chrono::seconds(SPEED_DURATION);
}

void PlayerBoost::activateShield() {
    shield = true;
    shieldEndTime = std::chrono::steady_clock::now() +
        std::chrono::seconds(SHIELD_DURATION);
}

void PlayerBoost::activateGod() {
    god = true;
    godEndTime = std::chrono::steady_clock::now() +
        std::chrono::seconds(GOD_DURATION);
}

void PlayerBoost::activateTeleport(int& playerX, int& playerY, int mapWidth, int mapHeight) {
    std::uniform_int_distribution<int> distX(1, mapWidth - 2);
    std::uniform_int_distribution<int> distY(1, mapHeight - 2);
    playerX = distX(rng);
    playerY = distY(rng);
    teleport = true;
}

// Проверка времени эффектов (вызывать каждый кадр/тик)
void PlayerBoost::updateEffects() {
    auto now = std::chrono::steady_clock::now();

    if (superSpeed && now > speedEndTime) {
        superSpeed = false;
    }

    if (god && now > godEndTime) {
        god = false;
    }

    if (shield && now > shieldEndTime) {
        shield = false;
    }
}

// === МЕТОДЫ ДЛЯ КАРТЫ ===

// Получить оставшееся время эффекта (для UI)
int  PlayerBoost::getRemainingSpeedTime() const {
    if (!superSpeed) return 0;
    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(
        speedEndTime - now).count();
    return (remaining > 0) ? static_cast<int>(remaining) : 0;
}

int  PlayerBoost::getRemainingGodTime() const {
    if (!god) return 0;
    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(
        godEndTime - now).count();
    return (remaining > 0) ? static_cast<int>(remaining) : 0;
}

int  PlayerBoost::getRemainingShieldTime() const {
    if (!shield) return 0;
    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(
        shieldEndTime - now).count();
    return (remaining > 0) ? static_cast<int>(remaining) : 0;
}

void PlayerBoost::activateRandomEffect() {
    std::uniform_int_distribution<> dist(0, 3);
    int randomNumber = dist(rng);

    switch (randomNumber)
    {
    case(0):
        activateSpeed();
        break;

    case(1):
        activateGod();
        break;
    case(2):
        activateShield();
        break;
    default:
        std::cout << "ошибка с выбором рандомного эффекта" << std::endl;
        break;
    }
}

