#include "Application.h"
#include "Enemy_BrownCookie.h"
#include "ModuleCollision.h"
#include "Path.h"

Enemy_Browncookie::Enemy_Browncookie(int x, int y) : Enemy(x, y)
{
	turn_up.PushBack({ 68,72,27,23 });
	turn_up.speed = 0.0f;

	turn_left.PushBack({ 3 ,72,27,23 });//166 38
	turn_left.speed = 0.0f;

	turn_down.PushBack({ 166,38,27,23 });
	turn_down.speed = 0.0f;

	animation = &turn_left;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	pathing.PushBack({-1.0f, -0.5f}, 100);
	pathing.PushBack({ -1.0f, 0.5f }, 80);
	pathing.PushBack({ -1.0f, 1.0f }, 80);

	original_pos.y = y;
	original_pos.x = x;

}

void Enemy_Browncookie::Move()
{
	position = original_pos + pathing.GetCurrentPosition();

}
