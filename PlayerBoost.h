#ifndef PlayerBoost_H
#define PlayerBoost_H

#include <Windows.h>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

class PlayerBoost {
private:
    // Таймеры для каждого эффекта
    std::chrono::steady_clock::time_point speedEndTime;
    std::chrono::steady_clock::time_point shieldEndTime;
    std::chrono::steady_clock::time_point godEndTime;

    // Координаты бустов на карте
    struct BoostItem {
        int x, y;
        char type; // 'S'-speed, 'H'-shield, 'G'-god, 'T'-teleport
        bool active;
        std::chrono::steady_clock::time_point spawnTime;
    };

    std::vector<BoostItem> activeBoosts;
    std::mt19937 rng;

    // Время действия эффектов (в секундах)
    const int SPEED_DURATION = 5;
    const int SHIELD_DURATION = 0; // пока флаг не сбросится
    const int GOD_DURATION = 3;

public:
    bool god = false;
    bool holdFlag = false; // щит для флага
    bool teleport = false; // активирован телепорт
    bool superSpeed = false;

    PlayerBoost() {}

    // === МЕТОДЫ ДЛЯ ИГРОКА ===

    // Активация эффекта
    void activateSpeed();

    void activateShield();

    void activateGod();


    void activateTeleport(int& playerX, int& playerY, int mapWidth, int mapHeight);


    // Проверка времени эффектов (вызывать каждый кадр/тик)
    void updateEffects();


    // Сброс щита (при потере флага)
    void resetShield();


    // === МЕТОДЫ ДЛЯ КАРТЫ ===

    // Создать случайный буст на карте
    void spawnRandomBoost(int mapWidth, int mapHeight, const std::vector<std::vector<int>>& map);


    // Обновить бусты на карте (исчезновение через время)
    void updateBoosts();

    // Проверить коллизию игрока с бустами
    char checkCollision(int playerX, int playerY);

    // Получить список активных бустов для отрисовки
    const std::vector<BoostItem>& getActiveBoosts() const {
        return activeBoosts;
    }

    // Очистить все бусты с карты
    void clearAllBoosts();

    // Получить оставшееся время эффекта (для UI)
    int getRemainingSpeedTime() const {}

    int getRemainingGodTime() const {}
};

#endif // PlayerBoost_H