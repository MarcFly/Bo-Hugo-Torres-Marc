#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleSceneIntro.h"
#include "ModuleSceneSpace.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	// idle animation (just the ship)
	/*idle.PushBack({66, 1, 32, 14});

	// move upwards
	up.PushBack({100, 1, 32, 14});
	up.PushBack({132, 0, 32, 14});
	up.loop = false;
	up.speed = 0.1f;

	// Move down
	down.PushBack({33, 1, 32, 14});
	down.PushBack({0, 1, 32, 14});
	down.loop = false;
	down.speed = 0.1f;
	*/
	//Gun.Smoke movement animationes

	//idle / up / down
	idle.PushBack({ 23, 15, 22, 32 });
	idle.PushBack({ 63, 15, 22, 32 });
	idle.PushBack({ 103, 15, 22, 32 });
	idle.PushBack({ 142, 15, 24, 32 });
	idle.PushBack({ 183, 15, 22, 32 });
	idle.speed = 0.2f;

	// move left
	right.PushBack({ 25, 56, 22, 32 });
	right.PushBack({ 65, 56, 22, 32 });
	right.PushBack({ 105, 56, 22, 32 });
	right.PushBack({ 145, 56, 22, 32 });
	right.PushBack({ 185, 56, 22, 32 });
	right.speed = 0.2f;

	// Move right
	left.PushBack({ 25, 95, 22, 32 });
	left.PushBack({ 65, 95, 22, 32 });
	left.PushBack({ 105, 95, 22, 32 });
	left.PushBack({ 145, 95, 22, 32 });
	left.PushBack({ 185, 95, 22, 32 });
	left.speed = 0.2f;
	/*down.PushBack({33, 1, 32, 14});
	down.PushBack({0, 1, 32, 14});
	down.loop = false;
	down.speed = 0.1f;*/

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	//graphics = App->textures->Load("rtype/ship.png");

	graphics = App->textures->Load("assets/player_sprites.png");

	position.x = 150;
	position.y = 120;

	// TODO 2: Add a collider to the player

	col = App->collision->AddCollider({ position.x - 2, position.y, 20, 28 }, COLLIDER_PLAYER);
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	int prev_x = position.x;
	int prev_y = position.y;

	/*if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
	position.x -= speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
	position.x += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
	position.y += speed;
	if(current_animation != &down)
	{
	down.Reset();
	current_animation = &down;
	}
	}

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
	position.y -= speed;
	if(current_animation != &up)
	{
	up.Reset();
	current_animation = &up;
	}
	}

	if(App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
	App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, COLLIDER_PLAYER_SHOT);
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE
	&& App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE)
	current_animation = &idle;*/


	//Gun.Smoke

	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (current_animation != &left)
		{
			current_animation = &left;
		}

	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (current_animation != &right)
		{
			current_animation = &right;
		}
	}

	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;

	}

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
	}


	// TODO 3: Update collider position to player position
	col->SetPos(position.x, position.y);

	for (int i = 0; i < 13; ++i)
	{
		if (col->CheckCollision(App->scene_space->Wall[i]->rect))
		{
			position.x = prev_x;
			if (col->CheckCollision_2rect(App->scene_space->Wall[i]->rect, { position.x - 2, position.y - 10, 20, 28 }))
			{
				position.y = prev_y + 5;
			}
		}
	}

	for (int i = 0; i < 3; ++i)
	{
		//if (col->CheckCollision(App->scene_space->Enemy->rect))
		//{
			//App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_intro);
		//}
	}

	//Gun.Smoke

	if (App->input->keyboard[SDL_SCANCODE_Z] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shot_l, position.x, position.y);
		//        App->audio->Play_sound();
	}

	if (App->input->keyboard[SDL_SCANCODE_X] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shot, position.x, position.y);
		//        App->audio->Play_sound();
	}

	if (App->input->keyboard[SDL_SCANCODE_C] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shot_r, position.x, position.y);
		//        App->audio->Play_sound();

	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE)
	{
		current_animation = &idle;
	}
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN)
	{
		current_animation = &idle;
	}
	//CAMARA LIMITS
	if (position.x<0)
	{
		position.x = prev_x;
	}
	if (position.x > 205)
	{
		position.x = prev_x;
	}

	/*if (position.y > 200)
	{
		position.y -= 50;
		for (int i = 0; i < 13; ++i)
		{

			if (col->CheckCollision(App->scene_space->Wall[i]->rect))
			{
				if (position.x > 112)
				{
					position.x -= 15;
				}
				if (position.x < 112)
				{
					position.x += 15;
				}
			}
		}
	}*/

	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 4: Detect collision with a wall. If so, go back to intro screen.
