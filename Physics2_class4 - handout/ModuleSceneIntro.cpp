#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
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
	bonus_fx = App->audio->LoadFx("pinball/bonus.wav");

	sensor = App->physics->CreateRectangleSensor(SCREEN_WIDTH / 2, SCREEN_HEIGHT, SCREEN_WIDTH, 50);

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
	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		ray_on = !ray_on;
		ray.x = App->input->GetMouseX();
		ray.y = App->input->GetMouseY();
	}

	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		circles.getLast()->data->listener = this;
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 100, 50));
	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// Pivot 0, 0
		int rick_head[64] = {
			14, 36,
			42, 40,
			40, 0,
			75, 30,
			88, 4,
			94, 39,
			111, 36,
			104, 58,
			107, 62,
			117, 67,
			109, 73,
			110, 85,
			106, 91,
			109, 99,
			103, 104,
			100, 115,
			106, 121,
			103, 125,
			98, 126,
			95, 137,
			83, 147,
			67, 147,
			53, 140,
			46, 132,
			34, 136,
			38, 126,
			23, 123,
			30, 114,
			10, 102,
			29, 90,
			0, 75,
			30, 62
		};

		ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64));
	}

	// Prepare for raycast ------------------------------------------------------
	
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();
	int ray_hit = ray.DistanceTo(mouse);

	fVector normal(0.0f, 0.0f);

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
		if(ray_on)
		{
			int hit = c->data->RayCast(ray.x, ray.y, mouse.x, mouse.y, normal.x, normal.y);
			if(hit >= 0)
				ray_hit = hit;
		}
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

	// ray -----------------
	if(ray_on == true)
	{
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
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
