#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = red_bumper = green_bumper = NULL;
	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	// Load Assets requirede for "map"
	circle = App->textures->Load("pinball/wheel.png");
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	red_bumper = App->textures->Load("pinball/redbump.png");
	green_bumper = App->textures->Load("pinball/greenbump.png");

	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT+50, SCREEN_WIDTH, 40);
	sensor->listener = App->player;
	// Create Level collisions
	
		int pinball[108] = {
			220, 659,
			220, 650,
			325, 620,
			325, 584,
			256, 605,
			250, 590,
			324, 567,
			325, 351,
			282, 334,
			323, 208,
			325, 183,
			321, 155,
			311, 127,
			298, 101,
			273, 77,
			255, 63,
			259, 58,
			280, 72,
			300, 92,
			318, 124,
			326, 146,
			330, 170,
			330, 651,
			367, 651,
			367, 171,
			362, 142,
			350, 112,
			334, 83,
			309, 53,
			280, 31,
			244, 14,
			201, 4,
			154, 5,
			109, 20,
			61, 52,
			27, 97,
			8, 147,
			5, 188,
			11, 227,
			69, 403,
			54, 407,
			45, 416,
			40, 430,
			21, 433,
			11, 442,
			5, 453,
			5, 609,
			151, 651,
			151, 659,
			1, 659,
			0, 1,
			371, 0,
			370, 660,
			222, 660
		};

		stage.add(App->physics->CreateChain(0, 0, pinball, 108, b2_staticBody));
	
	
		int pinballa[14] = {
			47, 480,
			40, 480,
			40, 583,
			118, 605,
			122, 590,
			47, 567,
			47, 481
		};

		stage.add(App->physics->CreateChain(0, 0, pinballa, 14, b2_staticBody));
	
	
		int pinballb[12] = {
			260, 551,
			283, 545,
			287, 541,
			290, 536,
			290, 476,
			260, 550
		};

		stage.add(App->physics->CreateChain(0, 0, pinballb, 12, b2_staticBody));
	
	
		int pinballc[60] = {
			88, 147,
			101, 121,
			122, 100,
			142, 88,
			168, 80,
			186, 78,
			215, 82,
			237, 92,
			257, 106,
			272, 124,
			283, 146,
			288, 162,
			290, 179,
			289, 195,
			284, 219,
			280, 214,
			283, 197,
			284, 175,
			279, 151,
			268, 130,
			254, 112,
			234, 97,
			215, 89,
			190, 84,
			164, 87,
			139, 96,
			121, 108,
			105, 125,
			93, 150,
			89, 147
		};

		stage.add(App->physics->CreateChain(0, 0, pinballc, 60, b2_staticBody));
	
	
		int pinballd[34] = {
			111, 59,
			114, 65,
			92, 80,
			71, 105,
			53, 141,
			47, 172,
			47, 198,
			49, 213,
			107, 388,
			102, 392,
			43, 216,
			40, 182,
			43, 157,
			52, 127,
			70, 96,
			85, 78,
			111, 60
		};

		stage.add(App->physics->CreateChain(0, 0, pinballd, 34, b2_staticBody));
	
		int pinballe[14] = {
			81, 475,
			81, 536,
			85, 542,
			91, 546,
			112, 551,
			112, 545,
			83, 475
		};

		stage.add(App->physics->CreateChain(0, 0, pinballe, 14, b2_staticBody));

		int bumper_left[6] = {
			86, 475,
			117, 544,
			116, 544
		};

		bumpers.add(App->physics->CreateChain(0, 0, bumper_left, 6, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		int bumper_right[6] = {
			285, 473,
			253, 547,
			254, 547
		};

		bumpers.add(App->physics->CreateChain(0, 0, bumper_right, 6, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		//3 up top

		bumpers.add(App->physics->CreateCircle(185, 55, 8, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		//3 red up ones

		bumpers.add(App->physics->CreateCircle(122, 135, 14, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		bumpers.add(App->physics->CreateCircle(188, 103, 14, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		bumpers.add(App->physics->CreateCircle(255, 135, 14, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		//4 middle ones
		bumpers.add(App->physics->CreateCircle(190, 205, 8, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		bumpers.add(App->physics->CreateCircle(105, 284, 8, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		bumpers.add(App->physics->CreateCircle(269, 284, 8, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

		bumpers.add(App->physics->CreateCircle(190, 360, 8, b2_staticBody));
		bumpers.getLast()->data->body->GetFixtureList()->SetRestitution(0.3);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	
	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if(c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		
		c = c->next;
	}

	c = ricks.getFirst();

	while(c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = bumpers.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		if (c->data->width == 14)
		{
			App->renderer->Blit(red_bumper, x, y, NULL, 1.0f, c->data->GetRotation());
		}
		if (c->data->width == 8)
		{
			App->renderer->Blit(green_bumper, x, y, NULL, 1.0f, c->data->GetRotation());
		}

		c = c->next;
	}

	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	int x, y;

	App->audio->PlayFx(bonus_fx);

	/*
	if(bodyA)
	{
		bodyA->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}

	if(bodyB)
	{
		bodyB->GetPosition(x, y);
		App->renderer->DrawCircle(x, y, 50, 100, 100, 100);
	}*/
}
