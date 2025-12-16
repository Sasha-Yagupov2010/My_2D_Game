#include "ShootGun.h"

ShootGun::ShootGun(int max_count, int count) :max_count(max_count), count(count) {}

void ShootGun::setPos(float x, float y)
	{ startX = x; startY = y; }


void ShootGun::setTarget(float x, float y)
	{ targetX = x; targetY = y; }


bool ShootGun::step(float stepSize) {

    // 1. ¬ычисл€ем рассто€ние до цели
    float dx = targetX - startX;
    float dy = targetY - startY;
    float distance = sqrt(dx * dx + dy * dy);

    // 2. ≈сли уже очень близко к цели - завершаем
    if (distance <= stepSize) {
        startX = targetX;
        startY = targetY;
        return true;  // достигли цели
    }

    // 3. ¬ычисл€ем единичный вектор направлени€
    float dirX = dx / distance;
    float dirY = dy / distance;

    // 4. ƒелаем шаг
    startX += dirX * stepSize;
    startY += dirY * stepSize;

    return false;  // еще не достигли
}


void ShootGun::unvis() 
	{ visible = !visible; }

void ShootGun::resetTarget() {
    targetX = -1;
    targetY = -1;
}

bool ShootGun::checkDestroy(float x, float y, float size)
{
    int distance = sqrt(pow((x - startX), 2) + pow((y - startY), 2));
    if (distance < size && visible) return true;
    return false;
}