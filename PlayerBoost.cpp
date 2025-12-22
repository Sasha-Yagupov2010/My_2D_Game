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
    holdFlag = true;
    // Щит действует пока флаг не сбросят
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

    // Щит сбрасывается отдельно при потере флага
}

// Сброс щита (при потере флага)
void PlayerBoost::resetShield() {
    holdFlag = false;
}

// === МЕТОДЫ ДЛЯ КАРТЫ ===

// Создать случайный буст на карте
void PlayerBoost::spawnRandomBoost(int mapWidth, int mapHeight, const std::vector<std::vector<int>>& map) {
    std::uniform_int_distribution<int> distType(0, 3);
    std::uniform_int_distribution<int> distX(1, mapWidth - 2);
    std::uniform_int_distribution<int> distY(1, mapHeight - 2);

    char types[] = { 'S', 'H', 'G', 'T' };
    char type = types[distType(rng)];

    // Ищем свободное место (где нет стены)
    int x, y;
    int attempts = 0;
    do {
        x = distX(rng);
        y = distY(rng);
        attempts++;
    } while (map[y][x] == 1 && attempts < 50); // 1 - стена

    if (attempts < 50) {
        BoostItem newBoost{ x, y, type, true, std::chrono::steady_clock::now() };
        activeBoosts.push_back(newBoost);
    }
}

// Обновить бусты на карте (исчезновение через время)
void PlayerBoost::updateBoosts() {
    auto now = std::chrono::steady_clock::now();
    auto duration = std::chrono::seconds(30); // Буст живет 30 секунд

    activeBoosts.erase(
        std::remove_if(activeBoosts.begin(), activeBoosts.end(),
            [now, duration](const BoostItem& boost) {
                return !boost.active || (now - boost.spawnTime) > duration;
            }),
        activeBoosts.end()
    );
}

// Проверить коллизию игрока с бустами
char PlayerBoost::checkCollision(int playerX, int playerY) {
    for (auto& boost : activeBoosts) {
        if (boost.active && boost.x == playerX && boost.y == playerY) {
            boost.active = false; // Подобрали
            return boost.type;
        }
    }
    return '0'; // Ничего не подобрали
}


// Очистить все бусты с карты
void PlayerBoost::clearAllBoosts() {
    activeBoosts.clear();
}

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