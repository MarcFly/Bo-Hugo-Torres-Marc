#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include <math.h>

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	//Load assets required for player (palancas tt)


	//Create desired objects
	bouncers[0].cpbody = App->physics-> App->physics->CreateCircle(175, 400, 0.01f, b2_kinematicBody);
	bouncers[0].flipperpbody = App->physics->CreateRectangle(200, 400, 50, 10,b2_dynamicBody);
	bouncers[0].joint = App->physics->CreateRotJoint(bouncers[0].cpbody, bouncers[0].flipperpbody);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	if ((App->input->GetKey(SDL_SCANCODE_L) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN ) && bouncers[0].joint != nullptr)
	{
		
		bouncers[0].flipperpbody->body->ApplyTorque(-100.0f, true);

		
	}
	else if (bouncers[0].joint != nullptr)
	{
		bouncers[0].flipperpbody->body->ApplyTorque(100.0f, true);

	}

	
	//LOG("%f", bouncers[0].joint->GetMotorSpeed());
	return UPDATE_CONTINUE;
}



