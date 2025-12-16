#ifndef ShootGun_H
#define ShootGun_H

#include <cmath>

class ShootGun {
public:
	float startX;
	float startY;

	float targetX;
	float targetY;

	int count;
	int max_count;

	int visible=false;

	ShootGun(int max_count=15, int count=15);

	void setPos(float, float);
	void setTarget(float, float);
	bool step(float);
	void unvis();
	void resetTarget();

	bool checkDestroy(float, float, float);
};


#endif // !ShootGun_H

