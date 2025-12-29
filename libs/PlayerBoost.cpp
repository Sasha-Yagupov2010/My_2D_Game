#include "PlayerBoost.h"
#include <iostream>

PlayerBoost::PlayerBoost() : rng(std::random_device{}()) {
    // Инициализация времени задержки
    delay = std::chrono::steady_clock::now();
}

// === МЕТОДЫ ДЛЯ ИГРОКА ===

// Активация эффекта
void PlayerBoost::activateSpeed() {
    if (!canActivateNewEffect()) return;

    superSpeed = true;
    speedEndTime = std::chrono::steady_clock::now() +
        std::chrono::seconds(SPEED_DURATION);

    delay = std::chrono::steady_clock::now() +
        std::chrono::seconds(SPEED_DURATION) +
        std::chrono::seconds(DELAY_DURATION);
}

void PlayerBoost::activateShield() {
    if (!canActivateNewEffect()) return;

    shield = true;
    shieldEndTime = std::chrono::steady_clock::now() +
        std::chrono::seconds(SHIELD_DURATION);

    delay = std::chrono::steady_clock::now() +
        std::chrono::seconds(SHIELD_DURATION) +
        std::chrono::seconds(DELAY_DURATION);
}

void PlayerBoost::activateGod() {
    if (!canActivateNewEffect()) return;

    god = true;
    godEndTime = std::chrono::steady_clock::now() +
        std::chrono::seconds(GOD_DURATION);

    delay = std::chrono::steady_clock::now() +
        std::chrono::seconds(GOD_DURATION) +
        std::chrono::seconds(DELAY_DURATION);
}

void PlayerBoost::clearAllEffects() {
    god = false;
    superSpeed = false;
    shield = false;
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
int PlayerBoost::getRemainingSpeedTime() const {
    if (!superSpeed) return 0;
    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(
        speedEndTime - now).count();
    return (remaining > 0) ? static_cast<int>(remaining) : 0;
}

int PlayerBoost::getRemainingGodTime() const {
    if (!god) return 0;
    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(
        godEndTime - now).count();
    return (remaining > 0) ? static_cast<int>(remaining) : 0;
}

int PlayerBoost::getRemainingShieldTime() const {
    if (!shield) return 0;
    auto now = std::chrono::steady_clock::now();
    auto remaining = std::chrono::duration_cast<std::chrono::seconds>(
        shieldEndTime - now).count();
    return (remaining > 0) ? static_cast<int>(remaining) : 0;
}

void PlayerBoost::activateRandomEffect() {
    if (!canActivateNewEffect()) return;

    std::uniform_int_distribution<> dist(0, 2);
    int randomNumber = dist(rng);

    switch (randomNumber) {
    case 0:
        activateSpeed();
        break;
    case 1:
        activateGod();
        break;
    case 2:
        activateShield();
        break;
    default:
        std::cout << "Ошибка с выбором рандомного эффекта: " << randomNumber << std::endl;
        break;
    }
}

bool PlayerBoost::canActivateNewEffect() const {
    auto now = std::chrono::steady_clock::now();

    // Проверяем, активен ли какой-либо эффект
    if (god || shield || superSpeed) {
        return false;
    }

    // Проверяем, прошла ли задержка
    if (now < delay) {
        return false;
    }

    return true;
}