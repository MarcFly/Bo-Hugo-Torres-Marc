#ifndef __ENEMY_BROWNCOOKIE_H__
#define __ENEMY_BROWNCOOKIE_H__

#include "Enemy.h"
#include "Path.h"
#include "p2Point.h"

class Enemy_Browncookie : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	int original_x = 0;
	Animation turn_up;
	Animation turn_down;
	Animation turn_left;

	iPoint original_pos;

	Path pathing;


public:

	Enemy_Browncookie(int x, int y);

	void Move();
};

#endif // __ENEMY_BROWNCOOKIE_H__