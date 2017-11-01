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

	bouncers[1].cpbody = App->physics->App->physics->CreateCircle(175, 600, 0.01f, b2_kinematicBody);
	bouncers[1].flipperpbody = App->physics->CreateRectangle(200, 600, 50, 10, b2_dynamicBody);
	bouncers[1].joint = App->physics->CreateRotJoint(bouncers[1].cpbody, bouncers[1].flipperpbody);

	bouncers[2].cpbody = App->physics->App->physics->CreateCircle(225, 200, 0.01f, b2_kinematicBody);
	bouncers[2].flipperpbody = App->physics->CreateRectangle(200, 200, 50, 10, b2_dynamicBody);
	bouncers[2].joint = App->physics->CreateFRotJoint(bouncers[2].cpbody, bouncers[2].flipperpbody);

	bouncers[3].cpbody = App->physics->App->physics->CreateCircle(225, 800, 0.01f, b2_kinematicBody);
	bouncers[3].flipperpbody = App->physics->CreateRectangle(200, 800, 50, 10, b2_dynamicBody);
	bouncers[3].joint = App->physics->CreateFRotJoint(bouncers[3].cpbody, bouncers[3].flipperpbody);

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

	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN ))
	{
		
		bouncers[0].flipperpbody->body->ApplyTorque(-100.0f, true);
		bouncers[1].flipperpbody->body->ApplyTorque(-100.0f, true);

		
	}
	else
	{
		bouncers[0].flipperpbody->body->ApplyTorque(100.0f, true);
		bouncers[1].flipperpbody->body->ApplyTorque(100.0f, true);

	}

	if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN))
	{

		bouncers[2].flipperpbody->body->ApplyTorque(100.0f, true);
		bouncers[3].flipperpbody->body->ApplyTorque(100.0f, true);


	}
	else
	{
		bouncers[2].flipperpbody->body->ApplyTorque(-100.0f, true);
		bouncers[3].flipperpbody->body->ApplyTorque(-100.0f, true);

	}

	
	//LOG("%f", bouncers[0].joint->GetMotorSpeed());
	return UPDATE_CONTINUE;
}



