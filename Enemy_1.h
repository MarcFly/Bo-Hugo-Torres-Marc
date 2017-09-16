#ifndef __ENEMY_NUMBER1_H__
#define __ENEMY_NUMBER1_H__

#include "Enemy.h"

class Enemy_1 : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
public:

	int value_between(int,int);
	Enemy_1(int x, int y);
	int xspeed;
	int yspeed;
	void Move();
};

#endif // __ENEMY_REDBIRD_H__