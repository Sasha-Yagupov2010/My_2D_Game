#ifndef PLAYERBOOST_H
#define PLAYERBOOST_H

#include <chrono>
#include <random>

class PlayerBoost {
private:
    // Таймеры для каждого эффекта
    std::chrono::steady_clock::time_point speedEndTime;
    std::chrono::steady_clock::time_point shieldEndTime;
    std::chrono::steady_clock::time_point godEndTime;
    std::chrono::steady_clock::time_point delay;

    std::mt19937 rng;

    // Время действия эффектов (в секундах)
    static constexpr int DELAY_DURATION = 15;
    static constexpr int SPEED_DURATION = 10;
    static constexpr int SHIELD_DURATION = 10;
    static constexpr int GOD_DURATION = 5;



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
    bool canActivateNewEffect() const;
    void activateRandomEffect();

    // Очистить все бусты с карты
    void clearAllEffects();

    // Получить оставшееся время эффекта (для UI)
    int getRemainingSpeedTime() const;
    int getRemainingGodTime() const;
    int getRemainingShieldTime() const;

    // Геттеры для проверки состояния эффектов
    bool isGod_On() const { return god; }
    bool isShield_On() const { return shield; }
    bool isSpeed_On() const { return superSpeed; }

    std::string UI_active_mode();

};

#endif // PLAYERBOOST_H