#ifndef ShootGun_H
#define ShootGun_H

class ShootGun {
public:
	int startX;
	int startY;

	int targetX;
	int targetY;

	int speed;
	int size;
	const int maxquantity = 15;
	int count;

	void setTarget(int, int);
	void setLocation(int, int);



};

#endif // !ShutGun_H
