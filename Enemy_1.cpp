#include "Application.h"
#include "Enemy_1.h"
#include "ModuleCollision.h"
#include <stdlib.h>
#include <time.h>

Enemy_1::Enemy_1(int x, int y) : Enemy(x, y)
{
	fly.PushBack({0,0,18,27});
	animation = &fly;
	srand(time(NULL));

	collider = App->collision->AddCollider({0, 0, 18, 27}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	
	original_y = y;
	xspeed = 1;
	yspeed = 1;
}

void Enemy_1::Move()
{
	int reverse_xspeed = xspeed*(-1);
	int reverse_yspeed = yspeed*(-1);

	if (value_between(0, 480) < 450)
	{
		xspeed = reverse_xspeed;
	}

	if (value_between(0, 480) < 450)
	{
		yspeed = reverse_yspeed;
	}
	
	if (xspeed == 1)
	{
		position.x += 0.5;
	}
	else
	{
		position.x -= 0.5;
	}

	if (yspeed == 1)
	{
		position.y += 0.5;
	}
	else
	{
		position.y -= 0.5;
	}
	position.y -= 1;
}
int Enemy_1::value_between(int min, int max)
{
	return rand() % (max - min + 1) + min;
}