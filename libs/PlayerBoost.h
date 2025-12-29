#ifndef PlayerBoost_H
#define PlayerBoost_H

#include <Windows.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

class PlayerBoost {
private:
    // Таймеры для каждого эффекта
    std::chrono::steady_clock::time_point speedEndTime;
    std::chrono::steady_clock::time_point shieldEndTime;
    std::chrono::steady_clock::time_point godEndTime;
    std::chrono::steady_clock::time_point delay;

    std::mt19937 rng;

    // Время действия эффектов (в секундах)
    const int SPEED_DURATION = 10;
    const int SHIELD_DURATION = 10; 
    const int GOD_DURATION = 5;

public:
    bool god = false;
    bool shield = false; // щит для флага
    bool superSpeed = false;

    PlayerBoost();

    // === МЕТОДЫ ДЛЯ ИГРОКА ===

    // Активация эффекта
    void activateSpeed();

    void activateShield();

    void activateGod();


    // Проверка времени эффектов (вызывать каждый кадр/тик)
    void updateEffects();


    void activateRandomEffect();


    // Очистить все бусты с карты
    void clearAllEffects();

    // Получить оставшееся время эффекта (для UI)
    int getRemainingSpeedTime() const;

    int getRemainingGodTime() const;

    int getRemainingShieldTime() const;

    bool isGod_On() { return god; }
    bool isShield_On() { return shield; }
    bool isSpeed_On() { return superSpeed; }

};

#endif // PlayerBoost_H