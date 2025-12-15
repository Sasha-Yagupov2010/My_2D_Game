#ifndef ShootGun_H
#define ShootGun_H

#include <cmath>

class ShootGun {
public:
	int startX;
	int startY;

	int targetX;
	int targetY;

	int count;
	int max_count;

	int visible=false;

	ShootGun(int max_count=15, int count=15);

	void setPos(int, int);
	void setTarget(int, int);
	bool step(float);
	void unvis();
};


#endif // !ShootGun_H

