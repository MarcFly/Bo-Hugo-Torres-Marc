#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneIntro.h"
#include "ModuleWindow.h"
#include "p2SString.h"
#include "ModuleAudio.h"
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

	sound_1 = App->audio->LoadFx("sound_bounce.wav");
	rocket_sound = App->audio->LoadFx("rocketfx.wav");
	//Create desired objects
	bouncers[0].cpbody = App->physics-> App->physics->CreateCircle(126, 597, 0.01f, b2_kinematicBody);
	bouncers[0].flipperpbody = App->physics->CreateRectangle(149, 597, 46, 10,b2_dynamicBody);
	bouncers[0].joint = App->physics->CreateRotJoint(bouncers[0].cpbody, bouncers[0].flipperpbody);

	bouncers[1].cpbody = App->physics->App->physics->CreateCircle(110, 394, 0.01f, b2_kinematicBody);
	bouncers[1].flipperpbody = App->physics->CreateRectangle(127, 394, 34, 10, b2_dynamicBody);
	bouncers[1].joint = App->physics->CreateRotJoint(bouncers[1].cpbody, bouncers[1].flipperpbody);

	bouncers[2].cpbody = App->physics->App->physics->CreateCircle(275, 218, 0.01f, b2_kinematicBody);
	bouncers[2].flipperpbody = App->physics->CreateRectangle(258, 218, 34, 10, b2_dynamicBody);
	bouncers[2].joint = App->physics->CreateFRotJoint(bouncers[2].cpbody, bouncers[2].flipperpbody);

	bouncers[3].cpbody = App->physics->App->physics->CreateCircle(246, 597, 0.01f, b2_kinematicBody);
	bouncers[3].flipperpbody = App->physics->CreateRectangle(229, 597, 46, 10, b2_dynamicBody);
	bouncers[3].joint = App->physics->CreateFRotJoint(bouncers[3].cpbody, bouncers[3].flipperpbody);

	StartBall();
	return true;
}

void ModulePlayer::StartBall()
{
	ball.add(App->physics->CreateCircle(350, 570, 10));
	ball.getLast()->data->body->SetBullet(true);
	ball.getLast()->data->listener = App->player;
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
		bouncers[0].flipperpbody->body->ApplyTorque(20.0f, true);
		bouncers[1].flipperpbody->body->ApplyTorque(20.0f, true);

	}

	if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN))
	{

		bouncers[2].flipperpbody->body->ApplyTorque(100.0f, true);
		bouncers[3].flipperpbody->body->ApplyTorque(100.0f, true);


	}
	else
	{
		bouncers[2].flipperpbody->body->ApplyTorque(-20.0f, true);
		bouncers[3].flipperpbody->body->ApplyTorque(-20.0f, true);

	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		if(timer < 90)
			timer++;
	}
	else if (timer > 0 && ball.getLast()->data->body->GetLinearVelocity().Length() == 0) {
		ball.getLast()->data->body->ApplyLinearImpulse({ 0,-0.05f*(30 + (float)timer) },ball.getLast()->data->body->GetPosition(),true);
		timer = 0;
		App->audio->PlayFx(rocket_sound);
	}

	p2SString title;
	title.create("score:%i  balls:%i  highscore:%i", score, lives, high_score);
	App->window->SetTitle(title.GetString());

	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(PhysBody* pb1, PhysBody* pb2) {
	if (pb2->body->GetFixtureList()->IsSensor())
		lost = true;
	else
		lost = false;

	if (pb2->body->GetFixtureList()->GetShape()->GetType() == pb2->body->GetFixtureList()->GetShape()->e_circle)
		score += 50;
		App->audio->PlayFx(sound_1);
}




